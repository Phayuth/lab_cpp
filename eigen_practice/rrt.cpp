#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>
#include <random>

class Node {
public:
    Node(double x, double y) : xpose(x), ypose(y) {} // use initializer list for member variables

    double xpose;
    double ypose;
};

class RRTBase {
public:
    RRTBase(Node x_init, Node x_goal, int max_iteration) :
        x_init_(x_init),
        x_goal_(x_goal),
        max_iter_(max_iteration)
    {}

    Node x_init_;
    Node x_goal_;
    int max_iter_;
    std::vector<Node> tree_node;

    void planning() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        for (int i = 0; i < max_iter_; ++i) {
            Node x_samp(dist(gen), dist(gen));
            tree_node.push_back(x_samp);
        }
    }
};

int main() {
    Node x_init(0.0, 0.0);
    Node x_goal(1.0, 1.0);
    int max_iteration = 10;
    RRTBase planner(x_init, x_goal, max_iteration);
    planner.planning();
    for (const auto& node : planner.tree_node) {
        std::cout << "Node: (" << node.xpose << ", " << node.ypose << ")" << std::endl;
    }
    return 0;
}
