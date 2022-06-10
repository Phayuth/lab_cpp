#include <iostream>
#include <stdio.h>
#include <string>

//A reference variable is a "reference" to an existing variable, and it is created with the & operator

std::string name = "Johnyuth";
std::string &neam = name;   // reference to name

int main(int argc, char const *argv[])
{
	std::cout<<"The original variable name is "<<name<<std::endl;
	std::cout<<"The reference variable neam is "<<neam<<std::endl;
	std::cout<<"The address of the variable "<<&neam<<std::endl;
	
	return 0;
}


// The & operator used for create a reference variable. 
// But it can also be used to get the memory address of a variable; 
// which is the location of where the variable is stored on the computer.

// When a variable is created in C++, a memory address is assigned to the variable. 
// And when we assign a value to the variable, it is stored in this memory address.

// To access it, use the & operator, and the result will represent where the variable is stored:

// References and Pointers give you the ability to manipulate the data in the computer memory
// which can reduce the code and improve the performance.
// The memory address is in hexadecimal form (0x).