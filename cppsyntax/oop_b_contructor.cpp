// Contructor

#include <iostream>

class Employee {
    public:
        std::string Name;
        std::string Company;
        int Age;

        void IntroduceYourself() {
            std::cout << "Name - " << Name << std::endl;
            std::cout << "Company - " << Company << std::endl;
            std::cout << "Age - " << Age << std::endl;
        }

        Employee() {} // constructor default empty

        Employee(std::string name, std::string company, int age) { // contructor
            Name = name;
            Company = company;
            Age = age;
        }

        Employee(std::string name, int age) : Name(name), Age(age) { // contructor with initializer
        }
};

int main() {
    Employee employee1("Phayuth", "DC_Lab", 21); // contructor
    employee1.IntroduceYourself();               // invoke the function in class

    Employee employee2 = Employee("Johnyuth", "CNU", 24);
    employee2.IntroduceYourself();

    auto employee3 = Employee("Nobby-", "BCK", 25);
    employee3.IntroduceYourself();

    auto employee4 = Employee("NB-", 25);
    employee4.IntroduceYourself();

    auto employee5 = Employee();
    employee5.IntroduceYourself();

    return 0;
}