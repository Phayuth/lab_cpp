#include <cmath>
#include <iostream>

int count = 10;
float freq = 2 * M_PI / 30;

int main(int argc, char const *argv[]) {
    // for loop
    for (int i = 0; i < count; ++i) {
        float pose = sin(freq * i);
    }

    // while loop
    int iterator = 0;
    while (iterator < count) {
        std::cout << iterator << std::endl;
        iterator++;
    }

    // do while loop
    int new_iterator = 0;
    do {
        std::cout << new_iterator << std::endl;
        new_iterator++;
    } while (new_iterator < count);

    return 0;
}