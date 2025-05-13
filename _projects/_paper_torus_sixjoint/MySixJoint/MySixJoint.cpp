#include "Bullet3Common/b3Quaternion.h"
#include "Bullet3Common/b3Vector3.h"
#include "SharedMemory/PhysicsClientC_API.h"
#include "SharedMemory/SharedMemoryInProcessPhysicsC_API.h"
#include "Utils/b3Clock.h"
#include <array>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

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
std::map<std::string, int> jointNameToId;
std::array<int, 6> jointIndices = {1, 2, 3, 4, 5, 6};
std::array<std::string, 6> jointNames = {"shoulder_pan_joint",
                                         "shoulder_lift_joint",
                                         "elbow_joint",
                                         "wrist_1_joint",
                                         "wrist_2_joint",
                                         "wrist_3_joint"};

bool resetJointState(b3PhysicsClientHandle &kPhysClient, int bodyID,
                     int jointIndex, double targetVal) {
    command = b3CreatePoseCommandInit(kPhysClient, bodyID);
    b3CreatePoseCommandSetJointPosition(
        kPhysClient, command, jointIndex, targetVal);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    return true;
}

bool resetJointStateArray(b3PhysicsClientHandle &kPhysClient, int bodyID,
                          std::array<int, 6> &jointIndices,
                          std::array<double, 6> &targetVals) {
    for (size_t i = 0; i < 6; i++) {
        resetJointState(kPhysClient, bodyID, jointIndices[i], targetVals[i]);
    }
    return true;
}

bool collision_check_singlebody(b3PhysicsClientHandle &kPhysClient, int bodyA,
                                int bodyB) {
    command = b3InitRequestContactPointInformation(kPhysClient);
    b3SetContactFilterBodyA(command, bodyA);
    b3SetContactFilterBodyB(command, bodyB);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    statusType = b3GetStatusType(statusHandle);
    struct b3ContactInformation contactInfo;
    if (statusType == CMD_CONTACT_POINT_INFORMATION_COMPLETED) {
        b3GetContactPointInformation(kPhysClient, &contactInfo);
        if (contactInfo.m_contactPointData != nullptr) {
            return true;
        }
    }
    return false;
}

bool collision_check_multibody(b3PhysicsClientHandle &kPhysClient, int mainbody,
                               std::vector<int> otherbodies) {
    for (size_t i = 0; i < otherbodies.size(); i++) {
        if (collision_check_singlebody(kPhysClient, mainbody, otherbodies.at(i))) {
            return true;
        }
    }
    return false;
}

bool collision_check_per_config(b3PhysicsClientHandle &kPhysClient, int robot,
                                std::vector<int> obstacles,
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

int main(int argc, char *argv[]) {
    kPhysClient = b3CreateInProcessPhysicsServerAndConnect(argc, argv);
    if (!kPhysClient)
        return -1;

    // visualizer
    command = b3InitConfigureOpenGLVisualizer(kPhysClient);
    b3ConfigureOpenGLVisualizerSetVisualizationFlags(command, COV_ENABLE_GUI, 0);
    b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
    b3ConfigureOpenGLVisualizerSetVisualizationFlags(
        command, COV_ENABLE_SHADOWS, 0);
    b3SubmitClientCommandAndWaitStatus(kPhysClient, command);

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
        -0.005); // offset the plane down abit to avoid collision with robot base
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

    // add bodies for collision check later
    std::vector<int> obstacles = {planeid, tableid};

    // disable default linear/angular damping
    b3SharedMemoryCommandHandle command = b3InitChangeDynamicsInfo(kPhysClient);
    double linearDamping = 0;
    double angularDamping = 0;
    b3ChangeDynamicsInfoSetLinearDamping(command, ur5eid, linearDamping);
    b3ChangeDynamicsInfoSetAngularDamping(command, ur5eid, angularDamping);
    statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);

    // Loop through all joints and get the id of robot's revolute joint
    int numJoints = b3GetNumJoints(kPhysClient, ur5eid);
    printf("numjoints = %d\n", numJoints);
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

    std::array<double, 6> target = {M_PI, -M_PI_2, 0.0, 0.0, 0.0, 0.0};

    // loop
    // unsigned long dtus1 = (unsigned long)1000000.0 * FIXED_TIMESTEP;
    // double simTimeS = 0;

    while (b3CanSubmitCommand(kPhysClient)) {
        bool col = collision_check_per_config(
            kPhysClient, ur5eid, obstacles, jointIndices, target);

        if (col) {
            printf("There is/are collision occured\n");
        }

        // simTimeS += 0.000001 * dtus1;

        // if (collision_check_multibody(kPhysClient, ur5eid, obstacles))
        // {
        //     printf("There is/are collision occured\n");
        // }

        // statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient,
        // b3InitStepSimulationCommand(kPhysClient)); printf("%.3f\t\n", simTimeS);
        b3Clock::usleep(1000. * 1000. * FIXED_TIMESTEP);
    }
    b3DisconnectSharedMemory(kPhysClient);
    return 0;
}

// reset joint state
// resetJointState(kPhysClient, ur5eid, 1, M_PI);
// std::array<double, 6> target = {M_PI, -M_PI_2, 0.0, 0.0, 0.0, 0.0};
// resetJointStateArray(kPhysClient, ur5eid, jointIndices, target);

// collision call when we dont step the simulation
// command = b3InitPerformCollisionDetectionCommand(kPhysClient);
// statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);

// collsion read
// command = b3InitRequestContactPointInformation(kPhysClient);
// b3SetContactFilterBodyA(command, ur5eid);
// b3SetContactFilterBodyB(command, planeid);
// statusHandle = b3SubmitClientCommandAndWaitStatus(kPhysClient, command);
// statusType = b3GetStatusType(statusHandle);
// struct b3ContactInformation contactInfo;
// if (statusType == CMD_CONTACT_POINT_INFORMATION_COMPLETED)
// {
//     b3GetContactPointInformation(kPhysClient, &contactInfo);
//     if (contactInfo.m_contactPointData>0)
//     {
//         printf("m_numContactPoints : %d\n", contactInfo.m_numContactPoints);
//     }
// }