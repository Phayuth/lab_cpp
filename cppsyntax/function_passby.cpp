#include <iostream>
#include <stdio.h>
#include <string>

void pass_by_value(int x) {
    x = 99;
    std::cout << "The value is: " << x << std::endl;
}

void pass_by_reference(int &x, int &y) {
    int z = x;
    x = y;
    y = z;
}

void pass_by_pointer(int *a, int *b, int *c) {
    *c = *a + *b;
}

int main(int argc, char const *argv[]) {
    // pass by value
    pass_by_value(50);
    std::cout << "The value is not changed : " << 50 << std::endl;

    // pass by reference
    int a = 31;
    int b = 55;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    pass_by_reference(a, b);
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    // pass by pointer
    int a = 10;
    int b = 20;
    int c;
    pass_by_pointer(&a, &b, &c);
    std::cout << "The value of c is: " << c << std::endl;
    return 0;
}