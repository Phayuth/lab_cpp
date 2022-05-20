#include<stdio.h>
#include<iostream>
#include <limits>

int imin = std::numeric_limits<int>::min(); // minimum value
int imax = std::numeric_limits<int>::max();

int main() {
	std::cout << imin << " , " << imax << std::endl;
	std::cout << std::numeric_limits<float>::min() << " , " << std::numeric_limits<float>::max() << std::endl;
}