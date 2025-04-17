#include "findaltconfig.h"
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <vector>

double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

// wrap value to pi range
double wrap_to_pi(double q) {
    return fmod(q + M_PI, 2.0 * M_PI) - M_PI;
}

// Function to compute Cartesian product of a vector with itself 'k' times
Eigen::MatrixXd cartesian_product(const std::vector<double> &vec, int k) {
    int n = vec.size();
    int total_combinations = pow(n, k);

    // Result matrix with (n^k) rows and k columns
    Eigen::MatrixXd result(total_combinations, k);

    // Fill the matrix with Cartesian product
    for (int row = 0; row < total_combinations; ++row) {
        int temp = row;
        for (int col = 0; col < k; ++col) {
            result(row, col) = vec[temp % n];
            temp /= n;
        }
    }

    return result;
}

Eigen::MatrixXd find_alt_config(Eigen::RowVectorXd q, Eigen::RowVectorXd qbound) {
    bool filter = true;

    // find cartesian product
    Eigen::RowVectorXd qw = q.unaryExpr(&wrap_to_pi);
    std::vector<double> vec = {-2 * M_PI, 0.0, 2 * M_PI};
    Eigen::MatrixXd cart = cartesian_product(vec, q.cols());
    Eigen::MatrixXd qShifted = cart.rowwise() + q;

    // eliminate with joint limit. check joint limit independently
    // Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> inup = (qShifted.array() < 2 * M_PI);
    // Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> inlw = (qShifted.array() > -2 * M_PI);
    // Perform row-wise comparison using broadcasting with array conversion
    Eigen::ArrayXXd qShiftedarray = qShifted.array();
    Eigen::ArrayXXd qboundarray = qbound.replicate(qShifted.rows(), 1);
    Eigen::Array<bool, Eigen::Dynamic, Eigen::Dynamic> inup = (qShiftedarray < qboundarray);
    Eigen::Array<bool, Eigen::Dynamic, Eigen::Dynamic> inlw = (qShiftedarray > -qboundarray);
    auto inlimit = (inup && inlw).rowwise().all();

    Eigen::MatrixXd qShiftedInLimit(inlimit.count(), qShifted.cols());
    int index = 0;
    for (int i = 0; i < inlimit.rows(); ++i) {
        if (inlimit(i)) {
            qShiftedInLimit.row(index++) = qShifted.row(i);
        }
    }

    printf("\nThe alternative configuration shape is %ld, %ld", qShiftedInLimit.rows(), qShiftedInLimit.cols());

    // TODO filter out the original q
    return qShiftedInLimit;
}

// void test() {
//     Eigen::RowVectorXd q(3);
//     // q << -1.57, -2.3, -1.4, 3.9, 1.57, 0.0;
//     printf("\nq original");
//     q << -1.4, 3.9, 0.0;
//     std::cout << q << std::endl;
//     std::cout << "There are #num and #col - " << q.rows() << " , " << q.cols() << std::endl;

//     printf("\nq wrapped in pi range");
//     Eigen::RowVectorXd qw = q.unaryExpr(&wrap_to_pi);
//     std::cout << std::endl
//               << qw << std::endl;

//     std::vector<double> vec = {-2 * M_PI, 0.0, 2 * M_PI};
//     int k = q.cols();

//     Eigen::MatrixXd cart = cartesian_product(vec, k);
//     std::cout << "\nCartesian Product:\n"
//               << cart << std::endl;

//     Eigen::MatrixXd qShifted = cart.rowwise() + q;
//     std::cout << "\nqShifted:\n"
//               << qShifted << std::endl;

//     // Check if elements are greater than PI
//     Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> inup = (qShifted.array() < 2 * M_PI);
//     Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> inlw = (qShifted.array() > -2 * M_PI);

//     // Output the result
//     std::cout << "\nin up:\n"
//               << inup << std::endl;
//     std::cout << "\nin low:\n"
//               << inlw << std::endl;

//     auto inlimit = (inup && inlw).rowwise().all();

//     std::cout << "\nin limit boolean index" << std::endl;
//     std::cout << inlimit << std::endl;

//     std::cout << "\nJoint value in limit are :" << std::endl;
//     // Preallocate the result matrix based on the number of `true` rows
//     std::cout << "There are true value - " << inlimit.count() << std::endl; // how many true are there ?
//     Eigen::MatrixXd qShiftedInLimit(inlimit.count(), qShifted.cols());

//     // Directly selecting rows by applying mask
//     int index = 0;
//     for (int i = 0; i < inlimit.rows(); ++i) {
//         if (inlimit(i)) {
//             qShiftedInLimit.row(index++) = qShifted.row(i);
//         }
//     }
//     std::cout << qShiftedInLimit << std::endl;
// }