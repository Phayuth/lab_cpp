#include <stdio.h>
#include <iostream>

// return output by function paramter - done by using reference

void function_reference(int &x, int &y)
{
	int z = x;
	x = y;
	y = z;
}

int first = 31;
int secnd = 55;

void cal_int(int a, int b, int &c)
{
	c = a + b;
};

int main()
{

	std::cout << first << std::endl;
	std::cout << secnd << std::endl;
	function_reference(first, secnd);
	std::cout << first << std::endl;
	std::cout << secnd << std::endl;

	int a = 10;
	int b = 20;
	int c{};
	cal_int(a, b, c);
	std::cout << c << std::endl;

	return 0;
}
