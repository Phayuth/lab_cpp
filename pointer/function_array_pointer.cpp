#include <stdio.h>
#include <iostream>
#include <string>

int main() {

	int arry[5] = {10, 20, 30, 40, 50};
	int* arry2[5];

	for (int i = 0; i < 5; ++i)
	{
		arry2[i] = &arry[i];
	}

	for (int i = 0; i < 5; ++i)
	{
		std::cout<<*arry2[i]<<std::endl;
	}

	return 0;
}