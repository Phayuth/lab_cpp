#include <iostream>
#include <limits>
#include <stdio.h>
#include <string>

int x = 5;                    // 2 or 4 bytes | Integer (whole number without decimals)
float y = 5.99f;              // 4 bytes      | Decimal point number Sufficient for storing 7 decimal digits
double z = 9.98;              // 8 bytes      | Decimal point number Sufficient for storing 15 decimal digits
char D = 'D';                 // 1 bytes      | Character Stores a single character/letter/number, or ASCII values
const char* st = "string";    //              | string literal in pure form. "" must be use instead of ''
std::string string = "Hello"; //              | string class. must include string
char sta[] = "string";        //              | string in form of array of char
bool bol = true;              // 1 bytes      | true or false. Stores true or false values
const int contInt = 5;        //              | Constant read only

int imin = std::numeric_limits<int>::min();
int imax = std::numeric_limits<int>::max();

int main() {
    std::cout << x << "\n";
    std::cout << y << "\n";
    std::cout << z << "\n";
    std::cout << st << "\n";
    std::cout << sta << "\n";
    std::cout << imin << " , " << imax << std::endl;

    return 0;
}