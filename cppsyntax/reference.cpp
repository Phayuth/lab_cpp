#include <iostream>
#include <stdio.h>
#include <string>

// A reference variable is a "reference" to an existing variable, and it is created with the & operator
void sdf() {
    std::string name = "Johnyuth";
    std::string &rname = name; // reference to name
    std::cout << "The original variable name is " << name << std::endl;
    std::cout << "The reference variable rname is " << rname << std::endl;
    std::cout << "The address of the variable " << &rname << std::endl;
}

// return output by function paramter - done by using reference
void function_reference(int &x, int &y) {
    int z = x;
    x = y;
    y = z;
}

void cal_int(int a, int b, int &c) {
    c = a + b;
}

void passbyref() {
    int first = 31;
    int secnd = 55;

    std::cout << first << std::endl;
    std::cout << secnd << std::endl;
    function_reference(first, secnd);
    std::cout << first << std::endl;
    std::cout << secnd << std::endl;

    int a = 10;
    int b = 20;
    int c{};
    cal_int(a, b, c);
    std::cout << c << std::endl;
}

int main(int argc, char const *argv[]) {
    sdf();
    return 0;
}

// The & operator used for create a reference variable.
// But it can also be used to get the memory address of a variable;

// References and Pointers give you the ability to manipulate the data in the computer memory
// which can reduce the code and improve the performance.
// The memory address is in hexadecimal form (0x).