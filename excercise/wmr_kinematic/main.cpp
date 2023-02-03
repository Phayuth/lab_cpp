#include <cmath>
#include <iostream>

// no using pointer
// float v=0.1;
// float omega = 0;
// float Ts = 0.03;

// float x=0;
// float y=0;
// float t=0;

// int count = 100;

// int main(int argc, char const *argv[])
// {
// 	std::cout << "Starting Odometry" << std::endl;
	
// 	while(true)
// 	{
// 		x = x + v*cos(t)*Ts;
// 		y = y + v*sin(t)*Ts;
// 		t = t + omega*Ts;
// 		std::cout << "X = " << x << " , " << "Y = " << y << " , " << " T = " << t << std::endl;
// 	}
// 	return 0;
// }


// with pointer
float v = 0.1;   // v[m/s]
float omga = 0;  // omega[rad/s]
float Ts = 0.03; // Ts[s]

float x=0,y=0,t=0; // initial value for coordinate
float *xptr = &x, *yptr = &y, *tptr = &t;

// void forward_kin(float v, float omga,float t){
// 	*xptr += v*cos(t)*Ts;
// 	*yptr += v*sin(t)*Ts;
// 	*tptr += omga*Ts;
// }

void printing(float x, float y, float t){
	std::cout<<"x = "<<x<<" , y = "<<y<<" , theta = "<<t<<std::endl;
}

int main(int argc, char const *argv[])
{
	for (int i = 0; i < 100; ++i)
	 {
	 	printing(x,y,t);
		*xptr += v*cos(t)*Ts;
		*yptr += v*sin(t)*Ts;
		*tptr += omga*Ts;
	 }
	return 0;
}