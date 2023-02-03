#include <iostream>
#include <string>
#include <stdbool.h>

struct struct_test
{
	int id;
	float hp;
	std::string hero_name;
	bool carry;
};


int main(int argc, char const *argv[])
{
	struct_test herohero;
	herohero.id = 1;
	herohero.hp = 500.99;
	herohero.hero_name = "Flollly";
	herohero.carry = true;

	std::cout<<"id = "<< herohero.id <<"\nhp = "<< herohero.hp << "\nhero_name = " << herohero.carry << "\ncarry ? = "<<herohero.carry << std::endl;
	return 0;
}