#include <iostream>
#include <ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/geometric/planners/rrt/RRT.h>

// Namespace alias for convenience
namespace ob = ompl::base;
namespace og = ompl::geometric;

// Function to check if a state is valid (collision check, etc.)
bool isStateValid(const ob::State *state) {
    // This is where you'd add your custom validity checks, like collisions or joint limits.
    // For now, we assume every state is valid.
    return true;
}

int main() {
    // 1. Define the state space for the 2-joint robot (2D)
    auto space = std::make_shared<ob::RealVectorStateSpace>(2);

    // 2. Set the bounds for the joints (assuming joint limits between -pi and pi)
    ob::RealVectorBounds bounds(2);
    bounds.setLow(-3.14159); // Lower bound for both joints
    bounds.setHigh(3.14159); // Upper bound for both joints
    space->setBounds(bounds);

    // 3. Create a SimpleSetup object, which handles all of the setup steps
    og::SimpleSetup ss(space);

    // 4. Set the state validity checker (here, we assume all states are valid)
    ss.setStateValidityChecker(isStateValid);

    // 5. Define the start and goal states
    ob::ScopedState<> start(space);
    start[0] = 0.0; // First joint angle
    start[1] = 0.0; // Second joint angle

    ob::ScopedState<> goal(space);
    goal[0] = 1.57; // First joint angle (90 degrees)
    goal[1] = 1.57; // Second joint angle (90 degrees)

    ss.setStartAndGoalStates(start, goal);

    // 6. Select the planner (in this case, RRT)
    auto planner = std::make_shared<og::RRT>(ss.getSpaceInformation());
    ss.setPlanner(planner);

    // 7. Attempt to solve the problem within a time limit
    ob::PlannerStatus solved = ss.solve(1.0);

    if (solved) {
        std::cout << "Found solution!" << std::endl;

        // Print the path
        ss.simplifySolution();
        ss.getSolutionPath().print(std::cout);
    } else {
        std::cout << "No solution found." << std::endl;
    }

    return 0;
}
