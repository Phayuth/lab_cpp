#include <iostream>
#include <string>

class Animal {
    public:
        std::string name;

        Animal(std::string &name) : name(name) {};

        virtual void sound() const = 0;

        ~Animal() {};
};

class Walking : public Animal {
    public:
        Walking(std::string &name) : Animal(name) {};

        virtual void sound() const override {
            std::cout << "Walking animal [" << name << "] is making sound." << std::endl;
        };
        virtual void walk() const {
            std::cout << "Walking animal [" << name << "] is walking." << std::endl;
        };

        ~Walking() {};
};

class Flying : public Animal {
    public:
        Flying(std::string &name) : Animal(name) {};

        virtual void sound() const override {
            std::cout << "Flying animal [" << name << "] is making sound." << std::endl;
        };

        virtual void fly() const {
            std::cout << "Flying animal [" << name << "] is flying." << std::endl;
        };

        ~Flying() {};
};

class Dog : public Walking {
    public:
        Dog(std::string &name) : Walking(name) {};
        virtual void sound() const override {
            std::cout << "Dog [" << name << "] is barking." << std::endl;
        };
        virtual void walk() const {
            std::cout << "Dog [" << name << "] is walking with 4 feet." << std::endl;
        };
        ~Dog() {};
};

class Cat : public Walking {
    public:
        Cat(std::string &name) : Walking(name) {};
        virtual void sound() const override {
            std::cout << "Cat [" << name << "] is meowing." << std::endl;
        };
        virtual void walk() const {
            std::cout << "Cat [" << name << "] is walking with 4 feet." << std::endl;
        };
        ~Cat() {};
};

class Crow : public Flying {
    public:
        Crow(std::string &name) : Flying(name) {};
        virtual void sound() const override {
            std::cout << "Crow [" << name << "] is cawing." << std::endl;
        };
        virtual void fly() const {
            std::cout << "Crow [" << name << "] is flying with 2 wings." << std::endl;
        };
        ~Crow() {};
};

class Chicken : public Flying {
    public:
        Chicken(std::string &name) : Flying(name) {};
        virtual void sound() const override {
            std::cout << "Chicken [" << name << "] is clucking." << std::endl;
        };
        virtual void fly() const {
            std::cout << "Chicken [" << name << "] is flying with 2 wings." << std::endl;
        };
        ~Chicken() {};
};

int main(int argc, char const *argv[]) {
    std::string dog_name = "Doggy";
    Dog dog(dog_name);
    dog.sound();

    std::string cat_name = "Kitty";
    Cat cat(cat_name);
    cat.sound();

    std::string crow_name = "Crowy";
    Crow crow(crow_name);
    crow.sound();

    std::string chicken_name = "Chicky";
    Chicken chicken(chicken_name);
    chicken.sound();

    Animal *animal_ptr[] = {&dog, &cat, &crow, &chicken};
    for (auto &animal : animal_ptr) {
        animal->sound();
    }

    Walking *walking_ptr[] = {&dog, &cat};
    for (auto &walking : walking_ptr) {
        walking->sound();
        walking->walk();
    }

    Flying *flying_ptr[] = {&crow, &chicken};
    for (auto &flying : flying_ptr) {
        flying->sound();
        flying->fly();
    }

    return 0;
}