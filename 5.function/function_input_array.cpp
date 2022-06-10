#include <stdio.h>
#include <iostream>
#include <string>

void func1(int myNumbers[5]) {
  for (int i = 0; i < 5; i++) {
    std::cout<<myNumbers[i]<<std::endl;
  }
}

int main() {
  
  int arry[5] = {10, 20, 30, 40, 50};
  func1(arry);
 

  return 0;
}