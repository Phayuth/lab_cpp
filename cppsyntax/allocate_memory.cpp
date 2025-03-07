#include <iostream>

int main(int argc, char const *argv[]) {
    { // stack scope
        int a = 10;
        int b = 20;
        int c = a + b;
        std::cout << c << std::endl;
    }

    { // heap scope
        int *a = new int(10); // ask for memory allocation with int value 10 with new keyword
        int *b = new int(20);
        int *c = new int(*a + *b);

        std::cout << *c << std::endl;

        delete a;    // release the memory allocation back to the system to avoid memory leak
        a = nullptr; // set the pointer to null to play safe with dangling pointer
        delete b;
        b = nullptr;
        delete c;
        c = nullptr;
    }
    return 0;
}
