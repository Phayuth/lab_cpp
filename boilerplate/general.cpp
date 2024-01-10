#include <cmath>
#include <cstdio> // printf
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char const *argv[]) {

    printf("There are [%i] arguments passed in.\n", argc-1);
    for (int i = 1; i < argc; i++) // 1st aug is just a file name
    {
        printf("Argument at [%i] is [%f] \n", i, atof(argv[i])); // convert string to float
    }
    return 0;
}