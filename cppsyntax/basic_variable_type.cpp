#include <iostream>
#include <limits>
#include <stdio.h>
#include <string>

int x = 5;       // 2 or 4 bytes | Integer (whole number without decimals)
float y = 5.99f; // 4 bytes      | Decimal point number Sufficient for storing 7
                 // decimal digits
double z = 9.98; // 8 bytes      | Decimal point number Sufficient for storing 15
                 // decimal digits
char D = 'D'; // 1 bytes      | Character Stores a single character/letter/number,
              // or ASCII values
const char *st = "string"; //              | string literal in pure form. "" must
                           //              be use instead of ''
std::string string = "Hello"; //              | string class. must include string
char sta[] = "string";        //              | string in form of array of char
bool bol = true;       // 1 bytes      | true or false. Stores true or false values
const int contInt = 5; //              | Constant read only

int imin = std::numeric_limits<int>::min();
int imax = std::numeric_limits<int>::max();

int count = 10;           // declare with assignment
int counting{10};         // declare with curly bracket
int counter(10);          // declare with function
const int gravity = 9.81; // constant val, cann't change error
auto x = 2.0;

int main() {
    std::cout << x << "\n";
    std::cout << y << "\n";
    std::cout << z << "\n";
    std::cout << st << "\n";
    std::cout << sta << "\n";
    std::cout << imin << " , " << imax << std::endl;

    std::cout << "Hello \rMr. Nobby-"; // print hello to screen
    std::cout << "\n";                 // print newline
    std::cout << 5;                    // can directly print number
    std::cout << "\n";
    std::cout << "5"; // can directly print number
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