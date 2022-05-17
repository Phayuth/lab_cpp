#include <stdio.h>
#include <iostream>
#include <string>

// int x = 5;          // Integer (whole number without decimals)
// float y = 5.99;     // Floating point number
// double z = 9.98;    // Floating point number
// char x = 'D';       // Character
// string x = "Hello"; // text
// bool x = true;      // true or false
// const int a = 5;    // make interger a constant = read only


// boolean  1      byte     Stores true or false values
// char     1      byte     Stores a single character/letter/number, or ASCII values
// int      2 or 4 bytes    Stores whole numbers, without decimals
// float    4      bytes    Stores fractional numbers, containing one or more decimals. Sufficient for storing 7 decimal digits
// double   8      bytes    Stores fractional numbers, containing one or more decimals. Sufficient for storing 15 decimal digits


int x = 4;
double y = 5.36;
char z = 'z';
std::string q = "ok"; // special. have to call in library string and std::string to this type
bool w = true;

int main() {
	std::cout << x;
	std::cout << "\n";
	std::cout << y;
	std::cout << "\n";
	std::cout << z;
	std::cout << "\n";
	std::cout << q;
	std::cout << "\n";

	system("pause"); // pause the sytem before exit
	return 0;
}