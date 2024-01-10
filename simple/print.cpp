#include <iostream>
#include <stdio.h>

// Character format
// \a = audible alert ( sound waring noise)
// \b = back space
// \l = linefeed
// \n = newline
// \r = carriage return
// \t = horizontal tab
// \v = vertical bar
// \' = sigle quote
// \" = doble quote
// \? = Question mark
// \\ = backslash
// \0 = null

int main() {
    std::cout << "Hello \rMr. Nobby-";   // print hello to screen
    std::cout << "\n";                   // print newline
    std::cout << 5;                      // can directly print number
    std::cout << "\n";
    std::cout << "5";                    // can directly print number
    std::cout << "\n";
    std::cout << "\r";

    int num = 42;
    double pi = 3.14159;
    double *pPi = &pi;
    char ch = 'A';
    const char *str = "Hello, World!";

    printf("Integer: %d\n", num);
    printf("Unsigned Integer: %u\n", (unsigned int)num);
    printf("Octal: %o\n", num);
    printf("Hexadecimal: %x\n", num);
    printf("Floating-point: %f\n", pi);
    printf("Scientific Notation: %e\n", pi);
    printf("Character: %c\n", ch);
    printf("String: %s\n", str);

    printf("Space Padding: %15f\n", pi); // must be bigger than string size
    printf("Precision: %.15f\n", pi);

    printf("Pointer Address: %p\n", pPi);


    return 0;
}