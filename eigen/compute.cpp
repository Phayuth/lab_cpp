#include <Eigen/Dense>
#include <iostream>

Eigen::Vector2d forward(Eigen::Vector2d q) {
    double l1 = 1;
    double l2 = 1;
    return Eigen::Vector2d(l1 * cos(q(0, 0)) + l2 * cos(q(0, 0) + q(1, 0)),
                           l2 * sin(q(0, 0)) + l2 * sin(q(0, 0) + q(1, 0)));
}

Eigen::Matrix<double, 2, 3> f;

int main() {
    std::cout << "-----------------" << "\n";
    Eigen::Vector2d q(0, 0);
    std::cout << "q = " << q << "q size = " << q.size() << "q rows = " << q.rows() << "q cols = " << q.cols() << std::endl;

    std::cout << "-----------------" << "\n";
    auto t = forward(q);
    std::cout << "t = " << t << "t size = " << t.size() << "t rows = " << t.rows() << "t coljs = " << t.cols() << std::endl;

    std::cout << "-----------------" << "\n";
    Eigen::MatrixXd A(3,3), B(3,3);
    A << 0, 1, 3,
         5, 4, 1,
         8, 4, 8;

    B << 1, 5, 1,
         6, 5, 1,
         9, 3, 2;
    std::cout << A << "\n" << B << std::endl;

    std::cout << "-----------------" << "\n";
    std::cout << A + B << std::endl;

    std::cout << "-----------------" << "\n";
    std::cout << A - B << std::endl;

    std::cout << "-----------------" << "\n";
    std::cout << A * B << std::endl; // matrix multiplication not element wise as numpy

    std::cout << "-----------------" << "\n";
    std::cout << A.cwiseProduct(B) << std::endl; // element wise product

    std::cout << "-----------------" << "\n";
    std::cout << -A << std::endl;

    std::cout << "-----------------" << "\n";
    std::cout << 9*A  << std::endl;

    std::cout << "-----------------" << "\n";
    std::cout << A/9 << std::endl;

    std::cout << "-----------------" << "\n";
    std::cout << A.transpose() << std::endl;
    // A = A.transpose(); // ! do NOT do this, wrong
    // A.transposeInPlace();

    std::cout << "-----------------" << "\n";
    std::cout << A.conjugate() << std::endl;

    std::cout << "-----------------" << "\n";
    std::cout << A.adjoint() << std::endl;

    std::cout << "-----------------" << "\n";
    std::cout << A.sum() << " - " << A.prod() << " - " << A.mean() << " - " << A.minCoeff() << " - " << A.maxCoeff() << " - " << A.trace() << std::endl;

    std::cout << "-----------------" << "\n";
    std::ptrdiff_t i, j;
    std::cout << "min :" << A.minCoeff(&i, &j) << "- min row (argmin row):" << i << "- min col (argmin col):" << j << std::endl;

    return 0;
}