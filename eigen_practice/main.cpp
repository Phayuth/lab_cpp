#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>

Eigen::Vector3d a(0, 1, 2); // create from a function bracket
Eigen::Vector3d b(0, 1, 2);
Eigen::Vector3d c = a.transpose();
Eigen::Vector2d d = Eigen::Vector2d(1, 2); // create from contructor

Eigen::Matrix3d A = Eigen::Matrix3d::Identity();
Eigen::Vector3d Aa = A * a;

Eigen::Vector2d forward(Eigen::Vector2d q)
{
    double l1 = 1;
    double l2 = 1;
    double x = l1 * cos(q(0, 0)) + l2 * cos(q(0, 0) + q(1, 0));
    double y = l2 * sin(q(0, 0)) + l2 * sin(q(0, 0) + q(1, 0));
    return Eigen::Vector2d(x, y);
}

int main()
{
    // std::cout << "Row : " << a.rows() << " Cols : " << a.cols() << std::endl;
    // std::cout << c << std::endl;
    // std::cout << A << std::endl;
    // std::cout << Aa << std::endl;

    Eigen::Vector2d q(0, 0);
    std::cout << forward(q) << std::endl;
}