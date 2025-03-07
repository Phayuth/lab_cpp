#include <iostream>
#include <memory>

void pointer() {
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

class MyClass {
    public:
        MyClass(int x) : value(x) {
            std::cout << "MyClass constructor called with value " << value << "\n";
        }
        ~MyClass() {
            std::cout << "MyClass destructor called\n";
        }
        int value;
};

int *getPointer(int &value) {
    return &value; // returns pointer to the argument
}

int main() {
    pointer();

    // Create a shared_ptr using make_shared
    std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>(42);
    // Access members of MyClass via shared_ptr
    std::cout << "Value: " << ptr->value << "\n";
    // The object is automatically deleted when the shared_ptr goes out of scope

    int x = 10;
    int *ptr = getPointer(x);
    *ptr = 20;

    return 0;
}

// In C++, std::make_shared is a function that creates a std::shared_ptr, a type of smart pointer provided by the C++ Standard Library.
// The std::shared_ptr is a reference-counted smart pointer that automatically manages the lifetime of dynamically allocated objects,
// ensuring that the object is destroyed when the last std::shared_ptr pointing to it is destroyed.

// std::make_shared simplifies the process of creating std::shared_ptr instances and is more efficient than manually creating std::shared_ptr objects.
// It allocates both the object and the control block (the part that tracks the reference count) in a single memory allocation,
// which can improve performance and reduce fragmentation.
