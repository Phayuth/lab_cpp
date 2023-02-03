#include <iostream>
#include "sqrt_plus.h"
// we have to inculde header file (.h) which is a declarator to another source cpp file
// we use #include ""  for custom header only
// we can use #include "" or #include <> for standard library


int main()
{
	std::cout<< " C is " << sqrt_plus(575,2.255) << std::endl;
	std::cin.get();
}

// apply the header file