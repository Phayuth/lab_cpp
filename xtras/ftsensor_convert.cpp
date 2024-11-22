#include <iostream>
#include <stdio.h>

unsigned char recvCandata[2][8];
double convertedC[8] = {0};
double ft_array[6];

int main(int argc, char const *argv[]) {
    convertedC[0] = (double)(((unsigned int)recvCandata[0][1]) * 256 + (((unsigned int)recvCandata[0][2])));
    convertedC[1] = (double)(((unsigned int)recvCandata[0][3]) * 256 + (((unsigned int)recvCandata[0][4])));
    convertedC[2] = (double)(((unsigned int)recvCandata[0][5]) * 256 + (((unsigned int)recvCandata[0][6])));
    convertedC[3] = (double)(((unsigned int)recvCandata[0][7]) * 256 + (((unsigned int)recvCandata[1][0])));
    convertedC[4] = (double)(((unsigned int)recvCandata[1][1]) * 256 + (((unsigned int)recvCandata[1][2])));
    convertedC[5] = (double)(((unsigned int)recvCandata[1][3]) * 256 + (((unsigned int)recvCandata[1][4])));

    for (size_t i = 0; i < 3; i++) {
        ft_array[i] = convertedC[i] / 1000 - 30;
        ft_array[i + 3] = convertedC[i + 3] / 300 - 100;
        //	ft_array[i]=convertedC[i]/1000-30;	          //    AFT50
        //	ft_array[i+3]=convertedC[i+3]/300-100;          //     AFT50
    }

    return 0;
}
