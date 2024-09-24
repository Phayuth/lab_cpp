#include <iostream>
#include <stdio.h>
#include <string>

void function_void() {
    std::cout << "The function_full is executed" << std::endl;
}

int calculate_int(int a, int b) {
    int c = a * b;
    return c;
}

float function_default_value(float def = 11.11, int a = 1, int b = 2) {
    float c = def + a + b;
    return c;
}

void function_prototype(); // function prototype on top of main

int main() {

    function_void();
    function_prototype();
    int c = calculate_int(10, 56);
    std::cout << "The calculated value : " << c << std::endl;
    float d = function_default_value();
    std::cout << "The Default value : " << d << std::endl;
    return 0;
}

void function_prototype() {
    std::cout << "The function_prototype is executed" << std::endl;
}