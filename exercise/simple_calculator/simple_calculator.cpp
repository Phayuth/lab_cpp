#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

float num1;
float num2;
float ans;
int oper;

int main()
{
	std::cout << "Operator are Multiply = 1\nDevide = 2\nPlus = 3\nMinus = 4" << std::endl;
	std::cout <<"Input the First Number: ";
	std::cin >> num1;
	std::cout << "Input the Second Number: ";
	std::cin >> num2;
	std::cout <<"Input the operation: ";
	std::cin >> oper;
	std::cout << "Num1 is :"<< num1 << std::endl;
	std::cout << "Num2 is :"<< num2 << std::endl;
	std::cout << "opt is  :"<< oper << std::endl;
	std::cin.get();

	if (oper == 1)
	{
		ans = num1 * num2;
		std::cout << "The answer is : " << ans << std::endl;
		std::cin.get();
	}

	else if (oper == 2)
	{
		ans = num1 / num2;
		std::cout << "The answer is : " << ans << std::endl;
		std::cin.get();
	}

	else if (oper == 3)
	{
		ans = num1 + num2;
		std::cout << "The answer is : " << ans << std::endl;
		std::cin.get();
	}

	else if (oper == 4)
	{
		ans = num1 - num2;
		std::cout << "The answer is : " << ans << std::endl;
		std::cin.get();
	}

	else
	{
		std::cout << "------"<< std::endl;
		std::cin.get();
	}
}


// g++ -o runProgram simple_calculator.cpp  to compile the code