#include<stdio.h>
#include<iostream>

// Character format
// \a = audible alert ( sound waring noise)
// \b = back space
// \l = linefeed
// \n = newline
// \r = carriage return
// \t = horizontal tab
// \v = vertical bar
// \' = sigle quote
// \" = doble quote
// \? = Question mark
// \\ = backslash
// \0 = null

int main() {
	std::cout << "Hello \rMr. Nobby-"; //print hello to screen
	std::cout << "\n"; // print newline
	std::cout << 5; // can directly print number
	std::cout << "\n";
    std::cout << "5"; // can directly print number
    std::cout << "\n";
    std::cout << "\r";
	system("pause"); // pause the sytem before exit
}