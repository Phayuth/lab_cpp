#include "robot_collision.cpp"
#include "robot_kinematic.cpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class PlanarRRSIM {
    public:
        PlanarRR robot;
        std::vector<Rectangle> env;

        PlanarRRSIM(const PlanarRR &robot, const std::vector<Rectangle> &env);
        ~PlanarRRSIM();

        bool check_collision(double theta1, double theta2);
};

PlanarRRSIM::PlanarRRSIM(const PlanarRR &robot, const std::vector<Rectangle> &env) : robot(robot), env(env) {
}

PlanarRRSIM::~PlanarRRSIM() {
}

bool PlanarRRSIM::check_collision(double theta1, double theta2) {
    // constuct line from link
    std::array<double, 6> linkpose = robot.forward_link(theta1, theta2);
    std::vector<Line> links;
    links.push_back(Line(linkpose[0], linkpose[1], linkpose[2], linkpose[3]));
    links.push_back(Line(linkpose[2], linkpose[3], linkpose[4], linkpose[5]));

    // loop through env(rectangle) and line for collision
    for (size_t i = 0; i < env.size(); i++) {
        for (size_t j = 0; j < links.size(); j++) {
            if (check_link_v_rectangle(links[j], env[i])) {
                return true;
            }
        }
    }
    return false;
}

// int main() {
//     double l1 = 2.0;
//     double l2 = 2.0;
//     PlanarRR robot(l1, l2);

//     std::vector<Rectangle> env;
//     env.push_back(Rectangle(-2.75, 1.0, 2.0, 1.0));
//     env.push_back(Rectangle(1.5, 2.0, 2.0, 1.0));

//     PlanarRRSIM sim(robot, env);

//     double theta1 = 0.0;
//     double theta2 = 0.0;

//     bool c = sim.check_collision(theta1, theta2);
//     printf("The collision is %d \n", c);

//     return 0;
// }
