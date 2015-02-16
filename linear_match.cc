#include "stdafx.h"
#include "linear_match.h"

double sqr(double x) {
	return x * x;
}

double dist(double x0, double y0, double x1, double y1) {
	return sqr(x0 - x1) + sqr(y0 - y1);
}

double LinearMatch :: matchArrs(int* a, int* ta, int* b) {
	double s(0);
	for (int *i = a, *j = b; i != ta; ++ i, ++ j)
		s += sqr(*i - *j);
	return sqrt(s);
}

