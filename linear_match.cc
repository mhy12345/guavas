#include "stdafx.h"
#include "linear_match.h"

double sqr(double x) {
	return x * x;
}

double dist(double x0, double y0, double x1, double y1) {
	return sqr(x0 - x1) + sqr(y0 - y1);
}

double LinearMatch :: matchArrs(double* a, double* ta, double* b) {
	double s(0);
	for (double *i = a, *j = b; i != ta; ++ i, ++ j)
		s += sqr(*i - *j);
	return sqrt(s);
}

