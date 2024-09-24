#ifndef INCLUDE_GUARD_H
#define INCLUDE_GUARD_H
#endif

#define _USE_MATH_DEFINES // use this to call cmath constant value such as pi = M_PI = 3.14
#include <cmath>
#include <iostream>
#include <stdbool.h>
#include <stdio.h>

// variable
int count = 10;   // declare with assignment
int counting{10}; // declare with curly bracket
int counter(10);  // declare with function
float freq = 2 * M_PI / 30;
const int gravity = 9.81; // constant val, cann't change error
double y = 5.36;
char z = 'z';
auto x = 2.0;
std::string q = "ok";
bool w = true;

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

    // ternary condition = if condition is true -> assign option 1, if false -> assign option 2. option 1 and 2 must have the same data type
    auto result = (50 == 50) ? true : false;
    std::cout << result << std::endl;

    // for loop
    for (int i = 0; i < count; ++i) {
        float pose = sin(freq * i);
    }

    // while loop
    int iterator = 0;
    while (iterator < count) {
        std::cout << iterator << std::endl;
        iterator++;
    }

    // do while loop
    int new_iterator = 0;
    do {
        std::cout << new_iterator << std::endl;
        new_iterator++;
    } while (new_iterator < count);

    return 0;
}