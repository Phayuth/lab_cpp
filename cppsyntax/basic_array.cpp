#include <iostream>
#include <stdio.h>

void create_array1() {
    int scores[5] = {10, 20, 30, 40, 50};
}

void create_array2() {
    int scores[5];
    scores[0] = 10;
    scores[1] = 20;
    scores[2] = 30;
    scores[3] = 40;
    scores[4] = 50;
}

void pointer_array() {
    int balance[5] = {1000, 2, 3, 17, 50};

    int *ptr = &balance[0] + 1; // the address increment using add and substract
    std::cout << *ptr << std::endl;

    // the array address is the first element of the array address
    std::cout << balance << std::endl;
    std::cout << &balance << std::endl;
    std::cout << &balance[0] << std::endl;
    std::cout << "They should be the same." << std::endl;
}

int main() {
    create_array1();
    create_array2();
    pointer_array();
    return 0;
}
