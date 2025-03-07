#include <iostream>
// casting is the process of converting a variable from one type to another.
// transorming a pointer from Base class to Derived class is called downcasting.
// dynamic_cast is used for downcasting at runtime.

class Animal {
    public:
        virtual void live() const {
            printf("Animal is living.\n");
        }

        virtual ~Animal() {
            printf("Animal is destroyed.\n");
        }
};

class Walking : public Animal {
    public:
        void walk() const {
            printf("Animal is walking.\n");
        }
        virtual ~Walking() {
            printf("Walking is destroyed.\n");
        }
};

class Dog : public Walking {
    public:
        void make_sound() const {
            printf("Dog barks.\n");
        }
        virtual ~Dog() {
            printf("Dog is destroyed.\n");
        }
};

// usually, dynamic_cast is made into a function to avoid the need to check the validity of the cast.
void sound(Animal *a) {
    Dog *d = dynamic_cast<Dog *>(a);
    if (d) {
        d->make_sound();
    } else {
        printf("Invalid cast.\n");
    }
}

int main(int argc, char const *argv[]) {
    Animal *a = new Dog();
    // a->make_sound(); compile error, the base class does not have make_sound method.

    // downcasting
    Dog *ptr = dynamic_cast<Dog *>(a);
    if (ptr) {
        ptr->make_sound();
    } else {
        printf("Invalid cast.\n");
    }

    sound(a);

    delete a;
    return 0;
}
