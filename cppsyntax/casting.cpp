#include <iostream>
// casting is the process of converting a variable from one type to another.

int main(int argc, char const *argv[]) {

    // TODO static cast
    // it performs a compile-time check and is used for well-defined,
    // non-polymorphic conversions like converting between numeric types,
    // or pointers and references of related types (upcasting or downcasting).
    // syntax -> new_type variable_name = static_cast<new_type>(old_variable);
    int x = 10;
    double y = static_cast<double>(x); // Converts int to double


    // TODO dynamic cast
    // This cast is used for handling polymorphism.
    // It is primarily used to cast pointers or references to base class objects to derived class objects.
    // It checks types at runtime and is useful in situations where you’re dealing with inheritance and want to ensure the cast is valid.

    // syntax -> Derived* d = dynamic_cast<Derived*>(base_pointer);
    class Base {
            virtual void foo() {} // Needs at least one virtual function
    };

    class Derived : public Base {
            // Some code here
    };

    Base *b = new Derived();
    Derived *d = dynamic_cast<Derived *>(b); // Valid cast

    Base *b2 = new Base();
    Derived *d2 = dynamic_cast<Derived *>(b2); // Invalid cast, returns nullptr



    return 0;
}
