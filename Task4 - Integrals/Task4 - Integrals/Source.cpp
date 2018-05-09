#include "Header.h"

int main()
{
	double exactValue = 7.71357;
	double metodicError = 0.0043;
	double eps = 1e-6;
	double a = 2.5;
	double aa = 2 / 3;
	double m = 0;
	double Rh2 = 0;
	double bb = 0;
	double b = 3.3;
	double L = 2;
	int n = 100;
	double h = (b - a) / n;
	double res1;
	res1 = NewtonCotesMethod(a, b, aa, bb, h);
	cout << "Exact value of the integral: " << exactValue << endl;
	cout << endl;

	cout << "Value of the integral, which was calculated by Newton-Cotes method: " << res1 << endl;
	cout << "The exact error: " << abs(exactValue - res1) << endl;
	cout << "The methodical error: " << metodicError << endl;
	cout << endl;

	double h2 = IKFSpecifiedAccuracy(a, b, aa, bb, L,  m, Rh2, h);
	cout << h2 << endl;
	double res2 = NewtonCotesMethod(a, b, aa, bb, h2);
	cout << "Value of the integral, which was calculated after calculated step by Aitken method: " << res2 << endl;
	cout << "The exact error: " << abs(exactValue - res2) << endl;
	cout << endl;

	int n1 = 1;
	int n2 = 2;
	int n3 = 4;
	
	double hOpt = findHopt(a, b, aa, bb, L, n1, eps);
	cout << hOpt << endl;
	hOpt = IKFSpecifiedAccuracy(a, b, aa, bb, L, m, Rh2, hOpt);
	cout << hOpt << endl;
	/*b = b + hOpt;*/
	double res3 = NewtonCotesMethod(a, b, aa, bb, hOpt);
	cout << "Value of the integral, which was calculated after calculated Optimal step: " << res3 << endl;
	cout << "The exact error: " << abs(exactValue - res3) << endl;
	cout << endl;

	system("pause");
	return 0;
}