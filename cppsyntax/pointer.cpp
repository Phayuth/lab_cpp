#include <iostream>
#include <stdio.h>

// basic pointer
void pointer_tutorial() {
    // &variable = to get the address of the variable
    // *address = to get the value inside of address

    std::string name = "Johnyuth"; // name
    std::string *pname = &name;    // a pointer store the memory address of the reference variable "name"

    std::cout << "Original Value of name : " << name << std::endl; // create original variable
    std::cout << "Original Adrs of name : " << &name << std::endl; // print out the memory address of name

    std::cout << "Pointer Value : " << pname << std::endl;
    std::cout << "Pointer Devalue : " << *pname << std::endl; // dereference, asterisk *pointer_variable

    *pname = "Johnyuth has now changed"; // change the value of the pointer
    std::cout << "Changed value of the pointer : " << *pname << std::endl;
    std::cout << "Changed value of the Original : " << name << std::endl;
}

// function to generate and return random numbers
int *getRandom() {
    srand((unsigned)time(NULL)); // set the seed
    static int r[3];
    r[0] = rand();
    r[1] = rand();
    r[2] = rand();

    for (int i = 0; i < 3; ++i) {
        r[i] = rand();
        std::cout << r[i] << std::endl;
    }
    return r;
}

// pass array pointer in
double getAverage(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    double avg = double(sum) / size;
    return avg;
}

void test_getAverage() {
    int balance[5] = {1000, 2, 3, 17, 50};
    double avg = getAverage(balance, 5);
    std::cout << "Average value is: " << avg << std::endl;
}

int main() {
    pointer_tutorial();

    int *p; // a pointer to an int.
    p = getRandom();
    int a = *(p + 0);
    int b = *(p + 1);
    std::cout << "First value is :" << a << std::endl;
    std::cout << "Second value is :" << b << std::endl;

    // test_getAverage();
    return 0;
}