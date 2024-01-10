#include <Eigen/Dense>
#include <iostream>

// Vector with initialized value
Eigen::Vector3d a(0, 1, 2);                // allocated vector with 3 dim with
Eigen::Vector4i b = {1, 3, 2, 3};          // allocated vector with 4 dim with
Eigen::Vector2d c = Eigen::Vector2d(1, 2); // allocated vector with 2 dim with create from contructor

// Vector with uninitialize value
Eigen::VectorXd d(10);                      // dynamic size vector, allocated with abitrary dim
Eigen::VectorXd e(3);

int main() {
    // check eigen library version
    std::cout << "Eigen version: " << EIGEN_WORLD_VERSION << "." << EIGEN_MAJOR_VERSION << "." << EIGEN_MINOR_VERSION << std::endl;

    std::cout << "-----------------" << "\n";
    std::cout << "a : " << a << "\n";
    std::cout << "Row : " << a.rows() << " Cols : " << a.cols() << "\n";

    std::cout << "-----------------" << "\n";
    d << 1.2, 21.2, 23.3, 1.2, 21.2, 23.3, 52.0, 1.2, 21.2, 23.3; // assigning value to vector with << operator
    std::cout << d << std::endl;

    std::cout << "-----------------" << "\n";
    Eigen::RowVector3d aTranspose1 = a;
    Eigen::RowVector3d aTranspose2 = a.transpose();
    auto aTranspose3 = a.transpose();
    std::cout << "aTranspose " << aTranspose3 << std::endl;
    std::cout << "Row : " << aTranspose3.rows() << " Cols : " << aTranspose3.cols() << "\n";

    std::cout << "-----------------" << "\n";
    Eigen::VectorXd m  = Eigen::VectorXd::Random(3);
    std::cout << m << "\n";

    std::cout << "-----------------" << "\n";
    e(0) = 2.3;
    e(1) = 1.4;
    e(2) = 5.1;
    std::cout << e << std::endl;

    std::cout << "-----------------" << "\n";
    Eigen::VectorXd one(5);
    one.setOnes();
    std::cout << one << std::endl;
}