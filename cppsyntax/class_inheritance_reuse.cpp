#include <iostream>
#include <string>
// resue the constructor of the base class in the derived class

class Person {
        friend std::ostream &operator<<(std::ostream &out, const Person &person) {
            out << "Person [" << person.firstname << " " << person.lastname << "]";
            return out;
        }

    public:
        std::string firstname{"None"};
        std::string lastname{"None"};
        std::string job{"Jobless"};

        Person() {};

        Person(const std::string &firstname, const std::string &lastname) {
            this->firstname = firstname;
            this->lastname = lastname;
        };

        ~Person() {};
};

class Player : public Person {
        friend std::ostream &operator<<(std::ostream &out, const Player &player) {
            out << "Player [" << player.firstname << " " << player.lastname << "]";
            return out;
        }

    public:
        std::string job{"Player"};

        Player() {};

        // reuse the constructor of the base class here !!!!!!!!
        Player(const std::string &firstname, const std::string &lastname)
            : Person(firstname, lastname) {};

        // ~Player() {
        // };
};

int main(int argc, char const *argv[]) {
    Person p1;
    printf("Person : %s %s, %s\n",
           p1.firstname.c_str(),
           p1.lastname.c_str(),
           p1.job.c_str());

    Player p2("John", "Wick");
    printf("Player : %s %s, %s\n",
           p2.firstname.c_str(),
           p2.lastname.c_str(),
           p2.job.c_str());
    printf("Player Person : %s %s, %s\n",
           p2.Person::firstname.c_str(),
           p2.Person::lastname.c_str(),
           p2.Person::job.c_str());

    return 0;
}
