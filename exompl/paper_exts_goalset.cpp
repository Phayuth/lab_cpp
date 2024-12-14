#include "findaltconfig.cpp"
#include "robot_simulator.cpp"
#include <fstream>
#include <iostream>
#include <ompl/base/goals/GoalStates.h>
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
    bounds.setLow(-2.0 * M_PI);
    bounds.setHigh(2.0 * M_PI);
    space->setBounds(bounds);
    og::SimpleSetup ss(space);

    // Robot setup
    double l1 = 2.0;
    double l2 = 2.0;
    PlanarRR robot(l1, l2);

    // Simulation setup
    std::vector<Rectangle> env;
    // ijcas env
    // env.push_back(Rectangle(-2.75, 1.0, 2.0, 1.0));
    // env.push_back(Rectangle(1.5, 2.0, 2.0, 1.0));

    // ifac env
    env.push_back(Rectangle(-0.7, 1.3, 2.0, 2.2));
    env.push_back(Rectangle(2.0, -2.0, 1.0, 4.0));
    env.push_back(Rectangle(-3.0, -3.0, 1.25, 2.0));
    PlanarRRSIM sim(robot, env);

    // Collision setup. Set the state validity checker using a lambda to pass 'sim' to 'isStateValid'
    ss.setStateValidityChecker([&sim](const ob::State *state) {
        return isStateValid(state, sim);
    });

    // Define the start state
    // Eigen::RowVectorXd qstart(2);
    ob::ScopedState<> start(space);
    // qstart << 2.68, -2.86;
    // for (size_t i = 0; i < qstart.rows(); i++) {
    //     start[i] = qstart[i];
    // }
    start[0] = 2.68;
    start[1] = -2.86;
    ss.setStartState(start);

    // Define multiple goal states
    Eigen::RowVectorXd qgoal(2);
    qgoal << -0.70, 1.73;
    Eigen::RowVectorXd qlimit(2);
    qlimit << 2 * M_PI, 2 * M_PI;
    Eigen::MatrixXd qgoalalt = find_alt_config(qgoal, qlimit);
    printf("\nI found %d alternative goal configurations.\n", qgoalalt.rows());
    printf("\nThey are: \n");
    for (size_t i = 0; i < qgoalalt.rows(); i++) {
        std::cout << qgoalalt.row(i) << std::endl;
    }
    auto goal = std::make_shared<ob::GoalStates>(ss.getSpaceInformation());
    for (size_t i = 0; i < qgoalalt.rows(); i++) {
        ob::ScopedState<> goali(space);
        for (size_t j = 0; j < qgoalalt.cols(); j++) {
            goali[j] = qgoalalt.row(i)[j];
        }
        goal->addState(goali);
    }
    ss.setGoal(goal);

    // std::vector<ob::ScopedState<>> goalStates;
    // ob::ScopedState<> goal1(space);
    // goal1[0] = -M_PI;
    // goal1[1] = M_PI;
    // goalStates.push_back(goal1);
    // ob::ScopedState<> goal2(space);
    // goal2[0] = M_PI;
    // goal2[1] = M_PI;
    // goalStates.push_back(goal2);
    // // Set up multiple goal states by using an OrientedGoalRegion
    // auto goal = std::make_shared<ob::GoalStates>(ss.getSpaceInformation());
    // for (auto &goalState : goalStates) {
    //     goal->addState(goalState);
    // }
    // ss.setGoal(goal);

    // Planner setup and solved
    // auto planner = std::make_shared<og::RRT>(ss.getSpaceInformation());
    auto planner = std::make_shared<og::RRTstar>(ss.getSpaceInformation());
    planner->setRange(0.3);
    planner->setGoalBias(0.05);
    ss.setPlanner(planner);
    ob::PlannerStatus solved = ss.solve(2.0); // within a time limit

    if (solved) {
        std::cout << "Found solution:" << std::endl;

        ss.simplifySolution();
        ss.getSolutionPath().print(std::cout);

        const og::PathGeometric &path = ss.getSolutionPath();
        auto space_information(std::make_shared<ompl::base::SpaceInformation>(space));
        savePathToFile(path, "zzzzz_path.csv");
        savePlannerData(planner, space_information);
        saveStartAndGoal(ss);
    } else {
        std::cout << "No solution found" << std::endl;
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
    std::ofstream file("zzzzz_planner_data.graphml");
    plannerData.printGraphML(file);
    file.close();
}

void saveStartAndGoal(const ompl::geometric::SimpleSetup &ss) {
    // Get the start and goal states
    const ob::State *startState = ss.getProblemDefinition()->getStartState(0);
    const ob::GoalStates *goalState = ss.getProblemDefinition()->getGoal()->as<ob::GoalStates>();

    std::ofstream file("zzzzz_start_goal.csv");

    const double *start_coords = startState->as<ob::RealVectorStateSpace::StateType>()->values;
    // start is first row
    file << start_coords[0] << "," << start_coords[1] << std::endl;

    // goals is second row onward
    int numGoals = goalState->getStateCount();
    printf("\nThere are %d goalstate(s).\n", numGoals);
    for (size_t i = 0; i < numGoals; i++) {
        const double *goal_coords = goalState->getState(i)->as<ob::RealVectorStateSpace::StateType>()->values;
        file << goal_coords[0] << "," << goal_coords[1] << std::endl;
    }
    file.close();
}