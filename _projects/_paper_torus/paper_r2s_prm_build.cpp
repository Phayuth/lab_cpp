#include "findaltconfig.h"
#include "sim_planar_rr.h"
#include <fstream>
#include <iostream>
#include <ompl-1.5/ompl/base/PlannerDataStorage.h>
#include <ompl-1.5/ompl/base/PlannerTerminationCondition.h>
#include <ompl-1.5/ompl/base/goals/GoalStates.h>
#include <ompl-1.5/ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl-1.5/ompl/geometric/SimpleSetup.h>
#include <ompl/geometric/planners/prm/PRM.h>
#include <ompl/geometric/planners/prm/PRMstar.h>
#include <yaml-cpp/yaml.h>

namespace ob = ompl::base;
namespace og = ompl::geometric;

bool isStateValid(const ob::State *state, PlanarRRSIM &sim);

void savePlannerData(const ompl::base::PlannerPtr &planner,
                     const ompl::base::SpaceInformationPtr &si,
                     const std::string &filename);

void savePlannerStorage(ob::PlannerDataStorage &datastorage, ob::PlannerData &data,
                        std::string &filename);
void loadPlannerStoarge(ob::PlannerDataStorage &datastorage, ob::PlannerData &data,
                        std::string &filename);

int main() {
    // Load YAML
    YAML::Node config = YAML::LoadFile("../config/paper_r2s_prm_build.yaml");

    // Robot setup
    double l1 = config["robot"]["l1"].as<double>();
    double l2 = config["robot"]["l2"].as<double>();
    PlanarRR robot(l1, l2);

    // Simulation environment setup
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
    ob::RealVectorBounds bounds(2);
    bounds.setLow(-config["qlimit"][0].as<double>());
    bounds.setHigh(config["qlimit"][1].as<double>());
    space->setBounds(bounds);
    og::SimpleSetup ss(space);

    // Collision setup
    ss.setStateValidityChecker(
        [&sim](const ob::State *state) { return isStateValid(state, sim); });

    // start and goal states
    ob::ScopedState<> start(space);
    start[0] = config["qstart"][0].as<double>();
    start[1] = config["qstart"][1].as<double>();
    ob::ScopedState<> goal(space);
    goal[0] = config["qgoal"][0].as<double>();
    goal[1] = config["qgoal"][1].as<double>();
    ss.setStartAndGoalStates(start, goal);

    // Planner setup and solve
    auto planner = std::make_shared<og::PRM>(ss.getSpaceInformation());
    ss.setPlanner(planner);
    ob::PlannerStatus solved = ss.solve(config["time_limit"].as<double>());

    // storage
    ob::PlannerDataStorage datastorage;

    ob::PlannerData data(ss.getSpaceInformation());
    ss.getPlannerData(data);

    // save to graphml
    std::ofstream file("saved_planner.graphml");
    data.printGraphML(file);
    file.close();

    // save to boost graph
    std::string prm_data_name = "prm_data";
    savePlannerStorage(datastorage, data, prm_data_name);
    return 0;
}

bool isStateValid(const ob::State *state, PlanarRRSIM &sim) {
    const ob::RealVectorStateSpace::StateType *realState =
        state->as<ob::RealVectorStateSpace::StateType>();
    double theta1 = realState->values[0];
    double theta2 = realState->values[1];
    bool c = sim.check_collision(theta1, theta2);
    return !c;
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

void savePlannerStorage(ob::PlannerDataStorage &datastorage, ob::PlannerData &data,
                        std::string &filename) {
    datastorage.store(data, filename.c_str());
}

void loadPlannerStoarge(ob::PlannerDataStorage &datastorage, ob::PlannerData &data,
                        std::string &filename) {
    datastorage.load(filename.c_str(), data);
}
