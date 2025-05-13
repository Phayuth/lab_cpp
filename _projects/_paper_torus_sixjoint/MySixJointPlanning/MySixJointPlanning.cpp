#include "Utils/b3Clock.h"
#include "Bullet3Common/b3Quaternion.h"
#include "Bullet3Common/b3Vector3.h"
#include "SharedMemory/PhysicsClientC_API.h"
#include "SharedMemory/SharedMemoryInProcessPhysicsC_API.h"
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

#include <ompl/base/goals/GoalState.h>
#include <ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/geometric/planners/rrt/RRTstar.h>

extern const int CONTROL_RATE;
const int CONTROL_RATE = 500;

// Bullet globals
b3PhysicsClientHandle kPhysClient = 0;
const b3Scalar FIXED_TIMESTEP = 1.0 / ((b3Scalar)CONTROL_RATE);

// temp vars used a lot
b3SharedMemoryCommandHandle command;
b3SharedMemoryStatusHandle statusHandle;
int statusType, ret;
b3JointInfo jointInfo;
b3JointSensorState state;

// variable
int ur5eid;
int planeid;
int tableid;
int pole1, pole2, pole3, pole4;
std::map<std::string, int> jointNameToId;
std::array<int, 6> jointIndices = {1, 2, 3, 4, 5, 6};
std::array<std::string, 6> jointNames = {"shoulder_pan_joint",
                                         "shoulder_lift_joint",
                                         "elbow_joint",
                                         "wrist_1_joint",
                                         "wrist_2_joint",
                                         "wrist_3_joint"};

// planning ompl
namespace ob = ompl::base;
namespace og = ompl::geometric;

bool resetJointState(b3PhysicsClientHandle &kPhysClient, int &bodyID,
                     int &jointIndex, double &targetVal) {
    command = b3CreatePoseCommandInit(kPhysClient, bodyID);
    b3CreatePoseCommandSetJointPosition(
        kPhysClient, command, jointIndex, targetVal);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    return true;
}

bool resetJointStateArray(b3PhysicsClientHandle &kPhysClient, int &bodyID,
                          std::array<int, 6> &jointIndices,
                          std::array<double, 6> &targetVals) {
    for (size_t i = 0; i < 6; i++) {
        resetJointState(kPhysClient, bodyID, jointIndices[i], targetVals[i]);
    }
    return true;
}

bool collision_check_singlebody(b3PhysicsClientHandle &kPhysClient, int &bodyA,
                                int &bodyB) {
    command = b3InitRequestContactPointInformation(kPhysClient);
    b3SetContactFilterBodyA(command, bodyA);
    b3SetContactFilterBodyB(command, bodyB);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    statusType = b3GetStatusType(statusHandle);
    struct b3ContactInformation contactInfo;
    if (statusType == CMD_CONTACT_POINT_INFORMATION_COMPLETED) {
        b3GetContactPointInformation(kPhysClient, &contactInfo);
        if (contactInfo.m_contactPointData > 0) {
            return true;
        }
    }
    return false;
}

bool collision_check_multibody(b3PhysicsClientHandle &kPhysClient, int &mainbody,
                               std::vector<int> &otherbodies) {
    for (size_t i = 0; i < otherbodies.size(); i++) {
        if (collision_check_singlebody(kPhysClient, mainbody, otherbodies.at(i))) {
            return true;
        }
    }
    return false;
}

bool collision_check_per_config(b3PhysicsClientHandle &kPhysClient, int &robot,
                                std::vector<int> &obstacles,
                                std::array<int, 6> &jointIndices,
                                std::array<double, 6> &targetVals) {
    // set robot joint to configuration
    resetJointStateArray(kPhysClient, robot, jointIndices, targetVals);

    // perform collision check call over the whole scene by bullet
    command = b3InitPerformCollisionDetectionCommand(kPhysClient);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);

    // read collsion
    return collision_check_multibody(kPhysClient, robot, obstacles);
}

bool isStateValid(const ob::State *state, b3PhysicsClientHandle &kPhysClient,
                  int &robot, std::vector<int> &obstacles,
                  std::array<int, 6> &jointIndices) {
    // get query configuration
    const ob::RealVectorStateSpace::StateType *realState =
        state->as<ob::RealVectorStateSpace::StateType>();
    std::array<double, 6> targetVals = {realState->values[0],
                                        realState->values[1],
                                        realState->values[2],
                                        realState->values[3],
                                        realState->values[4],
                                        realState->values[5]};

    // Check for collisions using the sim object
    // the function returns true if it is collision, which is notvalid.
    // since the isStateValid is oppsite to the collision, we reverse it.
    return !collision_check_per_config(
        kPhysClient, robot, obstacles, jointIndices, targetVals);
    // return true;
}

