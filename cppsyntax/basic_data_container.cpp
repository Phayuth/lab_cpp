#include <array>  // for array, at()
#include <cstdio> // printf
#include <iostream>
#include <string>
#include <tuple> // for get()
#include <unordered_map>
#include <vector>

int main() {
    printf("---------------C-style array---------------------\n");
    float arraySingleDim[3] = {25., 63., 88.};
    for (auto i : arraySingleDim) {
        printf("Get value from c-style array with index are %.2f\n", i);
    }

    float arrayAssignValue[3]; // pre initialize array
    arrayAssignValue[0] = 58.; // assign value to element array
    arrayAssignValue[1] = 48.;
    arrayAssignValue[2] = std::rand();

    int arrayMultipleDim[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("Array elemet [%i][%i] : %i\n", i, j, arrayMultipleDim[i][j]);
        }
    }

    printf("-------------------C++ array--------------------\n");
    std::array<int, 6> ar = {1, 3, 4, 5, 6, 7};
    printf("Get value from c++ class array %i, %i, %i\n",
           ar.at(3),
           ar[3],
           std::get<3>(ar));
    printf("Front and back member function %i, %i\n", ar.front(), ar.back());
    printf("Array Properties : %lu, %lu\n", ar.size(), ar.max_size());

    printf("-----------Equivalent to Python dictionary------\n");
    std::unordered_map<std::string, int> myMap;
    myMap["one"] = 1; // Insert key-value pairs
    myMap["two"] = 2;
    myMap["three"] = 3;
    std::cout << "Value for key 'two': " << myMap["two"]
              << std::endl; // Access values using keys
    for (const auto &pair : myMap) {
        printf("Key: %s, Value: %i\n", pair.first.c_str(), pair.second);
    }

    printf("--------------------Struct----------------------\n");
    struct StructData {
            std::string heroName;
            int id;
            float hp;
            bool isCarry;
    };

    StructData h1;
    h1.id = 1;
    h1.hp = 500.99;
    h1.heroName = "Stan";
    h1.isCarry = true;
    printf("Struct are [%i], [%f], [%s], [%i]",
           h1.id,
           h1.hp,
           h1.heroName.c_str(),
           h1.isCarry);

    printf("--------------------Tuple----------------------\n");
    std::tuple<std::string, std::string, std::string> hero =
        std::make_tuple("Stan", "Carry", "500.99");
    std::cout << "The Hero is " << std::get<0>(hero)
              << std::endl; // access the tuple std::get<index>(variable)
    std::cout << "Hero said " << std::get<1>(hero) << std::endl;
    std::cout << "Hero said " << std::get<2>(hero) << std::endl;

    return 0;
}