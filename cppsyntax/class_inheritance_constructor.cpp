#include <iostream>
#include <string>

class Person {
        friend std::ostream &operator<<(std::ostream &out, const Person &person) {
            out << "Person [" << person.firstname << " " << person.lastname << "]";
            return out;
        }

    private:
        std::string firstname{"None"};
        std::string lastname{"None"};

    public:
        Person() {
            printf("Default constructor for Person is called.\n");
        };

        Person(const std::string &firstname, const std::string &lastname) {
            this->firstname = firstname;
            this->lastname = lastname;
            printf("Custom constructor for Person is called.\n");
        };

        ~Person() {};

        std::string get_fn() const {
            return firstname;
        }
        std::string get_ln() const {
            return lastname;
        }

        void set_fn(const std::string &firstname) {
            this->firstname = firstname;
        }
        void set_ln(const std::string &lastname) {
            this->lastname = lastname;
        }
};

class Player : public Person {
        friend std::ostream &operator<<(std::ostream &out, const Player &player) {
            out << "Player : [ game : " << player.game
                << " names : " << player.get_fn() << " " << player.get_ln() << "]";
            return out;
        }

    private:
        std::string game{"None"};

    public:
        Player() {
            printf("Default constructor for Player is called.\n");
        };

        Player(const std::string &firstname, const std::string &lastname,
               const std::string &game)
            : Person(firstname, lastname) {
            this->game = game;
            printf("Custom constructor for Player is called.\n");
        };

        Player(const std::string &game) {
            this->game = game;
        };

        ~Player() {};
};

int main(int argc, char const *argv[]) {
    Player p1;

    Player p2("John", "Wick", "COD");
    return 0;
}
