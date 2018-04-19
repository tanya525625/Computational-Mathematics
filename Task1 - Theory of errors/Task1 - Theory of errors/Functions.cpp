#include "Header.h"

double classFunc (double x)
{
	double sinTerm = 0.74; 
	double sinhFactor = 0.8*x; 
	double sinhTerm = 0.1; 
	return sqrt(sin(x + sinTerm)) * sinh(sinhFactor*x + sinhTerm);
}

double myFunc (double x)
{
	int w0 = 1;
	double w1 = 0.5 * (w0 + mySin(x) / w0);
	double err = abs(w1 - w0)*mySh(x);
	int k = 1;
	double vych = 0;
	while (err > e3)
	{
		vych = mySqrt(mySin(x), k)*mySh(x);
		err = abs(mySqrt(mySin(x), k) - mySqrt(mySin(x), k - 1))*mySh(x);
		k++;
	}
	return vych;
}

double mySqrt(double x, int k)   
{
	if (k == 0)       //Рекурсивный споспоб вычисления квадратного корня
		return 1;
	else 
		return 0.5 * (mySqrt(x, k - 1) + x / mySqrt(x, k - 1));
}

double mySin (double x)
{
	double sinTerm = 0.74;
	double y = (pi / 2 - (x + sinTerm)); //Приведение аргумента для дальнейшего подсчета через косинус
	int k = 0;
	double err = abs(pow(y, 2*k) / factorial(2*k));
	double vych = 0;
	
	while (err > e1) 
	{
		
		vych = vych + pow(-1, k)*pow(y, 2 * k) / factorial(2 * k); //Разложение функции cos в ряд
		err = pow(y, 2 * k) / factorial(2 * k);
		k++;
	}
	return vych;
}

double mySh(double x)
{
	double sinhFactor = 0.8*x;
	double sinhTerm = 0.1;
	double t = sinhFactor*x + sinhTerm;
	int k = 0;
	double err = pow(t, 2 * k + 1) / factorial(2 * k + 1);
	double vych = 0;

	while (err > e2)
	{
		
		vych = vych + pow(t, 2 * k + 1) / factorial(2 * k + 1); //Разложение функции sh в ряд
		err = pow(t, 2 * k + 1) / factorial(2 * k + 1);
		k++;
	}
	return vych;
}

int factorial(int i)
{
	if (i == 0) return 1;
	else return i*factorial(i - 1);
}
