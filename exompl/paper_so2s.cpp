#include "robot_simulator.cpp"
#include <fstream>
#include <iostream>
#include <ompl/base/goals/GoalState.h>
#include <ompl/base/spaces/SO2StateSpace.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/geometric/planners/rrt/RRT.h>
#include <ompl/geometric/planners/rrt/RRTstar.h>

namespace ob = ompl::base;
namespace og = ompl::geometric;

bool isStateValid(const ob::State *state, PlanarRRSIM &sim);
void savePathToFile(const og::PathGeometric &path, const std::string &filename);
void savePlannerData(const ompl::base::PlannerPtr &planner, const ompl::base::SpaceInformationPtr &si);
void saveStartAndGoal(const ompl::geometric::SimpleSetup &ss);

int main() {
    // Planning space setup
    auto space = std::make_shared<ob::CompoundStateSpace>();        // each joint represented by SO2
    space->addSubspace(std::make_shared<ob::SO2StateSpace>(), 1.0); // First joint with weight of 1.0
    space->addSubspace(std::make_shared<ob::SO2StateSpace>(), 1.0); // Second joint
    og::SimpleSetup ss(space);

    // Robot setup
    double l1 = 2.0;
    double l2 = 2.0;
    PlanarRR robot(l1, l2);

    // Simulation setup
    std::vector<Rectangle> env;
    env.push_back(Rectangle(-2.75, 1.0, 2.0, 1.0));
    env.push_back(Rectangle(1.5, 2.0, 2.0, 1.0));
    PlanarRRSIM sim(robot, env);

    // Collision setup. Set the state validity checker using a lambda to pass 'sim' to 'isStateValid'
    ss.setStateValidityChecker([&sim](const ob::State *state) {
        return isStateValid(state, sim);
    });

    // 4. Define the start and goal states
    ob::ScopedState<ob::CompoundStateSpace> start(space);
    start[0] = -M_PI/2;
    start[1] = -M_PI + 0.3;

    ob::ScopedState<ob::CompoundStateSpace> goal(space);
    goal[0] = -M_PI/2;
    goal[1] = M_PI - 0.3;

    ss.setStartAndGoalStates(start, goal);

    // Planner setup and solved
    // auto planner = std::make_shared<og::RRT>(ss.getSpaceInformation());
    auto planner = std::make_shared<og::RRTstar>(ss.getSpaceInformation());
    planner->setRange(0.3);
    planner->setGoalBias(0.05);
    ss.setPlanner(planner);
    ob::PlannerStatus solved = ss.solve(2.0);

    if (solved) {
        std::cout << "Found solution! Printing it out...!" << std::endl;

        // ss.simplifySolution();
        ss.getSolutionPath().print(std::cout);
        // ss.getSolutionPath().printAsMatrix(std::cout);

        const og::PathGeometric &path = ss.getSolutionPath();
        auto space_information(std::make_shared<ompl::base::SpaceInformation>(space));
        savePathToFile(path, "z_path.csv");
        savePlannerData(planner, space_information);
        saveStartAndGoal(ss);
    } else {
        std::cout << "No solution found." << std::endl;
    }

    return 0;
}

bool isStateValid(const ob::State *state, PlanarRRSIM &sim) {
    const auto *compoundstate = state->as<ob::CompoundState>();
    double theta1 = compoundstate->as<ob::SO2StateSpace::StateType>(0)->value;
    double theta2 = compoundstate->as<ob::SO2StateSpace::StateType>(1)->value;
    bool c = sim.check_collision(theta1, theta2);
    // printf("state {%f, %f} - col {%d} \n", theta1, theta2, c);
    return !c;
    // return true;
}

void savePathToFile(const og::PathGeometric &path, const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    for (std::size_t i = 0; i < path.getStateCount(); ++i) {
        // Extract joint angles (SO2 states)
        const ob::State *state = path.getState(i);
        const auto *compoundState = state->as<ob::CompoundState>();
        double joint1 = compoundState->as<ob::SO2StateSpace::StateType>(0)->value;
        double joint2 = compoundState->as<ob::SO2StateSpace::StateType>(1)->value;
        file << joint1 << "," << joint2 << std::endl;
    }

    file.close();
    std::cout << "Path saved to " << filename << std::endl;
}

void savePlannerData(const ompl::base::PlannerPtr &planner, const ompl::base::SpaceInformationPtr &si) {
    ompl::base::PlannerData plannerData(si);
    planner->getPlannerData(plannerData);

    // Save PlannerData to a .graphml file
    std::ofstream file("z_planner_data.graphml");
    plannerData.printGraphML(file);
    file.close();
}

void saveStartAndGoal(const ompl::geometric::SimpleSetup &ss) {
    // Get the start and goal states
    const ob::State *startState = ss.getProblemDefinition()->getStartState(0);

    std::ofstream file("z_start_goal.csv");

    const auto *start_coords = startState->as<ob::CompoundState>();
    double ss1 = start_coords->as<ob::SO2StateSpace::StateType>(0)->value;
    double ss2 = start_coords->as<ob::SO2StateSpace::StateType>(1)->value;
    file << ss1 << "," << ss2 << std::endl;

    auto goalPtr = ss.getProblemDefinition()->getGoal();
    auto goalState = std::dynamic_pointer_cast<ob::GoalState>(goalPtr);
    const ob::State *goalStateVal = goalState->getState();
    const auto *compoundState = goalStateVal->as<ob::CompoundState>();
    double gs1 = compoundState->as<ob::SO2StateSpace::StateType>(0)->value;
    double gs2 = compoundState->as<ob::SO2StateSpace::StateType>(1)->value;
    file << gs1 << "," << gs2 << std::endl;

    file.close();
}