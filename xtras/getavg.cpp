#include <iostream>
#include <stdio.h>

double getAverage(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    double avg = double(sum) / size;
    return avg;
}

void test_getAverage() {
    int balance[5] = {1000, 2, 3, 17, 50};
    double avg = getAverage(balance, 5);
    std::cout << "Average value is: " << avg << std::endl;
}

int main() {
    test_getAverage();
    return 0;
}