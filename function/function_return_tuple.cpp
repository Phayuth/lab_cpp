#include <iostream>
#include <tuple>

char hero;
std::string res1;
std::string res2;
std::string name;

// return multiple value from function in tuple form
// std::tuple<datatype, datatype, datatype> name of function(datatype input)
//   code
// return std::make_tuple(value1, value2 , value3), value have to have the exact same datatype as define above
std::tuple<std::string, std::string, std::string> Return_responce(char hero) {
    if (hero == 'T' || hero == 't') {
        res1 = "The self-righteous shall choke on their sanctimony.";
        res2 = "Terror steals across the land.";
        name = "Terrorblade";
        return std::make_tuple(name, res1, res2);
    } else if (hero == 'J' || hero == 'j') {
        res1 = "I bring my blade.";
        res2 = "You have summoned Juggernaut.";
        name = "Juggernaut";
        return std::make_tuple(name, res1, res2);
    } else if (hero == 'A' || hero == 'a') {
        res1 = "I fear no vile sorcery!";
        res2 = "Magic is an abomination.";
        name = "Anti-Mage";
        return std::make_tuple(name, res1, res2);
    } else if (hero == 'M' || hero == 'm') {
        res1 = "None can stand against Sun Wukong.";
        res2 = "Hope they put up a decent fight.";
        name = "Monkey King";
        return std::make_tuple(name, res1, res2);
    } else
        return std::make_tuple("No", "No", "No");
}

int main() {
    auto thehero = Return_responce('T');                              // return data store in 1 variable
    std::cout << "The Hero is " << std::get<0>(thehero) << std::endl; // access the tuple std::get<index>(variable)
    std::cout << "Hero said " << std::get<1>(thehero) << std::endl;
    std::cout << "Hero said " << std::get<2>(thehero) << std::endl;
    std::cin.get();
}