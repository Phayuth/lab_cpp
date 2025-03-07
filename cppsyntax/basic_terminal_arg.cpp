#include <cstdio>
#include <iostream>

int main(int argc, char const *argv[]) {

    printf("There are [%i] arguments passed in.\n", argc - 1);
    printf("The first argument is the program name [%s].\n", argv[0]);
    for (int i = 1; i < argc; i++)
    {
        printf("Argument at [%i] is [%f] \n", i, atof(argv[i])); // convert string to float
    }
    return 0;
}