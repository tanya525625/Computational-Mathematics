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

double moment3(double iA, double iB, double a, double b) //Äëÿ aa = 2/3
{
	double res;
	/*res = (pow(iB - a, 1 / 3)*(81 * pow(a, 3) + 27 * a*a*iB + 18 * a*iB + 14 * pow(iB, 3))- (pow(iA - a, 1 / 3)*(81 * pow(a, 3) + 27 * a*a*iA + 18 * a*iA + 14 * pow(iA, 3))))*3/140;*/
	//res = 0.000191749*(pow(2 * iB - 5, 5 / 3)*(352 * pow(iB, 3) + 720 * iB*iB + 1350 * iB + 2025) - pow(2 * iA - 5, 5 / 3)*(352 * pow(iA, 3) + 720 * iA*iA + 1350 * iA + 2025));
	res = 0.3*(pow(iB - 2.5, 1 / 3)*(pow(iB, 3) + 3.21429*iB*iB + 12.0536*iB + 90.4018) - pow(iA - 2.5, 1 / 3)*(pow(iA, 3) + 3.21429*iA*iA + 12.0536*iA + 90.4018));
	return res;
}

double moment4(double iA, double iB, double a, double b)
{
	double res;
	/*res = (pow(iB - a, 1 / 3)*(243 * pow(a, 4) + 81 * pow(a, 3)*iB + 54 * a*a*iB*iB + 42 * a*pow(iB, 3) + 35 * pow(iB, 4)) -pow(iA - a, 1 / 3)*(243 * pow(a, 4) + 81 * pow(a, 3)*iA + 54 * a*a*iA*iA + 42 * a*pow(iA, 3) + 35 * pow(iA, 4)))/455*3;*/
	/*res = 0.176471*(pow(iB - 2.5, 2 / 3)*(pow(iB, 5) - 0.357143*pow(iB, 4) - 0.974026*pow(iB, 3) - 2.73945*iB*iB - 8.21834*iB - 30.8188) - pow(iA - 2.5, 2 / 3)*(pow(iA, 5) - 0.357143*pow(iA, 4) - 0.974026*pow(iA, 3) - 2.73945*iA*iA - 8.21834*iA - 30.8188));*/
	res = 0.230769*(pow(iB - 2.5, 1 / 3)*(pow(iB, 4) + 3 * pow(iB, 3) + 9.64286*iB*iB + 36.1607*iB + 271.205) - pow(iA - 2.5, 1 / 3)*(pow(iA, 4) + 3 * pow(iA, 3) + 9.64286*iA*iA + 36.1607*iA + 271.205));
	return res;
}

double moment5(double iA, double iB, double a, double b)
{
	double res;
	/*res = (pow(iB - a, 1 / 3)*(729 * pow(a, 5) + 243 * iB*pow(a, 4) + 162 * iB*iB*pow(a, 3) + 126 * a*a*pow(iB, 3) + 105 * a*pow(iB, 4) + 91 * pow(iB, 5)) - pow(iA - a, 1 / 3)*(729 * pow(a, 5) + 243 * iA*pow(a, 4) + 162 * iA*iA*pow(a, 3) + 126 * a*a*pow(iA, 3) + 105 * a*pow(iA, 4) + 91 * pow(iA, 5)))/1456*3;*/
	/*res = 0.15*(pow(iB - 2.5, 2 / 3)*(pow(iB, 6) - 0.294118*pow(iB, 5) - 0.787815*pow(iB, 4) - 2.14859*pow(iB, 3) - 6.0429*iB*iB - 18.1287*iB - 67.9826) - pow(iA - 2.5, 2 / 3)*(pow(iA, 6) - 0.294118*pow(iA, 5) - 0.787815*pow(iA, 4) - 2.14859*pow(iA, 3) - 6.0429*iA*iA - 18.1287*iA - 67.9826));*/
	res = 0.1875*(pow(iB - 2.5, 1 / 3) * (pow(iB, 5) + 2.88462*pow(iB, 4) + 8.65385*pow(iB, 3) + 27.8159*iB*iB + 104.31*iB + 782.323) - pow(iA - 2.5, 1 / 3) * (pow(iA, 5) + 2.88462*pow(iA, 4) + 8.65385*pow(iA, 3) + 27.8159*iA*iA + 104.31*iA + 782.323));
	return res;
}

void sort(double* data, int lenD)
{
	int tmp = 0;
	for (int i = 0; i<lenD; i++) 
	{
		for (int j = (lenD - 1); j >= (i + 1); j--) 
		{
			if (data[j]<data[j - 1]) 
			{
				tmp = data[j];
				data[j] = data[j - 1];
				data[j - 1] = tmp;
			}
		}
	}
}

double* Kardano(double* a, double* x)
{
	double temp = a[0]; 
	a[0] = a[2];
	a[2] = temp;
	double p = a[1] - a[0] * a[0] / 3; // p = b - a^2/3
	double q = a[2] + 2* a[0] * a[0] * a[0] / 27 - a[0] * a[1] / 3; // q = c + 2a^3/27 - ab/3
	double determinant = q * q / 4 + p * p * p / 27;

	if (determinant < 0)
	{
		double fi = 0;
		if (q < 0) fi = atan(2.0 * sqrt(-determinant) / (-q));
		if (q > 0) fi = atan(2.0 * sqrt(-determinant) / (-q) + pi);
		if (q == 0) fi = pi / 2.0;

		x[0] = 2.0 * sqrt(-p / 3.0) * cos(fi / 3.0) - a[0] / 3.0;
		x[1] = 2.0 * sqrt(-p / 3.0) * cos(fi / 3.0 + 2.0 * pi / 3.0) - a[0] / 3.0;
		x[2] = 2.0 * sqrt(-p / 3.0) * cos(fi / 3.0 + 4.0 * pi / 3.0) - a[0] / 3.0;
	}
	if (determinant > 0)
	{
		x[1] = 0;
		if ((-q) / 2.0 + pow(determinant, 1.0 / 2.0) < 0)
			x[1] += -pow((q) / 2.0 - pow(determinant, 1.0 / 2.0), 1.0 / 3.0);
		else x[1] += pow((-q) / 2.0 + pow(determinant, 1.0 / 2.0), 1.0 / 3.0);
		if (-q / 2.0 - pow(determinant, 1.0 / 2.0) < 0)
			x[1] += -pow(q / 2.0 + pow(determinant, 1.0 / 2.0), 1.0 / 3.0) - a[0] / 3.0;
		else x[1] += pow(-q / 2.0 - pow(determinant, 1.0 / 2.0), 1.0 / 3.0) - a[0] / 3.0;
	}
	if (determinant == 0) {
		x[0] = 2 * pow(-q / 2.0, 1.0 / 3.0) - a[0] / 3.0;
		x[1] = -pow(-q / 2.0, 1.0 / 3.0) - a[0] / 3.0;
	}
	return x;
}

