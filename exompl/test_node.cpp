#include <Eigen/Dense>
#include <iostream>
#include <vector>

class Node {
    public:
        Eigen::ArrayXd config;
        Node *parent;
        std::vector<Node *> child;
        double cost;

        Node(const Eigen::ArrayXd &configArray) : config(configArray), parent(nullptr) {
        }

        double cal_distance(const Node &a, const Node &b) const {
            return (a.config - b.config).matrix().norm();
        }
};

int main() {
    // RootNode
    Eigen::ArrayXd initialConfig(4);
    initialConfig << 0.0, 0.0, 0.0, 0.0;
    Node rootNode(initialConfig);

    // Child
    Eigen::ArrayXd newConfig(4);
    newConfig << 1.0, 0.0, 0.0, 0.0;
    Node anotherNode(newConfig);
    rootNode.child.push_back(&anotherNode);
    anotherNode.parent = &rootNode;


    double distance = rootNode.cal_distance(rootNode, anotherNode);
    std::cout << distance << std::endl;

    return 0;
}
