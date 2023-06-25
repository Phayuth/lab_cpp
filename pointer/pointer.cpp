#include <iostream>
#include <stdio.h>

// &variable = to get the address of the variable
// *address = to get the value inside of address

// a pointer is a special varailble that store an adress of other variable as its data
std::string name_original = "Johnyuth";
std::string *p_name = &name_original;

int main()
{
	std::cout << "Original = " << name_original << std::endl;
	std::cout << "Address of Original = " << &name_original << std::endl;

	std::cout << "Pointer = " << p_name << std::endl;
	std::cout << "Dereference back for the value of Pointer = " << *p_name << std::endl;

	// change the value of the pointer
	*p_name = "GOD YUTH";
	std::cout << "Changed value of the pointer = " << *p_name << std::endl;
	std::cout << "Changed value of the Original = " << name_original << std::endl;

	return 0;
}