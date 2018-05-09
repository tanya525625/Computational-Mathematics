#include "Header.h"

int main()
{
	double exactValue = 7.71357;
	double metodicError = 0.0043;
	double a = 2.5;
	double aa = 2 / 3;
	double bb = 0;
	double b = 3.3;
	int n = 100;
	double h = (b - a) / n;
	double approxValue;
	/*approxValue = middleRectanglesMethod(a, b, n);*/
	approxValue = NewtonCotesMethod(a, b, aa, bb, h);
	cout << "Exact value of the integral: " << exactValue << endl;
	cout << endl;

	cout << "Value of the integral, which was calculated by Newton-Cotes method: " << approxValue << endl;
	cout << "The exact error: " << abs(exactValue - approxValue) << endl;
	cout << "The methodical error: " << metodicError << endl;
	cout << endl;

	double res2 = IKFSpecifiedAccuracy(a, b, aa, bb, h);
	cout << "Value of the integral, which was calculated after calculated step by Aitken method: " << res2 << endl;
	cout << "The exact error: " << abs(exactValue - res2) << endl;
	cout << endl;





	system("pause");
	return 0;
}