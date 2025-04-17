#include "findaltconfig.h"
#include "sim_planar_rr.h"
#include <fstream>
#include <iostream>
#include <ompl-1.5/ompl/base/goals/GoalStates.h>
#include <ompl-1.5/ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl-1.5/ompl/geometric/SimpleSetup.h>
#include <ompl-1.5/ompl/geometric/planners/rrt/RRT.h>
#include <ompl-1.5/ompl/geometric/planners/rrt/RRTstar.h>
#include <yaml-cpp/yaml.h>

namespace ob = ompl::base;
namespace og = ompl::geometric;

bool isStateValid(const ob::State *state, PlanarRRSIM &sim);
void savePathToFile(const og::PathGeometric &path, const std::string &filename);
void savePlannerData(const ompl::base::PlannerPtr &planner, const ompl::base::SpaceInformationPtr &si, const std::string &filename);
void saveStartAndGoal(const ompl::geometric::SimpleSetup &ss, const std::string &filename);

int main() {
    // Load YAML configuration
    YAML::Node config = YAML::LoadFile("../config/paper_exts_goalset.yaml");

    // Robot setup
    double l1 = config["robot"]["l1"].as<double>();
    double l2 = config["robot"]["l2"].as<double>();
    PlanarRR robot(l1, l2);

    // Simulation environment setup
    std::vector<Rectangle> env;
    for (const auto &rect : config["env"]["rectangles"]) {
        env.push_back(Rectangle(rect[0].as<double>(), rect[1].as<double>(), rect[2].as<double>(), rect[3].as<double>()));
    }
    PlanarRRSIM sim(robot, env);

    // Planning space setup
    auto space = std::make_shared<ob::RealVectorStateSpace>(2);
    ob::RealVectorBounds bounds(2);
    bounds.setLow(-2.0 * M_PI);
    bounds.setHigh(2.0 * M_PI);
    space->setBounds(bounds);
    og::SimpleSetup ss(space);

    // Collision setup
    ss.setStateValidityChecker([&sim](const ob::State *state) {
        return isStateValid(state, sim);
    });

    // Define the start state
    ob::ScopedState<> start(space);
    start[0] = config["qstart"][0].as<double>();
    start[1] = config["qstart"][1].as<double>();
    ss.setStartState(start);

    // Define multiple goal states
    Eigen::RowVectorXd qgoal(2);
    qgoal[0] = config["qgoal"][0].as<double>();
    qgoal[1] = config["qgoal"][1].as<double>();
    Eigen::RowVectorXd qlimit(2);
    qlimit[0] = config["qlimit"][0].as<double>();
    qlimit[1] = config["qlimit"][1].as<double>();
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

    // Planner setup and solve
    auto planner = std::make_shared<og::RRTstar>(ss.getSpaceInformation());
    planner->setRange(config["range"].as<double>());
    planner->setGoalBias(config["bias"].as<double>());
    ss.setPlanner(planner);
    ob::PlannerStatus solved = ss.solve(config["time_limit"].as<double>()); // within a time limit

    if (solved) {
        std::cout << "Found solution:" << std::endl;

        if (config["simplify_solution"].as<bool>()) {

            ss.simplifySolution();
        }

        ss.getSolutionPath().print(std::cout);

        const og::PathGeometric &path = ss.getSolutionPath();
        auto space_information(std::make_shared<ompl::base::SpaceInformation>(space));
        savePathToFile(path, config["path_save_path"].as<std::string>() + ".csv");
        savePlannerData(planner, space_information, config["path_save_planner_data"].as<std::string>() + ".graphml");
        saveStartAndGoal(ss, config["path_save_start_goal"].as<std::string>() + ".csv");
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

void savePlannerData(const ompl::base::PlannerPtr &planner, const ompl::base::SpaceInformationPtr &si, const std::string &filename) {
    ompl::base::PlannerData plannerData(si);
    planner->getPlannerData(plannerData);

    // Save PlannerData to a .graphml file
    std::ofstream file(filename);
    plannerData.printGraphML(file);
    file.close();
}

void saveStartAndGoal(const ompl::geometric::SimpleSetup &ss, const std::string &filename) {
    // Get the start and goal states
    const ob::State *startState = ss.getProblemDefinition()->getStartState(0);
    const ob::GoalStates *goalState = ss.getProblemDefinition()->getGoal()->as<ob::GoalStates>();

    std::ofstream file(filename);

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