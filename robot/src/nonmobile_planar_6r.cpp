#include "nonmobile_planar_6r.h"
#include <array>
#include <cmath>

Planar6R::Planar6R(double link1, double link2, double link3, double link4,
                   double link5, double link6) {
    this->link1 = link1;
    this->link2 = link2;
    this->link3 = link3;
    this->link4 = link4;
    this->link5 = link5;
    this->link6 = link6;
}

Planar6R::~Planar6R() {
}

std::array<double, 3> Planar6R::forward_kinematic(double theta1, double theta2,
                                                  double theta3, double theta4,
                                                  double theta5, double theta6) {
    double x = link1 * cos(theta1) +
               link2 * cos(theta1 + theta2) +
               link3 * cos(theta1 + theta2 + theta3) +
               link4 * cos(theta1 + theta2 + theta3 + theta4) +
               link5 * cos(theta1 + theta2 + theta3 + theta4 + theta5) +
               link6 * cos(theta1 + theta2 + theta3 + theta4 + theta5 + theta6);

    double y = link1 * sin(theta1) +
               link2 * sin(theta1 + theta2) +
               link3 * sin(theta1 + theta2 + theta3) +
               link4 * sin(theta1 + theta2 + theta3 + theta4) +
               link5 * sin(theta1 + theta2 + theta3 + theta4 + theta5) +
               link6 * sin(theta1 + theta2 + theta3 + theta4 + theta5 + theta6);

    double p = theta1 + theta2 + theta3 + theta4 + theta5 + theta6;

    std::array<double, 3> xyp = {x, y, p};
    return xyp;
}

std::array<double, 14> Planar6R::forward_link(double theta1, double theta2,
                                              double theta3, double theta4,
                                              double theta5, double theta6) {
    double x1 = link1 * cos(theta1);
    double y1 = link1 * sin(theta1);

    double x2 = x1 + link2 * cos(theta1 + theta2);
    double y2 = y1 + link2 * sin(theta1 + theta2);

    double x3 = x2 + link3 * cos(theta1 + theta2 + theta3);
    double y3 = y2 + link3 * sin(theta1 + theta2 + theta3);

    double x4 = x3 + link4 * cos(theta1 + theta2 + theta3 + theta4);
    double y4 = y3 + link4 * sin(theta1 + theta2 + theta3 + theta4);

    double x5 = x4 + link5 * cos(theta1 + theta2 + theta3 + theta4 + theta5);
    double y5 = y4 + link5 * sin(theta1 + theta2 + theta3 + theta4 + theta5);

    double x6 = x5 + link6 * cos(theta1 + theta2 + theta3 + theta4 + theta5 + theta6);
    double y6 = y5 + link6 * sin(theta1 + theta2 + theta3 + theta4 + theta5 + theta6);

    std::array<double, 14> bee = {0.0, 0.0, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6};
    return bee;
}