void savePathToFile(const og::PathGeometric &path, const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    for (std::size_t i = 0; i < path.getStateCount(); ++i) {
        const ob::State *state = path.getState(i);
        const auto *realState = state->as<ob::RealVectorStateSpace::StateType>();
        double theta1 = realState->values[0];
        double theta2 = realState->values[1];
        double theta3 = realState->values[2];
        double theta4 = realState->values[3];
        double theta5 = realState->values[4];
        double theta6 = realState->values[5];
        file << theta1 << "," << theta2 << "," << theta3 << "," << theta4 << ","
             << theta5 << "," << theta6 << std::endl;
    }

    file.close();
    std::cout << "Path saved to " << filename << std::endl;
}

int main(int argc, char *argv[]) {
    // kPhysClient = b3CreateInProcessPhysicsServerAndConnect(argc, argv); // show
    // gui
    kPhysClient = b3ConnectPhysicsDirect(); // no gui
    if (!kPhysClient)
        return -1;

    // visualizer
    // command = b3InitConfigureOpenGLVisualizer(kPhysClient);
    // b3ConfigureOpenGLVisualizerSetVisualizationFlags(command, COV_ENABLE_GUI,
    // 0); b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    // b3ConfigureOpenGLVisualizerSetVisualizationFlags(command,
    // COV_ENABLE_SHADOWS, 0); b3SubmitClientCommandAndWaitStatus(kPhysClient,
    // command);

    b3SetTimeOut(kPhysClient, 10);

    // syncBodies is only needed when connecting to an existing physics server that
    // has already some bodies
    command = b3InitSyncBodyInfoCommand(kPhysClient);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    statusType = b3GetStatusType(statusHandle);

    // set fixed time step
    command = b3InitPhysicsParamCommand(kPhysClient);
    ret = b3PhysicsParamSetTimeStep(command, FIXED_TIMESTEP);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    ret = b3PhysicsParamSetRealTimeSimulation(command, false);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    b3Assert(b3GetStatusType(statusHandle) == CMD_CLIENT_COMMAND_COMPLETED);

    // load plane
    command = b3LoadUrdfCommandInit(kPhysClient, "plane.urdf");
    b3LoadUrdfCommandSetStartPosition(
        command,
        0.0,
        0.0,
        -0.005); // 5mm offset the plane down to avoid collision with robot base
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    statusType = b3GetStatusType(statusHandle);
    b3Assert(statusType == CMD_URDF_LOADING_COMPLETED);
    if (statusType == CMD_URDF_LOADING_COMPLETED) {
        planeid = b3GetStatusBodyIndex(statusHandle);
    }

    // load table
    command = b3LoadUrdfCommandInit(kPhysClient, "table/table.urdf");
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    statusType = b3GetStatusType(statusHandle);
    b3Assert(statusType == CMD_URDF_LOADING_COMPLETED);
    if (statusType == CMD_URDF_LOADING_COMPLETED) {
        tableid = b3GetStatusBodyIndex(statusHandle);
    }

    // load ur5e
    command = b3LoadUrdfCommandInit(kPhysClient, "ur5e_extract_calibrated.urdf");
    int flags = URDF_USE_SELF_COLLISION;
    b3LoadUrdfCommandSetFlags(command, flags);
    b3LoadUrdfCommandSetUseFixedBase(command, true);
    b3LoadUrdfCommandSetUseMultiBody(command, true);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    statusType = b3GetStatusType(statusHandle);
    b3Assert(statusType == CMD_URDF_LOADING_COMPLETED);
    if (statusType == CMD_URDF_LOADING_COMPLETED) {
        ur5eid = b3GetStatusBodyIndex(statusHandle);
    }

    // load pole1
    command = b3LoadUrdfCommandInit(kPhysClient,
                                    "/home/yuth/ws_yuthdev/robotics_manipulator/"
                                    "datasave/urdf/simple_box.urdf");
    b3LoadUrdfCommandSetStartPosition(command, 0.3, 0.3, 0.0);
    b3LoadUrdfCommandSetUseFixedBase(command, true);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    statusType = b3GetStatusType(statusHandle);
    b3Assert(statusType == CMD_URDF_LOADING_COMPLETED);
    if (statusType == CMD_URDF_LOADING_COMPLETED) {
        pole1 = b3GetStatusBodyIndex(statusHandle);
    }
    // load pole2
    command = b3LoadUrdfCommandInit(kPhysClient,
                                    "/home/yuth/ws_yuthdev/robotics_manipulator/"
                                    "datasave/urdf/simple_box.urdf");
    b3LoadUrdfCommandSetStartPosition(command, -0.3, 0.3, 0.0);
    b3LoadUrdfCommandSetUseFixedBase(command, true);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    statusType = b3GetStatusType(statusHandle);
    b3Assert(statusType == CMD_URDF_LOADING_COMPLETED);
    if (statusType == CMD_URDF_LOADING_COMPLETED) {
        pole2 = b3GetStatusBodyIndex(statusHandle);
    }
    // load pole2
    command = b3LoadUrdfCommandInit(kPhysClient,
                                    "/home/yuth/ws_yuthdev/robotics_manipulator/"
                                    "datasave/urdf/simple_box.urdf");
    b3LoadUrdfCommandSetStartPosition(command, -0.3, -0.3, 0.0);
    b3LoadUrdfCommandSetUseFixedBase(command, true);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    statusType = b3GetStatusType(statusHandle);
    b3Assert(statusType == CMD_URDF_LOADING_COMPLETED);
    if (statusType == CMD_URDF_LOADING_COMPLETED) {
        pole3 = b3GetStatusBodyIndex(statusHandle);
    }
    // load pole3
    command = b3LoadUrdfCommandInit(kPhysClient,
                                    "/home/yuth/ws_yuthdev/robotics_manipulator/"
                                    "datasave/urdf/simple_box.urdf");
    b3LoadUrdfCommandSetStartPosition(command, 0.3, -0.3, 0.0);
    b3LoadUrdfCommandSetUseFixedBase(command, true);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    statusType = b3GetStatusType(statusHandle);
    b3Assert(statusType == CMD_URDF_LOADING_COMPLETED);
    if (statusType == CMD_URDF_LOADING_COMPLETED) {
        pole4 = b3GetStatusBodyIndex(statusHandle);
    }

    // add bodies for collision check later
    // std::vector<int> obstacles = {planeid, tableid};
    // std::vector<int> obstacles = {planeid}; // no table
    std::vector<int> obstacles = {planeid, pole1, pole2, pole3, pole4};

    // disable default linear/angular damping
    b3SharedMemoryCommandHandle command = b3InitChangeDynamicsInfo(kPhysClient);
    double linearDamping = 0;
    double angularDamping = 0;
    b3ChangeDynamicsInfoSetLinearDamping(command, ur5eid, linearDamping);
    b3ChangeDynamicsInfoSetAngularDamping(command, ur5eid, angularDamping);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);

    // Loop through all joints and get the id of robot's revolute joint
    int numJoints = b3GetNumJoints(kPhysClient, ur5eid);
    printf("\nnumjoints = %d\n", numJoints);
    for (int i = 0; i < numJoints; ++i) {
        b3GetJointInfo(kPhysClient, ur5eid, i, &jointInfo);
        if (jointInfo.m_jointName[0]) {
            for (int j = 0; j < jointNames.size(); ++j) {
                if (jointNames.at(j) == std::string(jointInfo.m_jointName)) {
                    jointNameToId[std::string(jointInfo.m_jointName)] = i;
                    std::cout << std::string(jointInfo.m_jointName) << std::endl;
                }
            }
        } else {
            continue;
        }
    }

    // Planning setup
    auto space = std::make_shared<ob::RealVectorStateSpace>(6);
    ob::RealVectorBounds bounds(6);
    bounds.setLow(-2 * M_PI); // set all joint bound to 2pi
    bounds.setHigh(2 * M_PI);
    bounds.setLow(2, -M_PI); // set elbow joint (index 2) bound to pi
    bounds.setHigh(2, M_PI);
    space->setBounds(bounds);
    og::SimpleSetup ss(space);

    // Collision setup. Set the state validity checker using a lambda
    ss.setStateValidityChecker([&](const ob::State *state) {
        return isStateValid(state, kPhysClient, ur5eid, obstacles, jointIndices);
    });

    // start and goal states
    ob::ScopedState<> start(space);
    start[0] = 0.0;
    start[1] = -0.98;
    start[2] = 1.57;
    start[3] = -0.47;
    start[4] = 1.57;
    start[5] = 0.0;
    ob::ScopedState<> goal(space);
    goal[0] = -3.22;
    goal[1] = -1.09;
    goal[2] = 1.59;
    goal[3] = 5.86;
    goal[4] = 1.59;
    goal[5] = 0.0;
    ss.setStartAndGoalStates(start, goal);

    // Planner setup and solved
    // auto planner = std::make_shared<og::RRT>(ss.getSpaceInformation());
    auto planner = std::make_shared<og::RRTstar>(ss.getSpaceInformation());
    planner->setRange(0.3);
    planner->setGoalBias(0.05);
    ss.setPlanner(planner);
    planner->getProblemDefinition();
    ob::PlannerStatus solved = ss.solve(10.0); // within a time limit

    if (solved) {
        std::cout << "Found solution!" << std::endl;

        ss.simplifySolution();
        // ss.getSolutionPath().print(std::cout);

        const og::PathGeometric &path = ss.getSolutionPath();
        savePathToFile(path, "zzz_path.csv");

    } else {
        std::cout << "No solution found." << std::endl;
    }

    b3DisconnectSharedMemory(kPhysClient);
    return 0;
}