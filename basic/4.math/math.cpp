#define _USE_MATH_DEFINES  // use this to call cmath constant value such as pi = M_PI = 3.14
#include <iostream>        // use this to use print etc
#include <cmath>           // use this to use math in c++

float x;   // we can define type before main
float y;
float q;
int count = 101;
float freq = 2*M_PI/30;
const int gravity = 9.81;  // constant of value where we can not change it later

int quater(int i, float freq){
	// float b = sqrt(i)*sin(freq*i)+cos(freq*i+1);
	// float b = sqrt(i);
	unsigned long long b = pow(i,2); // can overflow when value become high See max min value of data type
	return b;
}

void lineprint(){ // void function
	std::cout << "-------------------------------------------------------------"<< std::endl;
}

int main() {
	for (int i = 0; i < count; ++i)
	{
	float u = sin(freq*i); // we can define type in main as well
	float wer = quater(i,freq);
	lineprint();
	std::cout <<"Step : "<< i << " Sin wave is :" << u << std::endl;
	std::cout << "quater is :" << wer << std::endl;

	if (u < 0)
	{
		std::cout << "Negative region"<< std::endl;
	}
	else{
		std::cout << "Positive region"<< std::endl;
	}
	}
	std::cin.get();  // use to stop console to close, press enter to continue
}


// int main() {
// 	x = 5;
// 	y = 9;
// 	float w = pow(x,2);
// 	float r = pow(y,2);
// 	q = sqrt(w+r);
// 	std::cout << "Your number is :" << q << std::endl;
// }