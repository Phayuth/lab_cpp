#include <Eigen/Dense>
#include <iostream>

// Matrix
Eigen::Matrix3d A = Eigen::Matrix3d::Identity();
Eigen::Matrix<double, 2, 3> B;
Eigen::MatrixXd C(3, 3);
// Eigen::Matrix2d D = {{1,1},{2,2}}; pre init coeff is not available for matrix

int main() {
    // check eigen library version
    std::cout << "Eigen version: " << EIGEN_WORLD_VERSION << "." << EIGEN_MAJOR_VERSION << "." << EIGEN_MINOR_VERSION << std::endl;

    // Matrix
    std::cout << "-----------------" << "\n";
    std::cout << "A " << A << std::endl;

    std::cout << "-----------------" << "\n";
    B << 2, 3, 4,
        5, 6, 7;
    std::cout << B << std::endl;
    std::cout << B * 2 << std::endl;
    std::cout << B.cwiseProduct(B * 2) << std::endl;

    std::cout << "-----------------" << "\n";
    C << 2, 3, 4,
        5, 6, 7,
        8, 9, 1;
    std::cout << C << std::endl;
}