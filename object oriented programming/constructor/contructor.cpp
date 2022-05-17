// From code beauty on YT https://www.youtube.com/watch?v=wN0x9eZLix4
// You will learn
// Contructor

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
	Employee(string name,string company,int age) {   // contructor
		Name = name;
		Company = company;
		Age = age;
	}
};

int main()  //main() function is the entry point of any C++ program. It is the point at which execution of program is started. When a C++ program is executed, the execution control goes directly to the main() function.
{
	Employee employee1("Phayuth","DC_Lab",21);  // contructor
	employee1.IntroduceYourself();              // invoke the function in class
	system("pause");
}