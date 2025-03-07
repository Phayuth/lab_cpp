#include <Eigen/Dense>
#include <iostream>
#include <random>
#include <vector>

class Node {
    public:
        Node(double x, double y) : xpose(x), ypose(y) {} // use initializer list for member variables

        double xpose;
        double ypose;
};

class RRTBase {
    public:
        RRTBase(Node xInit, Node xGoal, int maxIteration) : xInit_(xInit), xGoal_(xGoal), maxIter_(maxIteration) {
        }

        Node xInit_;
        Node xGoal_;
        int maxIter_;
        std::vector<Node> tree_node;

        void planning() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<double> dist(0.0, 1.0);

            for (int i = 0; i < maxIter_; ++i) {
                Node x_samp(dist(gen), dist(gen));
                tree_node.push_back(x_samp);
            }
        }
};

int main() {
    Node xInit(0.0, 0.0);
    Node xGoal(1.0, 1.0);
    int maxIteration = 10;
    RRTBase planner(xInit, xGoal, maxIteration);
    planner.planning();
    for (const auto &node : planner.tree_node) {
        std::cout << "Node: (" << node.xpose << ", " << node.ypose << ")" << std::endl;
    }
    return 0;
}