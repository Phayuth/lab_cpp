#include <Eigen/Dense>
#include <iostream>

int main() {
    // Eigen::VectorXd d(6);
    // d << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

    // Eigen::VectorXd e(6);
    // e << 1.0, 1.0, 1.0, 5.0, 5.0, 5.0;

    // auto t = d - e;
    // std::cout << t;

    // Eigen::MatrixXd m(6,6);

    // std::cout << m;

    // auto y = m.colwise() - e;
    // std::cout << y;

    Eigen::MatrixXf m(2, 4);
    Eigen::VectorXf v(2);

    m << 1, 23, 6, 9,
        3, 11, 7, 2;

    v << 2,
        3;

    Eigen::Index index;
    // find nearest neighbour
    (m.colwise() - v).colwise().squaredNorm().minCoeff(&index);

    std::cout << "Nearest neighbour is column " << index << ":" << std::endl;
    std::cout << m.col(index) << std::endl;
}