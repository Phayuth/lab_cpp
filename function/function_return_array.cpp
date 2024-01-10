#include <ctime>
#include <iostream>

using namespace std;

// function to generate and return random numbers.
int *getRandom() {

    static int r[10];

    // set the seed
    srand((unsigned)time(NULL));

    r[0] = rand();
    r[1] = rand();
    r[2] = rand();
    r[3] = rand();
    r[4] = rand();
    r[5] = rand();
    r[6] = rand();
    r[7] = rand();
    r[8] = rand();
    r[9] = rand();
    // for (int i = 0; i < 10; ++i) {
    // 	r[i] = rand();
    //    cout << r[i] << endl;   if u want to print out first
    // }

    return r;
}

int main() {

    // a pointer to an int.
    int *p;

    p = getRandom();

    int a;
    int b;

    a = *(p + 0);
    b = *(p + 1);

    cout << "First value is :" << a << endl;
    cout << "First value is :" << b << endl;

    return 0;
}