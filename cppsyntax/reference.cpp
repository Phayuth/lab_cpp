#include <iostream>
#include <stdio.h>
#include <string>

// A reference variable is a "reference" to an existing variable, and it is created with the & operator
// The & operator used for create a reference variable.
// But it can also be used to get the memory address of a variable;

// References and Pointers give you the ability to manipulate the data in the computer memory
// which can reduce the code and improve the performance.
// The memory address is in hexadecimal form (0x).

void reference() {
    std::string name = "Johnyuth";
    std::string &rname = name; // reference to name
    std::cout << "The original variable name is " << name << std::endl;
    std::cout << "The reference variable rname is " << rname << std::endl;
    std::cout << "The address of the variable " << &rname << std::endl;

    rname = "Johnyuth has now changed";
    std::cout << "The changed variable name is " << name << std::endl;
    std::cout << "The changed reference variable rname is " << rname << std::endl;
}

int &getreference(int &x) {
    std::cout << &x << std::endl;
    return x;
}

int main(int argc, char const *argv[]) {
    reference();

    int a = 1;
    std::cout << &a << std::endl;
    int &b = getreference(a);
    std::cout << &b << std::endl;
    printf("%i", b);

    return 0;
}