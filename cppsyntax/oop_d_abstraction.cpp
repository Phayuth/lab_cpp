// Abstraction

#include <iostream>

class AbstractEmployee {
        // abstraction : declare a virtual function so that the any class that inherent from this main class will need to implement its own method
        virtual void AskForPromotion() = 0;
};

class Employee : AbstractEmployee {

    private:
        std::string Name;
        std::string Company;
        int Age;

    public:
        void setName(std::string name) {
            Name = name;
        }

        std::string getName() {
            return Name;
        }

        void setCompany(std::string company) {
            Company = company;
        }

        std::string getCompany() {
            return Name;
        }

        void setAge(int age) {
            if (age >= 18)
                Age = age;
        }

        int getAge() {
            return Age;
        }

        Employee(std::string name, std::string company, int age) {
            Name = name;
            Company = company;
            Age = age;
        }

        void IntroduceYourself() {
            std::cout << "Name - " << Name << std::endl;
            std::cout << "Company - " << Company << std::endl;
            std::cout << "Age - " << Age << std::endl;
        }

        void AskForPromotion() {
            if (Age > 18) {
                std::cout << "You will be promoted" << std::endl;
            }
        }
};

int main() {
    Employee employee1("Phayuth", "DC_Lab", 21);
    employee1.IntroduceYourself();

    employee1.setAge(21); // setter
    std::cout << employee1.getName() << " is " << employee1.getAge() << std::endl;

    employee1.AskForPromotion();

    return 0;
}