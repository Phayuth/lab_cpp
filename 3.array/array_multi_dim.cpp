#include <iostream>
#include <cmath>

int array[3][3]={{0,1,2},{3,4,5},{6,7,8}};

int main()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cout<<"Array element"<<"["<<i<<"]"<<"["<<j<<"]"<<array[i][j]<<std::endl;
		}
	}
	
}