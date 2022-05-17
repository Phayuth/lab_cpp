#include <iostream>
#include <ctime>

using namespace std;

// function to generate and return random numbers.
int * getRandom( ) {

	static int  r[10];

	// set the seed
	srand( (unsigned)time( NULL ) );

	r[0] = 55;
	r[1] = 45;
	r[2] = 77;
	r[3] = 54;
	r[4] = 24;
	r[5] = 75;
	r[6] = 22;
	r[7] = 55;
	r[8] = 78;
	r[9] = 97;
	// for (int i = 0; i < 10; ++i) {
	// 	r[i] = rand();
	// 	//cout << r[i] << endl;   if u want to print out first
	// }

	return r;
}

int main () {

	// a pointer to an int.
	int *p;

	p = getRandom();

	int a;
	int b;

	a = *(p+0);
	b = *(p+1);

	cout << "First value is :" << a << endl;
	cout << "First value is :" << b << endl;

	return 0;
}