#include <iostream>

// lamda function signature
// [capture list](paramters)->return type{function body};

auto lamdafunc = []() { std::cout << "hello!" << std::endl; };

int main(int argc, char const *argv[]) {
    lamdafunc();

    // lamda with paramters and call it directly
    [](double a, double b) { std::cout << (a + b) << std::endl; }(1.2, 1.4);

    // lamda return something
    auto result = [](double a, double b) { return (a + b); }(1.2, .2);
    std::cout << result << std::endl;

    // lamda specify return type
    auto res = [](double a, double b) -> double { return (a + b); }(1.2, .2);
    std::cout << res << std::endl;

    // Capture List
    // Capture by value
    int c{14};

    auto func = [c]() { printf("Capture by value %d\n", c); };
    func();

    // Capture by reference
    auto funcref = [&c]() {
        printf("Capture by reference %d\n", c);
        ++c;
    };
    funcref();
    printf("Capture by reference %d\n", c);

    // Capture EVERYTHING OUTSIDE by value
    auto funvcall = [=]() { printf("Capture ALL by value %d\n", c); };
    funvcall();

    // Capture EVERYTHING OUTSIDE by reference
    auto funrcall = [&]() {
        printf("Capture ALL by ref %d\n", c);
        ++c;
    };
    funrcall();
    printf("Capture ALL by ref %d\n", c);

    return 0;
}
