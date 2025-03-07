#include <iostream>

int max(int x, int y) {
    std::cout << "The int max function is called." << std::endl;
    return (x > y) ? x : y;
}

double max(double x, double y) {
    std::cout << "The double max function is called." << std::endl;
    return (x > y) ? x : y;
}

int main(int argc, char const *argv[]) {
    int a = 10;
    int b = 20;
    std::cout << "The max value is: " << max(a, b) << std::endl;

    double c = 10.5;
    double d = 20.5;
    std::cout << "The max value is: " << max(c, d) << std::endl;
    return 0;
}
