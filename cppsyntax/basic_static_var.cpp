#include <iostream>

// A static local variable inside a function maintains its value between function
// calls. Normally, local variables inside a function are created and destroyed
// with each function call,

// static local variables are initialized only once and persist across multiple
// calls.

void counter() {
    static int count = 0; // Static local variable
    count++;
    std::cout << "Count: " << count << std::endl;
}

class MyClass {
    public:
        static int sharedValue; // Static member variable
};

int MyClass::sharedValue = 0;

int main() {
    counter(); // Output: Count: 1
    counter(); // Output: Count: 2
    counter(); // Output: Count: 3

    MyClass obj1;
    MyClass obj2;
    obj1.sharedValue = 5; // Modify static variable using obj1
    std::cout << "obj1.sharedValue: " << obj1.sharedValue
              << std::endl; // Output: 5
    std::cout << "obj2.sharedValue: " << obj2.sharedValue
              << std::endl; // Output: 5

    obj2.sharedValue = 10; // Modify static variable using obj2
    std::cout << "obj1.sharedValue: " << obj1.sharedValue
              << std::endl; // Output: 10
    std::cout << "obj2.sharedValue: " << obj2.sharedValue
              << std::endl; // Output: 10

    return 0;
}