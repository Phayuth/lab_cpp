#include <iostream>
#include <cmath>

int main()
{
	float Lasertheta=0;
	float Laserdistn=0;

	float Laser[3] = {25.,63.,88.};// datatype variable[number of element] = {ele1,ele2,......}
	float Laser_pi[6]; // pre initialize array

	Laser_pi[0]=58.; // assign value to element array
	Laser_pi[1]=48.;
	Laser_pi[2]=54.;
	Laser_pi[3]=12.;
	Laser_pi[4]=21.;
	Laser_pi[5]=71.;

	float Laser_loop[360];

	for (int i = 0; i < 360; ++i)
	{
		Laser_loop[i] = std::rand();
		std::cout << "Laser_loop" << "[" << i << "] = "<< Laser_loop[i] <<std::endl;
	}
	std::cout << "Laser Theta = "<< Lasertheta << std::endl;
	std::cout << "Laser Distn = "<< Laserdistn << std::endl;

	std::cout << "Laser 1  = "<< Laser[0] << std::endl;
	std::cout << "Laser 2  = "<< Laser[1] << std::endl;
	std::cout << "Laser 3  = "<< Laser[2] << std::endl;

	std::cout << "Laser_pi 1  = "<< Laser_pi[0] << std::endl;
	std::cout << "Laser_pi 2  = "<< Laser_pi[1] << std::endl;
	std::cout << "Laser_pi 3  = "<< Laser_pi[2] << std::endl;
	std::cout << "Laser_pi 1  = "<< Laser_pi[3] << std::endl;
	std::cout << "Laser_pi 2  = "<< Laser_pi[4] << std::endl;
	std::cout << "Laser_pi 3  = "<< Laser_pi[5] << std::endl;

	std::cin.get();
}