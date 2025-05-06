#include <cstring> // for std::strcmp
#include <iostream>

// template by value
template <typename T> T add(T a, T b) {
    return a + b;
}

// template by reference
template <typename T> T addref(const T &a, const T &b) {
    return a + b;
}

// template specialization (let compiler know not to do the defualt behaviour of
// just copying type.)
template <> std::string add<std::string>(std::string a, std::string b) {
    return "Specialized concatenation: " + a + " " + b;
}

int main(int argc, char const *argv[]) {
    int res;
    res = add(14, 12);
    printf("the result is : %i\n", res);

    // manually template type deduction
    res = add<int>(21, 11);
    printf("the result is : %i\n", res);

    // this can make the compiler avoid error when difference type is used, by
    // implicit conversion
    double d;
    d = add<double>(11, 12);
    printf("the result is : %f\n", d);

    // pass by ref
    int a = 12;
    int b = 42;
    auto c = addref(a, b);
    printf("the result : %i\n", c);

    std::string str1 = "Hello";
    std::string str2 = "World";
    std::string result = add(str1, str2);
    std::cout << result << std::endl;

    return 0;
}
