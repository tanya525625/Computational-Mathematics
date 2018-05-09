#include "Header.h" 

double F(double x)
{
	double aa = 2 / 3;
	x = (3 * cos(1.5*x)*exp(x / 4) + 4 * sin(3.5*x)*exp(-3 * x) + 4 * x)/* / pow(x - 2.5, aa)*/;

	return x;
}

double moment0(double iA, double iB, double a, double b, double aa, double bb)
{
	double res;
	res =  (pow(iB - a, 1-aa) - pow(iA - a, 1-aa))/(1-aa);
	return res;
}

double moment1(double iA, double iB, double a, double b, double aa, double bb, double mom0)
{
	double res;
	res = (pow(iB - a, 2-aa) - pow(iA - a, 2 - aa)) / (2 - aa) + a*mom0;
	return res;
}

double moment2(double iA, double iB, double a, double b, double aa, double bb, double mom0, double mom1)
{
	double res;
	res = (pow(iB - a, 3 - aa) - pow(iA - a, 3 - aa)) / (3 - aa) + 2 * a*mom1- a*a*mom0;
	return res;
}

