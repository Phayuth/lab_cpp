// Encapsulation = bundle the method and data into class

#include <iostream>

class Employee { // create class name Employee, in private, the data is encapsulated and hidden and only access with public setter and getter

    private: // make property in class private
        std::string Name;
        std::string Company;
        int Age;

    public:
        void setName(std::string name) { // setter
            Name = name;
        }

        std::string getName() { // getter
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

        void IntroduceYourself() { // create function name IntroduceYourself
            std::cout << "Name - " << Name << std::endl;
            std::cout << "Company - " << Company << std::endl;
            std::cout << "Age - " << Age << std::endl;
        }

        Employee(std::string name, std::string company, int age) { // contructor
            Name = name;
            Company = company;
            Age = age;
        }
};

int main() {
    Employee employee1("Phayuth", "DC_Lab", 21); // contructor
    employee1.IntroduceYourself();               // invoke the function in class

    employee1.setAge(21); // setter
    std::cout << employee1.getName() << " is " << employee1.getAge() << std::endl;
}