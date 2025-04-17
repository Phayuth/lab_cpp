#include <iostream>
#include <ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/geometric/planners/prm/PRM.h>
#include <ompl/geometric/planners/prm/PRMstar.h>

namespace ob = ompl::base;
namespace og = ompl::geometric;

bool isStateValid(const ob::State *state) {
    return true;
}
int main() {

    auto space = std::make_shared<ob::RealVectorStateSpace>(2);
    ob::RealVectorBounds bounds(2);
    bounds.setLow(-2 * M_PI);
    bounds.setHigh(2 * M_PI);
    space->setBounds(bounds);

    og::SimpleSetup ss(space);

    ss.setStateValidityChecker(isStateValid);

    ob::ScopedState<> qs(space);
    qs[0] = 0.0;
    qs[1] = 0.0;
    ob::ScopedState<> qg(space);
    qg[0] = 1.57;
    qg[1] = 1.57;

    ss.setStartAndGoalStates(qs, qg);

    auto planner = std::make_shared<og::PRM>(ss.getSpaceInformation());
    ss.setPlanner(planner);
    planner->constructRoadmap(ob::PlannerTerminationCondition());
    // planner->expandRoadmap(10.0);
    std::cout << "expanding roadmap for 10s" << std::endl;
    ob::PlannerStatus solved = ss.solve(1.0);

    ob::PlannerData data(ss.getSpaceInformation());
    if (solved) {
        std::cout << "Found!" << std::endl;

        ss.getSolutionPath().print(std::cout);
        ss.getPlannerData(data);
        data.printGraphML(std::cout);

    } else {
        std::cout << "No Solution!" << std::endl;
    }
    return 0;
}
