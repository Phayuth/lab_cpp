/*
RRTStar Planning with R2 state space
*/
#include "sim_planar_6r.h"
#include <fstream>
#include <iostream>
#include <ompl-1.5/ompl/base/goals/GoalState.h>
#include <ompl-1.5/ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl-1.5/ompl/geometric/SimpleSetup.h>
#include <ompl-1.5/ompl/geometric/planners/rrt/RRTstar.h>
#include <yaml-cpp/yaml.h>

namespace ob = ompl::base;
namespace og = ompl::geometric;

bool isStateValid(const ob::State *state, Planar6RSIM &sim);
void savePathToFile(const og::PathGeometric &path, const std::string &filename);
void savePlannerData(const ompl::base::PlannerPtr &planner,
                     const ompl::base::SpaceInformationPtr &si,
                     const std::string &filename);
void saveStartAndGoal(const ompl::geometric::SimpleSetup &ss,
                      const std::string &filename);

int main() {
    // load YAML configurations
    YAML::Node config = YAML::LoadFile("../config/paper_r6s.yaml");

    // Robot setup
    double l1 = config["robot"]["l1"].as<double>();
    double l2 = config["robot"]["l2"].as<double>();
    double l3 = config["robot"]["l3"].as<double>();
    double l4 = config["robot"]["l4"].as<double>();
    double l5 = config["robot"]["l5"].as<double>();
    double l6 = config["robot"]["l6"].as<double>();
    Planar6R robot(l1, l2, l3, l4, l5, l6);

    // Simulation setup
    std::vector<Rectangle> env;
    for (const auto &rect : config["env"]["rectangles"]) {
        env.push_back(Rectangle(rect[0].as<double>(),
                                rect[1].as<double>(),
                                rect[2].as<double>(),
                                rect[3].as<double>()));
    }
    Planar6RSIM sim(robot, env);

    // Planning space setup
    auto space = std::make_shared<ob::RealVectorStateSpace>(6);
    ob::RealVectorBounds bounds(6);
    for (int i = 0; i < 6; ++i) {
        bounds.setLow(i, -config["bounds"][i].as<double>());
        bounds.setHigh(i, config["bounds"][i].as<double>());
    }
    space->setBounds(bounds);
    og::SimpleSetup ss(space);

    // Collision setup. Set the state validity checker using a lambda to pass
    // 'sim' to 'isStateValid'
    ss.setStateValidityChecker(
        [&sim](const ob::State *state) { return isStateValid(state, sim); });

    // start and goal states
    ob::ScopedState<> start(space);
    start[0] = config["qstart"][0].as<double>();
    start[1] = config["qstart"][1].as<double>();
    start[2] = config["qstart"][2].as<double>();
    start[3] = config["qstart"][3].as<double>();
    start[4] = config["qstart"][4].as<double>();
    start[5] = config["qstart"][5].as<double>();
    ob::ScopedState<> goal(space);
    goal[0] = config["qgoal"][0].as<double>();
    goal[1] = config["qgoal"][1].as<double>();
    goal[2] = config["qgoal"][2].as<double>();
    goal[3] = config["qgoal"][3].as<double>();
    goal[4] = config["qgoal"][4].as<double>();
    goal[5] = config["qgoal"][5].as<double>();
    ss.setStartAndGoalStates(start, goal);

    // Planner setup and solved
    // auto planner = std::make_shared<og::RRT>(ss.getSpaceInformation());
    auto planner = std::make_shared<og::RRTstar>(ss.getSpaceInformation());
    planner->setRange(0.3);
    planner->setGoalBias(0.05);
    ss.setPlanner(planner);

    ob::PlannerStatus solved =
        ss.solve(config["time_limit"].as<double>()); // within a time limit

    if (solved) {
        std::cout << "Found solution!" << std::endl;

        if (config["simplify_solution"].as<bool>()) {
            ss.simplifySolution();
        }

        ss.getSolutionPath().print(std::cout);

        const og::PathGeometric &path = ss.getSolutionPath();
        auto space_information(
            std::make_shared<ompl::base::SpaceInformation>(space));
        savePathToFile(path, config["path_save_path"].as<std::string>() + ".csv");
        savePlannerData(planner,
                        space_information,
                        config["path_save_planner_data"].as<std::string>() +
                            ".graphml");
        saveStartAndGoal(
            ss, config["path_save_start_goal"].as<std::string>() + ".csv");
    } else {
        std::cout << "No solution found." << std::endl;
    }

    return 0;
}

bool isStateValid(const ob::State *state, Planar6RSIM &sim) {
    const ob::RealVectorStateSpace::StateType *realState =
        state->as<ob::RealVectorStateSpace::StateType>();
    double theta1 = realState->values[0];
    double theta2 = realState->values[1];
    double theta3 = realState->values[2];
    double theta4 = realState->values[3];
    double theta5 = realState->values[4];
    double theta6 = realState->values[5];
    bool c = sim.check_collision(theta1, theta2, theta3, theta4, theta5, theta6);
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

void savePlannerData(const ompl::base::PlannerPtr &planner,
                     const ompl::base::SpaceInformationPtr &si,
                     const std::string &filename) {
    ompl::base::PlannerData plannerData(si);
    planner->getPlannerData(plannerData);

    // Save PlannerData to a .graphml file
    std::ofstream file(filename);
    plannerData.printGraphML(file);
    file.close();
}

void saveStartAndGoal(const ompl::geometric::SimpleSetup &ss,
                      const std::string &filename) {
    // Get the start and goal states
    const ob::State *startState = ss.getProblemDefinition()->getStartState(0);
    const ob::GoalState *goalState =
        ss.getProblemDefinition()->getGoal()->as<ob::GoalState>();

    std::ofstream file(filename);

    const double *start_coords =
        startState->as<ob::RealVectorStateSpace::StateType>()->values;
    file << start_coords[0] << "," << start_coords[1] << start_coords[2] << ","
         << start_coords[3] << "," << start_coords[4] << "," << start_coords[5]
         << std::endl;

    const double *goal_coords =
        goalState->getState()->as<ob::RealVectorStateSpace::StateType>()->values;
    file << goal_coords[0] << "," << goal_coords[1] << "," << goal_coords[2] << ","
         << goal_coords[3] << "," << goal_coords[4] << "," << goal_coords[5]
         << std::endl;

    file.close();
}
