// Polymorphism

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

        virtual void work() {
            // declare a general member method.
            // polymorphism : must have the same name of method for every child class,
            // use virtual is importance.
            // it say that if the child class does not have this method, use the default one from super class, otherwise use their own method.
            std::cout << getName() << " is doing general work" << std::endl;
        }
};

class Developer : public Employee {

    private:
        std::string ProgrammingLanguage;

    public:
        Developer(std::string name, std::string company, int age, std::string programmingLanguage) : Employee(name, company, age) {
            ProgrammingLanguage = programmingLanguage;
        }

        std::string getProgLang() {
            return ProgrammingLanguage;
        }

        void work() {
            std::cout << getName() << " is writing " << ProgrammingLanguage << std::endl;
        }
};

class Teacher : public Employee {

    private:
        std::string Subject;

    public:
        Teacher(std::string name, std::string company, int age, std::string subject) : Employee(name, company, age) {
            Subject = subject;
        }

        void work() {
            std::cout << getName() << " is teaching " << Subject << std::endl;
        }
};

int main() {
    Developer dev1("Nobby-", "BCK", 25, "CPP");
    dev1.IntroduceYourself();

    Teacher tec1("NB-", "CU", 26, "Math");
    tec1.IntroduceYourself();

    // polymorphism : create a pointer of type super class that point to address to derived child class
    Employee *e1 = &dev1;
    Employee *t1 = &tec1;

    // polymorphism : then a pointer can directly use method and properties of derived child class.
    // for normal object use "." symbol. for pointer object use "->".
    e1->work();
    t1->work();


    return 0;
}