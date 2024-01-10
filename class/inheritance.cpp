// Inheritance

#include <iostream>

class Employee {

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
            if (age >= 18) {
                Age = age;
            } else {
                std::cout << "Age must be larger than threshold" << std::endl;
            };
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
            };
        }
};

class Developer : public Employee { // must declare public to expose method from super class, otherwise it is private by default

    private:
        std::string ProgrammingLanguage;

    public:
        Developer(std::string name, std::string company, int age, std::string programmingLanguage) : Employee(name, company, age) {
            ProgrammingLanguage = programmingLanguage;
        }

        std::string getProgLang(){
            return ProgrammingLanguage;
        }
};

int main() {
    Employee employee1("Phayuth", "DC_Lab", 21);
    employee1.IntroduceYourself();
    employee1.setAge(21);
    std::cout << employee1.getName() << " is " << employee1.getAge() << std::endl;
    employee1.AskForPromotion();


    Developer dev1("Nobby-", "BCK", 25, "CPP");
    dev1.IntroduceYourself();
    std::cout << dev1.getProgLang() << std::endl;

    return 0;
}