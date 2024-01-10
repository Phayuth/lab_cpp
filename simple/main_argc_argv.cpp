/*
"argc" is in short for "argument count" -> it output the number of argument that have passed into the program
for example : cpptest 1 2 3 4 5 6 -> in this case the program has been passed with the argument of 6.
remember that the argc will return the number of argument + 1. where the 0th index is the name of the program itself.

"argv" is in short for "argument vector" - > it is the vector that store the argument of the program.
to call back the argument we can use argv[index].
for example : cpptest 1 2 3 4 5 6 -> argv[1] is 1.

std::cout << "Have " << argc << " arguments:" << std::endl;
for (int i = 0; i < argc; ++i) {
	std::cout << argv[i] << std::endl;
}
*/

#include <iostream>

int main(int argc, char const *argv[])
{
	std::cout << "Hi all, the program start here!...?" << std::endl;
	std::cout << "There are " << argc - 1 << " argument that have passed into the program" << std::endl;
	for (int i = 0; i < argc; ++i)
	{
		if (i == 1)
		{
			std::cout << "The 1st argument is " << argv[i] << std::endl;
		}
		if (i == 2)
		{
			std::cout << "The 2nd argument is " << argv[i] << std::endl;
		}
		if (i == 3)
		{
			std::cout << "The 3rd argument is " << argv[i] << std::endl;
		}
		if (i > 3)
		{
			std::cout << "The " << i << "th argument is " << argv[i] << std::endl;
		}
	}

	return 0;
}