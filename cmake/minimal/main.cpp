#include "math_lib.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) // When I delete this section, and call the exe by not passing in
                  // more input it give Segmentation fault (core dumped)
    {
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    std::cout << "Passed in arguments are" << argc << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << "Arguments " << i << " is :" << argv[i] << std::endl;
    }

    double inputValue = atof(argv[1]);
    std::cout << "The square root of " << inputValue << " is "
              << mysqrt(inputValue) << std::endl;
    return 0;
}
