#include <cstdio>
#include <iostream>

template <typename T>
void find_val(T a, T b, T &res) {
    res = a + b * a + b;
}

int main(int argc, char const *argv[]) {
    int res;
    find_val(14, 12, res);
    printf("the result is : %i", res);
    return 0;
}
