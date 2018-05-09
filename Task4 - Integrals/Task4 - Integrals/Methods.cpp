#include "Header.h"

double NewtonCotesMethod(double a, double b, double aa, double bb, double h)
{
	
	double res = 0;
	double iA = a;
	Array matrix(3, 3);
	Array* LU = new Array[2];
	double iB = a+h;
	double* m = new double[3];
	double* x = new double[3];
	double* A = new double[3];
	while (iB <= b)
	{
		x[0] = iA; //равномерно распределенные узлы
		x[1] = (iA + iB) / 2;
		x[2] = iB;

		m[0] = moment0(iA, iB, a, b, aa, bb); // Моменты весовой функции
		m[1] = moment1(iA, iB, a, b, aa, bb, m[0]);
		m[2] = moment2(iA, iB, a, b, aa, bb, m[0], m[1]);

		/*matrix.arr[0][0] = 1;
		matrix.arr[0][1] = 1;
		matrix.arr[0][2] = 1;
		matrix.arr[1][0] = x[0];
		matrix.arr[1][1] = x[1];
		matrix.arr[1][2] = x[2];
		matrix.arr[2][0] = x[0] * x[0];
		matrix.arr[2][1] = x[1] * x[1];
		matrix.arr[2][2] = x[2] * x[2];
		for (int i = 0; i < 3; i++)
			matrix.b[i] = m[i];
		LU = matrix.PLU_decomposition();
		A = matrix.SLAE(LU[1], matrix.b, false);*/

		A[0] = (m[2] - m[1] * (x[1] + x[2]) + m[0] * x[1] * x[2]) / ((x[1] - x[0])*(x[2] - x[0]));
		A[1] = -(m[2] - m[1] * (x[0] + x[2]) + m[0] * x[0] * x[2]) / ((x[1] - x[0])*(x[2] - x[1]));
		A[2] = (m[2] - m[1] * (x[1] + x[0]) + m[0] * x[1] * x[0]) / ((x[2] - x[1])*(x[2] - x[0]));

		for (int i = 0; i < 3; i++)
		{
			res += A[i] * F(x[i]);
		}
		iA = iB;
		iB += h;
	}

	return res;
}

double IKFSpecifiedAccuracy(double a, double b, double aa, double bb, double h)
{
	double res1 = 0;
	double res2 = 0;
	double res3 = 0;
	double iA = a;
	double iB = a+h;
	double error = 1;
	double m = 0;
	double L = 2;
	double e = 1e-6;
	
	cout << "The rate of convergence by the Aitken rule: " << endl;
	while (error > e)
	{
		h *= L;
		iB = a + h;
		res1 = NewtonCotesMethod(iA, iB, aa, bb, h);

		h = h / L;
		res2 = NewtonCotesMethod(iA, iB, aa, bb, h);

		h = h / L;
		res3 = NewtonCotesMethod(iA, iB, aa, bb, h);

		m = -log(abs((res3 - res2) / (res2 - res1))) / log(L);
		error = res2 + (res2 - res1) / (pow(L, m) - 1);
		cout << error << endl;
	}
	cout << endl;
	res1 = NewtonCotesMethod(a, b, aa, bb, h);
	return res1;
}
