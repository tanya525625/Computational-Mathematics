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
	int n = 3;
	double h = (b - a) / n;
	double res1;
	res1 = NewtonCotesMethod(a, b, aa, bb, h);
	cout << "Exact value of the integral: " << exactValue << endl;
	cout << endl;

	cout << "Value of the integral, which was calculated by Newton-Cotes method: " << res1 << endl;
	cout << "The exact error: " << abs(exactValue - res1) << endl;
	cout << "The methodical error: " << metodicError << endl;
	cout << endl;

	double h2 = IKFSpecifiedAccuracy(a, b, aa, bb, L,  m, Rh2, h, eps);
	double res2 = NewtonCotesMethod(a, b, aa, bb, h2);
	cout << "Value of the integral, which was calculated after calculated step by Aitken method: " << res2 << endl;
	cout << "The exact error: " << abs(exactValue - res2) << endl;
	cout << endl;

	int n1 = 1;
	
	double hOpt = findHopt(a, b, aa, bb, L, n1, eps);
	double res3 = NewtonCotesMethod(a, b, aa, bb, hOpt);
	cout << "Value of the integral, which was calculated after calculated Optimal step: " << res3 << endl;
	cout << "The exact error: " << abs(exactValue - res3) << endl;
	cout << endl;

	double res4;
	res4 = GaussMethod(a, b, aa, bb, h);
	metodicError = 0.000617531;
	cout << "Exact value of the integral: " << res4 << endl;
	cout << endl;
	cout << "Value of the integral, which was calculated by Gauss method: " << res4 << endl;
	cout << "The exact error: " << abs(exactValue - res4) << endl;
	cout << "The methodical error: " << metodicError << endl;
	cout << endl;

	h2 = IKFSpecifiedAccuracyGauss(a, b, aa, bb, L, m, Rh2, h, eps);
	double res5 = GaussMethod(a, b, aa, bb, h2);
	cout << "Value of the integral by Gauss, which was calculated after calculated step by Aitken method: " << res5 << endl;
	cout << "The exact error: " << abs(exactValue - res5) << endl;
	cout << endl;

	int n2 = 1;
	hOpt = findHoptGauss(a, b, aa, bb, L, n2, eps);
	res5 = GaussMethod(a, b, aa, bb, hOpt);
	cout << "Value of the integral, which was calculated after  Optimal step: " << res5 << endl;
	cout << "The exact error: " << abs(exactValue - res5) << endl;
	cout << endl;

	system("pause");
	return 0;
}