#include <iostream>
#include <stdio.h>

// &variable = to get the address of the variable
// *address = to get the value inside of address

std::string name = "Johnyuth"; // the original string variable "name" that has the value of "Johnyuth"
std::string *neam = &name;	   // a pointer of type string "neam" that used to store the memory address of the reference variable "name"

int main()
{
	// create original variable
	std::cout << "Original = " << name << std::endl;

	// print out the memory address of name
	std::cout << "Adrs of Original = " << &name << std::endl;

	// create a pointer to the original variable and call the pointer 'neam' and print the 'neam' out
	std::cout << "Pointer address of Original = " << neam << std::endl;

	// dereference : to get the value back that the memory of that address has. this operation can be done
	// with asterisk symbol (*). example : *pointer_variable
	std::cout << "Deference back for the value of Pointer = " << *neam << std::endl;

	// change the value of the pointer
	*neam = "GOD YUTH";

	// print out the new pointer value
	std::cout << "Changed value of the pointer = " << *neam << std::endl;

	std::cout << "Changed value of the Original = " << name << std::endl;

	return 0;
}