#include <stdio.h>
#include <iostream>
#include <string>

// int main – ‘int main’ means that our function needs to return some integer at the end of the execution and we do so by returning 0 at the end of the program. 0 is the standard for the “successful execution of the program”.
// The :: is called scope resolution operator. Can be used like this:
// :: identifier
// class-name :: identifier
// namespace :: identifier

// Declaration: the return type, the name of the function, and parameters (if any)
// Definition: the body of the function (code to be executed)

void functionfull(){
	// To declare the function, we have to put the function on the top of the "main()"
	std::cout<<"The function_full is executed"<<std::endl;
}

int calculate_int(int a, int b){
	int c = a * b;
	return c;
}

float function_default_value(float def = 11.11, int a = 1,int b = 2){
	float c = def + a + b;
	return c;
}

void print_stuff(std::string input_string){
	std::cout<<input_string<<std::endl;
}

void function_prototype();// we can put the function below the "main" function as well, but we have to put a function prototype on top

int main() {
	print_stuff("--------------------------------------");

	functionfull();
	print_stuff("--------------------------------------");

	function_prototype();
	print_stuff("--------------------------------------");

	int c = calculate_int(10,56);
	print_stuff("--------------------------------------");

	std::cout<<"The calculated value : "<<c<<std::endl;
	print_stuff("--------------------------------------");

	float d = function_default_value();
	print_stuff("--------------------------------------");

	std::cout<<"The Default value : "<<d<<std::endl;
	print_stuff("--------------------------------------");

	return 0;
}

void function_prototype(){
	std::cout<<"The function_prototype is executed"<<std::endl;
}