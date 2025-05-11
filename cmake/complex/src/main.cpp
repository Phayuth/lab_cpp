#include "my_math/math_lib.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }
    double inputValue = atof(argv[1]);
    std::cout << "The square root of " << inputValue << " is "
              << mysqrt(inputValue) << std::endl;
    return 0;
}
