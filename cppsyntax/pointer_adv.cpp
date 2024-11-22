#include <iostream>
#include <memory>

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

int main() {
    // Create a shared_ptr using make_shared
    std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>(42);

    // Access members of MyClass via shared_ptr
    std::cout << "Value: " << ptr->value << "\n";

    // The object is automatically deleted when the shared_ptr goes out of scope
    return 0;
}

// In C++, std::make_shared is a function that creates a std::shared_ptr, a type of smart pointer provided by the C++ Standard Library.
// The std::shared_ptr is a reference-counted smart pointer that automatically manages the lifetime of dynamically allocated objects,
// ensuring that the object is destroyed when the last std::shared_ptr pointing to it is destroyed.

// std::make_shared simplifies the process of creating std::shared_ptr instances and is more efficient than manually creating std::shared_ptr objects.
// It allocates both the object and the control block (the part that tracks the reference count) in a single memory allocation,
// which can improve performance and reduce fragmentation.
