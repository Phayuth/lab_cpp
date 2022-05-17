// From code beauty on YT https://www.youtube.com/watch?v=wN0x9eZLix4
// You will learn
// Encapsulation = bundle the method and data into class

#include <iostream> // include this lib to use cout cin
using std::string; // using std::string; to avoid repeatly put [std::string] before variable creating
class Employee {             // create class name Employee
private:                     // make property in class private
	string Name;             // create variable
	string Company;          // create variable
	int Age;                 // create variable
	// in private, the data is encapsulated and hidden and only access with public setter and getter
public:
	void setName(string name) {   // setter
		Name = name;
	}
	string getName() {            // getter
		return Name;
	}
	void setCompany(string company) {
		Company = company;
	}
	string getCompany() {
		return Name;
	}
	void setAge(int age) {
		if (age>=18)
		Age = age;
	}
	int getAge() {
		return Age;
	}
	void IntroduceYourself() {   // create function name IntroduceYourself
		std::cout << "Name - " << Name << std::endl;        // print out Name
		std::cout << "Company - " << Company << std::endl;  // print out Company
		std::cout << "Age - " << Age << std::endl;          // print out Age
	}
	Employee(string name, string company, int age) {   // contructor
		Name = name;
		Company = company;
		Age = age;
	}
};

int main()  //main() function is the entry point of any C++ program. It is the point at which execution of program is started. When a C++ program is executed, the execution control goes directly to the main() function.
{
	Employee employee1("Phayuth", "DC_Lab", 21);  // contructor
	employee1.IntroduceYourself();              // invoke the function in class
	
	employee1.setAge(21);        // setter
	std::cout << employee1.getName() << " is " << employee1.getAge() << std::endl;
}