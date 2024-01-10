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

// array
int array[3] = {9, 17, 26};
int array_multi_dim[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

// class
class myclass {
    public:
        int myclass_int = 1;
        std::string myclass_str = "Johnyuth";

    private:
        int myclass_int_priv = 4;
        std::string myclass_str_priv = "private_string";
};

// struct
struct mystruct {
        int mystruct_int;
        float mystruct_float;
        std::string mystruct_str;
        bool mystruct_bool;
};

// function return string
std::string region(float pose) {
    if (pose < 0) {
        return "Negative region";
    } else {
        return "Positive region";
    }
}

// function return int
int func_int() {
    return 10;
}

// function return nothing
void enter(unsigned int age) {
    if (age > 25) {
        std::cout << "gg" << std::endl;
    }
}

int main(int argc, char const *argv[]) {
    // struct
    mystruct hero;
    hero.mystruct_int = 1;
    hero.mystruct_float = 500.99;
    hero.mystruct_str = "Flollly";
    hero.mystruct_bool = true;

    // class
    myclass classing;
    std::cout << classing.myclass_int << std::endl;

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
        std::cout << "Step : " << i << " Sin wave is :" << pose << region(pose) << std::endl;
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

    // loop in array
    for (int i = 0; i < (sizeof(array) / sizeof(*array)); ++i) {
        std::cout << array[i] << std::endl;
    }
    for (int i = 0; i < std::size(array); ++i) {
        std::cout << array[i] << std::endl;
    }
    for (auto v : array) {
        std::cout << v << std::endl;
    }

    // references
    double original_val{6};
    double &ref_to_original_val{original_val};

    std::cout << original_val << std::endl;
    std::cout << ref_to_original_val << std::endl;

    return 0;
}