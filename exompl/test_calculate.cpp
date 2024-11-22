#include "findaltconfig.cpp"
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

    Eigen::RowVectorXd qgoal(2);
    qgoal << -M_PI, M_PI;
    Eigen::RowVectorXd qlimit(2);
    qlimit << 2 * M_PI, 2 * M_PI;
    Eigen::MatrixXd qgoalalt = find_alt_config(qgoal, qlimit);
    printf("\nI found %d alternative goal configurations.\n", qgoalalt.rows());
    printf("\nThey are: \n");

    for (size_t i = 0; i < qgoalalt.rows(); i++) {
        std::cout << qgoalalt.row(i) << std::endl;
    }

    Eigen::ArrayXXd qgoalaltarray = qgoalalt.array();
    // Eigen::ArrayXXd qgoalarray = qbound.replicate(qShifted.rows(), 1);
    Eigen::ArrayXXd qgoalarray = qgoal.replicate(qgoalalt.rows(), 1);

    printf("\nreplicate: \n");
    std::cout << qgoalarray << std::endl;

    Eigen::Array<bool, Eigen::Dynamic, Eigen::Dynamic> equal = (qgoalaltarray == qgoalarray);
    // auto inlimit = (inup && inlw).rowwise().all();

    printf("\nCompare in: \n");
    std::cout << equal << std::endl;
}