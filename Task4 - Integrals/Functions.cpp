#include "Header.h" 


double F(double x)
{
	double aa = 2 / 3;
	x = (3 * cos(1.5*x)*exp(x / 4) + 4 * sin(3.5*x)*exp(-3 * x) + 4 * x)/ pow(x - 2.5, aa);

	return x;
}

double moment0(double iA, double iB, double a, double b, double aa, double bb)
{
	double res;

	/*res =  (pow(iB - a, 1-aa) - pow(iA - a, 1-aa))/(1-aa);*/
	res = (pow(iB - a, 1.0 / 3.0) - pow(iA - a, 1.0 / 3.0))*3;
	return res;
}

double moment1(double iA, double iB, double a, double b, double aa, double bb, double mom0)
{
	double res;
	/*res = (pow(iB - a, 2-aa) - pow(iA - a, 2 - aa)) / (2 - aa) + a*mom0;*/
	res = 0.75*(pow(iB - a, 1.0 / 3.0)*(iB + 7.5) - (pow(iA - a, 1.0 / 3.0)*(iA + 7.5)));
	return res;
}

double moment2(double iA, double iB, double a, double b, double aa, double bb, double mom0, double mom1)
{
	double res;
	/*res = (pow(iB - a, 3 - aa) - pow(iA - a, 3 - aa)) / (3.0 - aa) + 2.0  * a*mom1- a*a*mom0;*/
	res = 0.428571*(pow(iB - 2.5, 1 / 3.0)*(iB*iB + 3.75*iB + 28.125) - (pow(iA - 2.5, 1 / 3.0)*(iA*iA + 3.75*iA + 28.125)));
	return res;
}

double moment3(double iA, double iB, double a, double b) //Äëÿ aa = 2/3
{
	double res;
	res = (pow(iB - a, 1 / 3.0)*(81 * pow(a, 3) + 27 * a*a*iB + 18 * a*iB + 14 * pow(iB, 3))- (pow(iA - a, 1 / 3.0)*(81 * pow(a, 3) + 27 * a*a*iA + 18 * a*iA + 14 * pow(iA, 3))))*3/140.0;
	//res = 0.000191749*(pow(2 * iB - 5, 5 / 3)*(352 * pow(iB, 3) + 720 * iB*iB + 1350 * iB + 2025) - pow(2 * iA - 5, 5 / 3)*(352 * pow(iA, 3) + 720 * iA*iA + 1350 * iA + 2025));
	/*res = 0.3*(pow(iB - 2.5, 1 / 3)*(pow(iB, 3) + 3.21429*iB*iB + 12.0536*iB + 90.4018) - pow(iA - 2.5, 1 / 3)*(pow(iA, 3) + 3.21429*iA*iA + 12.0536*iA + 90.4018));*/
	//res = 3/10.0*pow(iB - a, 10 / 3.0) + 45/ 14.0  * pow(iB - a, 7/ 3.0) + 225 / 16.0  * pow(iB - a, 4 / 3.0) + 375 / 8.0  * pow(iB - a, 1/ 3.0) - (0.3*pow(iA - a, 10 / 3.0) + 45 / 14.0 * pow(iA - a, 7/ 3.0) + 225 / 16.0  * pow(iA - a, 4 / 3.0) + 375 / 8.0  * pow(iA - a, 1 / 3.0));
	return res;
}

