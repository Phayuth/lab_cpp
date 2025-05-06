#include <iostream>

int main(int argc, char const *argv[]) {
    // switch
    const int pen{10};
    const int eraser{2};
    int tool{pen};
    switch (tool) {
    case pen:
        std::cout << "tool is pen" << std::endl;
        break;
    case eraser:
        std::cout << "tool is eraser" << std::endl;
    default:
        std::cout << "No tool" << std::endl;
        break;
    }

    // ternary condition = if condition is true -> assign option 1, if false ->
    // assign option 2. option 1 and 2 must have the same data type
    auto result = (50 == 50) ? true : false;
    std::cout << result << std::endl;

    return 0;
}