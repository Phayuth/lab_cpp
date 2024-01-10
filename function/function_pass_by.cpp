#include <iostream>
#include <stdio.h>
#include <string>

void pass_by_reference(int &x, int &y) {
    int z = x;
    x = y;
    y = z;
}

int main() {
    int first = 31;
    int secnd = 55;
    std::cout << first << std::endl;
    std::cout << secnd << std::endl;
    pass_by_reference(first, secnd);
    std::cout << first << std::endl;
    std::cout << secnd << std::endl;

    int a = 5;
    int &b = a;
    int *c = &a;

    return 0;
}
