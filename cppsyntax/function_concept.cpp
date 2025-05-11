#include <concepts>
#include <iostream>

template <typename T>
    requires std::integral<T> // constraint on template to satisfy
T add(T a, T b) {
    return a + b;
}

int main(int argc, char const *argv[]) {
    int res;
    res = add(14, 12);
    printf("the result is : %i\n", res);

    // manually template type deduction
    res = add<int>(21, 11);
    printf("the result is : %i\n", res);

    return 0;
}
