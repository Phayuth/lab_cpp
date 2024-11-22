#include <iostream>
#include <stdio.h>

// pointer array address 1
void create_new_array_from_old() {
    int arry[5] = {10, 20, 30, 40, 50};
    int *arry2[5];

    for (int i = 0; i < 5; ++i) {
        arry2[i] = &arry[i];
    }

    for (int i = 0; i < 5; ++i) {
        std::cout << *arry2[i] << std::endl;
    }
}

// pointer array address 2
void pointer_array2() {
    int balance[5] = {1000, 2, 3, 17, 50};

    int *ptr = &balance[0] + 1; // the address increment using add and substract
    std::cout << *ptr << std::endl;

    // the array address is the first element of the array address
    // all the code below print the address of the array all the same
    std::cout << balance << std::endl;
    std::cout << &balance << std::endl;
    std::cout << &balance[0] << std::endl;
}

int main() {
    create_new_array_from_old();
    pointer_array2();
    return 0;
}
