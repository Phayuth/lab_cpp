#include <iostream>
#include <cstdlib>
#include <cmath>

int main (int argc, char *argv[])
{
	double inputValue = atof(argv[1]);
	std::cout << "The square root of " << inputValue << " is " << sqrt(inputValue) << std::endl;
	return 0;
}