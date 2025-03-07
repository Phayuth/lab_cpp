// From code beauty on YT https://www.youtube.com/watch?v=wN0x9eZLix4

#include <iostream>

class Employee { // create class name Employee
    public:      // access modifier. make property in class public instead of private , protected
        std::string Name;
        std::string Company;
        int Age;

        void IntroduceYourself() { // create function
            std::cout << "Name - " << Name << std::endl;
            std::cout << "Company - " << Company << std::endl;
            std::cout << "Age - " << Age << std::endl;
        }
};

int main() {
    Employee employee1; // create an object inherit the class
    employee1.Name = "Phayuth";
    employee1.Company = "DC_Lab";
    employee1.Age = 21;
    employee1.IntroduceYourself();

    Employee employee2;
    employee1.Name = "Johnyuth";
    employee1.Company = "Home";
    employee1.Age = 150;
    employee1.IntroduceYourself();

    return 0;
}