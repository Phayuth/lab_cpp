#include <iostream>
using namespace std;

int main () {
	// an int array with 5 elements.
	int balance[5] = {1000, 2, 3, 17, 50};

	int *ptr = &balance[0]+1; // the address can use addition and substract operation
	cout << *ptr << endl;


	// In array
	// the array address is the first element of the array address
	// all the code below print the address of the array all the same
	cout << balance << endl;
	cout << &balance << endl;
	cout << &balance[0] << endl;

	return 0;
}