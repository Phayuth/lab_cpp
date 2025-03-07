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
        Person() = default;
        Person(const std::string &firstname, const std::string &lastname) {
            this->firstname = firstname;
            this->lastname = lastname;
        };
        ~Person() {
        };

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
            out << "Player : [ game : " << player.game << " names : " << player.get_fn() << " " << player.get_ln() << "]";
            return out;
        }

    private:
        std::string game{"None"};

    public:
        Player() = default;
        Player(const std::string &firstname, const std::string &lastname, const std::string &game) {
            set_fn(firstname);
            set_ln(lastname);
            this->game = game;
        };
        Player(const std::string &game) {
            this->game = game;
        };

        ~Player() {
        };
};

int main(int argc, char const *argv[]) {
    Player p1("Basketball");
    p1.set_fn("John");
    p1.set_ln("Snow");
    std::cout << "player 1: " << p1 << std::endl;

    p1.set_fn("John1");
    p1.set_ln("Snow2");
    std::cout << "player 1: " << p1 << std::endl;

    Player p2("John", "Wick", "BlackJack");
    std::cout << "player 2: " << p2 << std::endl;

    return 0;
}
