#include "robot_simulator.cpp"
#include <fstream>
#include <iostream>
#include <ompl/base/goals/GoalState.h>
#include <ompl/base/spaces/RealVectorStateSpace.h>
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
    auto space = std::make_shared<ob::RealVectorStateSpace>(2);
    ob::RealVectorBounds bounds(2);
    bounds.setLow(-M_PI);
    bounds.setHigh(M_PI);
    space->setBounds(bounds);
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

    // start and goal states
    ob::ScopedState<> start(space);
    start[0] = -M_PI;
    start[1] = 0.0;
    ob::ScopedState<> goal(space);
    goal[0] = 1.57;
    goal[1] = 0.0;
    ss.setStartAndGoalStates(start, goal);

    // Planner setup and solved
    // auto planner = std::make_shared<og::RRT>(ss.getSpaceInformation());
    auto planner = std::make_shared<og::RRTstar>(ss.getSpaceInformation());
    planner->setRange(0.3);
    planner->setGoalBias(0.05);
    ss.setPlanner(planner);
    planner->getProblemDefinition();
    ob::PlannerStatus solved = ss.solve(2.0); // within a time limit

    if (solved) {
        std::cout << "Found solution!" << std::endl;

        // ss.simplifySolution();
        ss.getSolutionPath().print(std::cout);

        const og::PathGeometric &path = ss.getSolutionPath();

        auto space_information(std::make_shared<ompl::base::SpaceInformation>(space));
        savePathToFile(path, "zzz_path.csv");
        savePlannerData(planner, space_information);
        saveStartAndGoal(ss);
    } else {
        std::cout << "No solution found." << std::endl;
    }

    return 0;
}

bool isStateValid(const ob::State *state, PlanarRRSIM &sim) {
    const ob::RealVectorStateSpace::StateType *realState = state->as<ob::RealVectorStateSpace::StateType>();
    double theta1 = realState->values[0];
    double theta2 = realState->values[1];
    // Check for collisions using the sim object
    // the function returns true if it is collision, which is notvalid.
    // since the isStateValid is oppsite to the collision, we reverse it.
    bool c = sim.check_collision(theta1, theta2);
    // printf("state {%f, %f} - col {%d} \n", theta1, theta2, c);
    return !c;
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
        file << theta1 << "," << theta2 << std::endl;
    }

    file.close();
    std::cout << "Path saved to " << filename << std::endl;
}

void savePlannerData(const ompl::base::PlannerPtr &planner, const ompl::base::SpaceInformationPtr &si) {
    ompl::base::PlannerData plannerData(si);
    planner->getPlannerData(plannerData);

    // Save PlannerData to a .graphml file
    std::ofstream file("zzz_planner_data.graphml");
    plannerData.printGraphML(file);
    file.close();
}

void saveStartAndGoal(const ompl::geometric::SimpleSetup &ss) {
    // Get the start and goal states
    const ob::State *startState = ss.getProblemDefinition()->getStartState(0);
    const ob::GoalState *goalState = ss.getProblemDefinition()->getGoal()->as<ob::GoalState>();

    std::ofstream file("zzz_start_goal.csv");

    const double *start_coords = startState->as<ob::RealVectorStateSpace::StateType>()->values;
    file << start_coords[0] << "," << start_coords[1] << std::endl;

    const double *goal_coords = goalState->getState()->as<ob::RealVectorStateSpace::StateType>()->values;
    file << goal_coords[0] << "," << goal_coords[1] << std::endl;

    file.close();
}