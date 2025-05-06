#include <iostream>
#include <string>
// copy constructor is used to copy the data from one object to another object with
// the same class like a clone.

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

        Person(const Person &p) : firstname(p.firstname), lastname(p.lastname) {
            printf("Person Copy Constructor is called.\n");
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

        void print_info() {
            printf("%s, %s", firstname.c_str(), lastname.c_str());
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

        // Player(const Player& pl) : game(pl.game){
        //     printf("This is wrong. we lost data to initialize Person first.");
        // };

        // Player(const Player& pl) : Person(pl.get_fn(), pl.get_ln()),
        // game(pl.game){
        //     printf("This is working but not efficient. It copy data and we hate
        //     copying data in CPP.");
        // };

        // copy constructor is here !!!!!!!!!!!!!!!!!!
        Player(const Player &pl) : Person(pl), game(pl.game) {
            printf("This will use the copy constructor from the Person class");
            printf("Great! The compiler is smart enough by strip-off data from "
                   "player source to initialize the person.\n");
        };

        Player(const std::string &game) {
            this->game = game;
        };

        ~Player() {};
};

int main(int argc, char const *argv[]) {
    Player p1("John", "Wick", "COD");
    p1.print_info();

    // copy constructor
    Player p2(p1);
    p2.print_info();

    return 0;
}
