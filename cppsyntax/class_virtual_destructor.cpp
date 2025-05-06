#include <iostream>
// when delete derived class, we must delete based on the hierarchy
// otherwise, we will have memory leak !!!!!!!!!!!!!!!!!!!!!
// specify virtual to allow polymorphism (dynamically binding) !!!!!!!!!!!!!!

class Animal {
    public:
        // specify virtual to allow polymorphism (dynamically binding)
        // !!!!!!!!!!!!!!
        virtual ~Animal() {
            std::cout << "Animal Destructor" << std::endl;
        }
};

class Walking : public Animal {
    public:
        virtual ~Walking() {
            std::cout << "Walking Destructor" << std::endl;
        }
};

class Dog : public Walking {
    public:
        virtual ~Dog() {
            std::cout << "Dog Destructor" << std::endl;
        }
};

int main(int argc, char const *argv[]) {
    Animal *a = new Dog();
    // when delete dog, we must delete based on the hierarchy
    // delete dog first, then walking, then animal
    // otherwise, we will have memory leak !!!!!!!!!!!!!!!!!!!!!
    delete a;
    return 0;
}