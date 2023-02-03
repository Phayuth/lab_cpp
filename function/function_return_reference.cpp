#include <stdio.h>
#include <iostream>
#include <string>

void function_reference(int &x, int &y){
	int z = x;
	x = y;
	y = z;
}

int first = 31;
int secnd = 55;

int a = 5;
int &b = a;
int* c = &a;

int main() {

	std::cout<<first<<std::endl;
	std::cout<<secnd<<std::endl;
	function_reference(first,secnd);
	std::cout<<first<<std::endl;
	std::cout<<secnd<<std::endl;
	
	return 0;
}
