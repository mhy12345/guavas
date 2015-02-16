#include "stdafx.h"
double Gaussian_Distribution_f(double x)
{
    return 1.0/(sqrt(2*PI))*exp(-x*x/2);
}
double Gaussian_Distribution_g(double x)
{
    if (x>0)return 0.398942280407134-Gaussian_Distribution_f(x);
    else return Gaussian_Distribution_f(x)-0.398942280407134;
}
double Gaussian_Distribution_h(double x)
{
    return Gaussian_Distribution_g((x-128)/128)*815.4343586563920+128;
}
int RGBdiff(int x,int y)
{
    return abs((x>>16)-(y>>16))
            +abs((x&0x00ff00>>8)-(y&0x00ff00>>8))
            +abs((x&0x0000ff)-(y&0x0000ff));
}
