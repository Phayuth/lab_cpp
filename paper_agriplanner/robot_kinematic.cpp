#include <array>
#include <cmath>
#include <stdio.h>

class PlanarRR {
    private:
        double link1;
        double link2;

    public:
        PlanarRR(double link1, double link2);
        ~PlanarRR();

        std::array<double, 2> forward_kinematic(double theta1, double theta2);
        std::array<double, 6> forward_link(double theta1, double theta2);
};

PlanarRR::PlanarRR(double link1, double link2) {
    this->link1 = link1;
    this->link2 = link2;
}

PlanarRR::~PlanarRR() {
}

std::array<double, 2> PlanarRR::forward_kinematic(double theta1, double theta2) {
    double x = this->link1 * cos(theta1) + this->link2 * cos(theta1 + theta2);
    double y = this->link1 * sin(theta1) + this->link2 * sin(theta1 + theta2);

    std::array<double, 2> xy = {x, y};

    return xy;
}

std::array<double, 6> PlanarRR::forward_link(double theta1, double theta2) {
    double elbowx = this->link1 * cos(theta1);
    double elbowy = this->link1 * sin(theta1);

    double eex = this->link1 * cos(theta1) + this->link2 * cos(theta1 + theta2);
    double eey = this->link1 * sin(theta1) + this->link2 * sin(theta1 + theta2);

    std::array<double, 6> bee = {0.0, 0.0, elbowx, elbowy, eex, eey};

    return bee;
}

// int main(int argc, char const *argv[]) {
//     double l1 = 2.0;
//     double l2 = 2.0;

//     PlanarRR robot(l1, l2);

//     double theta1 = 0.0;
//     double theta2 = 0.0;

//     printf("------forward kinematic------\n");
//     std::array<double, 2> xy = robot.forward_kinematic(theta1, theta2);
//     for (size_t i = 0; i < xy.size(); i++) {
//         printf("%f, ", xy[i]);
//     }

//     printf("\n");
//     printf("------forward link------\n");
//     std::array<double, 6> bee = robot.forward_link(theta1, theta2);
//     for (size_t i = 0; i < bee.size(); i++) {
//         printf("%f, ", bee[i]);
//     }
//     printf("\n");

//     return 0;
// }