double moment4(double iA, double iB, double a, double b)
{
	double res;
	res = 3*(pow(iB - a, 1 / 3.0)*(243 * pow(a, 4) + 81 * pow(a, 3)*iB + 54 * a*a*iB*iB + 42 * a*pow(iB, 3) + 35 * pow(iB, 4)) - pow(iA - a, 1 / 3.0)*(243 * pow(a, 4) + 81 * pow(a, 3)*iA + 54 * a*a*iA*iA + 42 * a*pow(iA, 3) + 35 * pow(iA, 4)))/455.0;
	/*res = 0.176471*(pow(iB - 2.5, 2 / 3)*(pow(iB, 5) - 0.357143*pow(iB, 4) - 0.974026*pow(iB, 3) - 2.73945*iB*iB - 8.21834*iB - 30.8188) - pow(iA - 2.5, 2 / 3)*(pow(iA, 5) - 0.357143*pow(iA, 4) - 0.974026*pow(iA, 3) - 2.73945*iA*iA - 8.21834*iA - 30.8188));*/
	/*res = 0.230769*(pow(iB - 2.5, 1 / 3)*(pow(iB, 4) + 3 * pow(iB, 3) + 9.64286*iB*iB + 36.1607*iB + 271.205) - pow(iA - 2.5, 1 / 3)*(pow(iA, 4) + 3 * pow(iA, 3) + 9.64286*iA*iA + 36.1607*iA + 271.205));*/
	//res = 3 / 13.0  * pow(iB - a, 13 / 3.0) + 3.0  * pow(iB - a, 10/ 3.0) + 225 / 14.0  * (iB - a, 7 / 3.0) + 375 / 8.0  * pow(iB - a, 4/ 3.0) + 1875 / 16.0  * pow(iB - a, 1 / 3.0) - (3/ 13.0  * pow(iA - a, 13 / 3.0) + 3 * pow(iA - a, 10 / 3.0) + 225 / 14.0  * (iA - a, 7 / 3.0) + 375 / 8.0  * pow(iA - a, 4 / 3.0) + 1875/ 16.0  * pow(iA - a, 1 / 3.0));
	return res;
}

double moment5(double iA, double iB, double a, double b)
{
	double res;
	//res = (pow(iB - a, 1 / 3.0)*(729 * pow(a, 5) + 243 * iB*pow(a, 4) + 162 * iB*iB*pow(a, 3) + 126 * a*a*pow(iB, 3) + 105 * a*pow(iB, 4) + 91 * pow(iB, 5)) - pow(iA - a, 1 / 3.0)*(729 * pow(a, 5) + 243 * iA*pow(a, 4) + 162 * iA*iA*pow(a, 3) + 126 * a*a*pow(iA, 3) + 105 * a*pow(iA, 4) + 91 * pow(iA, 5)))/1456 *3.0;
	//res = 0.1875*(pow(iB - a, 1 / 3.0) * (pow(iB, 5) + 2.88462*pow(iB, 4) + 8.65385*pow(iB, 3) + 27.8159*iB*iB + 104.31*iB + 782.323) - pow(iA - a, 1 / 3.0) * (pow(iA, 5) + 2.88462*pow(iA, 4) + 8.65385*pow(iA, 3) + 27.8159*iA*iA + 104.31*iA + 782.323));
	res = 3 / 16.0  * pow(iB - a, 16 / 3.0) + 75 / 26.0  * pow(iB - a, 13 / 3.0) + 75 / 4.0  * pow(iB - a, 10 / 3.0) + 1875 / 28.0  * pow(iB - a, 7/ 3.0) + 9375 / 64.0  * pow(iB - a, 4 / 3.0) + 9375 / 32.0  * pow(iB - a, 1 / 3.0) - (3/ 16.0  * pow(iA - a, 16 / 3.0) + 75 / 26.0  * pow(iA - a, 13 / 3.0) + 75 / 4.0  * pow(iA - a, 10 / 3.0) + 1875 / 28.0  * pow(iA - a, 7/ 3.0) + 9375 / 64.0  * pow(iA - a, 4 / 3.0) + 9375/ 32.0  * pow(iA - a, 1 / 3.0));

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
	double p = a[1] - a[0] * a[0] / 3.0; // p = b - a^2/3
	double q = a[2] + 2* a[0] * a[0] * a[0] / 27.0 - a[0] * a[1] / 3.0; // q = c + 2a^3/27 - ab/3
	double determinant = q * q / 4 + p * p * p / 27.0;

	if (determinant < 0)
	{
		/*cout << " Det < 0 " << endl;*/
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
		/*cout << " Det > 0 " << endl;*/
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

