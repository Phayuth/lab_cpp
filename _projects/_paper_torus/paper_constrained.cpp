/*
RRTStar Planning with R2 state space can be on -pi/pi and -2pi/2pi.
*/
#include "sim_planar_rr.h"
#include <fstream>
#include <iostream>
#include <ompl-1.5/ompl/base/goals/GoalState.h>
#include <ompl-1.5/ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl-1.5/ompl/base/spaces/SE2StateSpace.h>
#include <ompl-1.5/ompl/geometric/SimpleSetup.h>
#include <ompl-1.5/ompl/geometric/planners/rrt/RRT.h>
#include <ompl-1.5/ompl/geometric/planners/rrt/RRTstar.h>
#include <yaml-cpp/yaml.h>

namespace ob = ompl::base;
namespace og = ompl::geometric;

bool isStateValid(const ob::State *state, PlanarRRSIM &sim);
void savePathToFile(const og::PathGeometric &path, const std::string &filename);
void savePlannerData(const ompl::base::PlannerPtr &planner,
                     const ompl::base::SpaceInformationPtr &si,
                     const std::string &filename);
void saveStartAndGoal(const ompl::geometric::SimpleSetup &ss,
                      const std::string &filename);

class CartesianGoalRegion : public ob::GoalRegion {
    public:
        CartesianGoalRegion(const ob::SpaceInformationPtr &si, PlanarRR &robot,
                            double x_goal, double y_goal, double tol)
            : ob::GoalRegion(si), robot_(robot), x_goal_(x_goal), y_goal_(y_goal),
              tol_(tol) {
            threshold_ = tol;
        }

        double distanceGoal(const ob::State *state) const override {
            const auto *realState =
                state->as<ob::RealVectorStateSpace::StateType>();
            double theta1 = realState->values[0];
            double theta2 = realState->values[1];
            std::array<double, 2> xy;
            xy = robot_.forward_kinematic(theta1, theta2);
            double dx = xy[0] - x_goal_;
            double dy = xy[1] - y_goal_;
            return std::sqrt(dx * dx + dy * dy);
        }

    private:
        PlanarRR &robot_;
        double x_goal_, y_goal_, tol_;
};

int main() {
    // load YAML configurations
    YAML::Node config = YAML::LoadFile("../config/paper_constrained.yaml");

    // Robot setup
    double l1 = config["robot"]["l1"].as<double>();
    double l2 = config["robot"]["l2"].as<double>();
    PlanarRR robot(l1, l2);

    // Simulation setup
    std::vector<Rectangle> env;
    for (const auto &rect : config["env"]["rectangles"]) {
        env.push_back(Rectangle(rect[0].as<double>(),
                                rect[1].as<double>(),
                                rect[2].as<double>(),
                                rect[3].as<double>()));
    }
    PlanarRRSIM sim(robot, env);

    // Planning space setup
    auto space = std::make_shared<ob::RealVectorStateSpace>(2);
    auto goalspace = std::make_shared<ob::SE2StateSpace>();
    ob::RealVectorBounds bounds(2);
    bounds.setLow(-config["qlimit"][0].as<double>());
    bounds.setHigh(config["qlimit"][1].as<double>());
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
    ss.setStartState(start);

    // Instead of ob::ScopedState goal...
    auto goal_region = std::make_shared<CartesianGoalRegion>(
        ss.getSpaceInformation(),
        robot,
        config["xgoal"].as<double>(),
        config["ygoal"].as<double>(),
        config["goal_tolerance"].as<double>());
    ss.setGoal(goal_region);

    // Planner setup and solved
    // auto planner = std::make_shared<og::RRT>(ss.getSpaceInformation());
    auto planner = std::make_shared<og::RRTstar>(ss.getSpaceInformation());
    planner->setRange(config["range"].as<double>());
    planner->setGoalBias(config["bias"].as<double>());
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
        // saveStartAndGoal(
        //     ss, config["path_save_start_goal"].as<std::string>() + ".csv");
    } else {
        std::cout << "No solution found." << std::endl;
    }

    return 0;
}

bool isStateValid(const ob::State *state, PlanarRRSIM &sim) {
    const ob::RealVectorStateSpace::StateType *realState =
        state->as<ob::RealVectorStateSpace::StateType>();
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
    file << start_coords[0] << "," << start_coords[1] << std::endl;

    const double *goal_coords =
        goalState->getState()->as<ob::RealVectorStateSpace::StateType>()->values;
    file << goal_coords[0] << "," << goal_coords[1] << std::endl;

    file.close();
}