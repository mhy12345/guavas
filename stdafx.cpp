#ifndef STDAFX_H
#define STDAFX_H

#include <bits/stdc++.h>

using namespace std;

#ifndef CONST_DEFINATION
#define CONST_DEFINATION
#define PI 3.1415926535384
const int mov[9][2]= {{0,1},{1,0},{0,-1},{-1,0},{1,1},{-1,-1},{-1,1},{1,-1},{0,0}};
const int maxpic=10;
#endif

double Gaussian_Distribution_h(double x);
double Gaussian_Distribution_g(double x);
double Gaussian_Distribution_f(double x);

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#endif
