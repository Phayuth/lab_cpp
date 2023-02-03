// From code beauty on YT https://www.youtube.com/watch?v=wN0x9eZLix4
// You will learn
// Introduction
// Introduction to OOP
// Classesand objects
// Access modifiers

#include <iostream> // include this lib to use cout cin
using std::string; // using std::string; to avoid repeatly put [std::string] before variable creating
class Employee {             // create class name Employee
public:                      // make property in class public instead of private , protected
	string Name;             // create variable
	string Company;          // create variable
	int Age;                 // create variable

	void IntroduceYourself() {   // create function name IntroduceYourself
		std::cout << "Name - " << Name << std::endl;        // print out Name
		std::cout << "Company - " << Company << std::endl;  // print out Company
		std::cout << "Age - " << Age << std::endl;          // print out Age
	}
};

int main()  //main() function is the entry point of any C++ program. It is the point at which execution of program is started. When a C++ program is executed, the execution control goes directly to the main() function.
{
	Employee employee1;                // create an object inherit the class
	employee1.Name = "Phayuth";        // input data into the object property
	employee1.Company = "DC_Lab";      // input data into the object property
	employee1.Age = 21;                // input data into the object property
	employee1.IntroduceYourself();     // invoke the function in class

	Employee employee2;                // create an object inherit the class
	employee1.Name = "Johnyuth";       // input data into the object property
	employee1.Company = "Home";        // input data into the object property
	employee1.Age = 150;               // input data into the object property
	employee1.IntroduceYourself();     // invoke the function in class

	std::cin.get();    // Use to make console stay up
}