#define _USE_MATH_DEFINES
#include <stdio.h>
#include <iostream>
#include <cmath>


float v = 0.1;   // v[m/s]
float omga = 0;  // omega[rad/s]
float Ts = 0.01; // Ts[s]

float x=0,y=0,t=0; // initial value for coordinate
float *xptr = &x, *yptr = &y, *tptr = &t;

void forward_kin(float v, float omga,float t){
	*xptr += v*cos(t)*Ts;
	*yptr += v*sin(t)*Ts;
	*tptr += omga*Ts;
}

void printing(float x, float y, float t){
	std::cout<<"x = "<<x<<" , y = "<<y<<" , theta = "<<t<<std::endl;
}

int main(int argc, char const *argv[])
{
	while (true) {
		printing(x,y,t);
		forward_kin(v,omga,Ts);
	}
	return 0;
}