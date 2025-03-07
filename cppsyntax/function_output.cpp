#include <iostream>

void output_with_reference(int &x) {
    x = 99;
}

void output_with_pointer(int *x) {
    *x = 100;
}

void output_with_input_const_reference(const int &x, int &y) {
    y = x + 99;
}

double output_with_return(double x) {
    return x + 5.48;
}


int main(int argc, char const *argv[]) {
    int x;
    output_with_reference(x);
    std::cout << "The value is: " << x << std::endl;

    int y;
    output_with_pointer(&y);
    std::cout << "The value is: " << y << std::endl;

    int out;
    output_with_input_const_reference(100, out);
    std::cout << "The value is: " << out << std::endl;

    double z = output_with_return(100.0);
    std::cout << "The value is: " << z << std::endl;
    return 0;
}