#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>

class Node
{
public:
    Node(double x, double y) // class constructor, maybe in poython is __init__(self, x, y)
    {
        xpose = x;
        ypose = y;
    }
    double xpose; // class variable, maybe in python it is self.xpose
    double ypose;

};

double cal_distance(Node a, Node b)
{
    return sqrt((b.xpose - a.xpose) * (b.xpose - a.xpose) + (b.ypose - a.ypose) * (b.ypose - a.ypose));
}

int main()
{   
    Node a(2.2, 5.7);
    Node b(0.0, 8.4);
    std::cout << a.xpose << std::endl;
    std::cout << cal_distance(a, b) << std::endl;

    std::vector<Node> myVector; // create a vector with type Node
    for (int i = 0; i < 10; ++i)
    {
        myVector.push_back(a);
        myVector.push_back(b);
    }
    std::cout << "Size of Array: " << myVector.size() << std::endl;
    std::cout << "Value of object 2: " << myVector[1].xpose << std::endl;
}