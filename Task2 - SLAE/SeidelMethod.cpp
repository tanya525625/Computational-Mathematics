#include "SeidelMethod.h"



SeidelMethod::SeidelMethod(Array _matrix)
{
	matrix = Array(_matrix.n, _matrix.m);
	matrix.n = _matrix.n;
	matrix.m = _matrix.m;
	n = _matrix.n;
	m = _matrix.m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			matrix.arr[i][j] = _matrix.arr[i][j];
	
	b = new double[n];
	b = _matrix.b;
}

SeidelMethod::~SeidelMethod()
{
}

double* SeidelMethod::SLAESolution()
{
	double eps = 1e-8;
	int k = 0;
	double* pre = new double[m];
	for (int i = 0; i < m; i++)
		pre[i] = 0;

	double* x = new double[m];
	for (int i = 0; i < m; i++)
		x[i] = 0; //Начальное приближение


	double normVal = 0;

	do
	{
		k++;
		for (int i = 0; i < n; i++)
			pre[i] = x[i];

		for (int i = 0; i < n; i++)
		{
			double var = 0;
			for (int j = 0; j < i; j++)
				var += (matrix.arr[i][j] * x[j]);
			for (int j = i + 1; j < n; j++)
				var += (matrix.arr[i][j] * pre[j]);
			if (matrix.arr[i][i] != 0)
			x[i] = (b[i] - var) / matrix.arr[i][i];
		}
	} while (!(*this).isConverge(x, pre, eps)); //Пока система не начнет сходится

	
	normVal = norm(x, matrix, b);
	cout << "The solution of the SLAE by Seidel method is done. The norm is " << normVal << ". The number of iterations is " << k << endl;

	return x;
}

bool SeidelMethod::isConverge(double *xk, double *xkp, double eps) // Условие окончания
{
	
	double norm = 0;
	for (int i = 0; i < n; i++)
	{
		norm += (xk[i] - xkp[i])*(xk[i] - xkp[i]);
	}
	if (sqrt(norm) >= eps)
		return false;
	else
		return true;
}

double* SeidelMethod::SLAEJacobiSolution()
{
	double* pre = new double[m];
	double normVal = 0;
	double eps = 1e-8; //Точность
	double* x = new double[m];
	int k = 0;  //Количество итераций
	for (int i = 0; i < m; i++)
		x[i] = 0; //Начальное приближение

	do {
		k++;
		for (int i = 0; i < n; i++) 
		{
			pre[i] = b[i]; 
			for (int j = 0; j < n; j++)
			{
				if (i != j)
					pre[i] -= matrix.arr[i][j] * x[j];
			}
			pre[i] = pre[i] / matrix.arr[i][i];
		}
		normVal = abs(x[0] - pre[0]);
		for (int k = 0; k < n; k++) 
		{
			if (abs(x[k] - pre[k]) > normVal)
				normVal = abs(x[k] - pre[k]);
			x[k] = pre[k];
		}
	} while (normVal > eps);

	normVal = norm(x, matrix, b);
	
	cout << "The solution of the SLAE by Jacobi method is done. The norm is " << normVal << ". The number of iterations is " << k << endl;

	return x;
}

double SeidelMethod:: norm(double *x, Array matrix, double* b)
{
	double normVal = 0;
	double* temp = new double[n];
	for (int i = 0; i < n; i++)
		temp[i] = 0;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			temp[i] += matrix.arr[i][j] * x[j];
		}
	cout.precision(10);
	for (int i = 0; i < n; i++)
	{
		normVal = normVal + (temp[i] - b[i])*(temp[i] - b[i]);
	}
	normVal = sqrt(normVal);

	return normVal;
}

//Норма невязки: ||Ax-b|| 
//Количество итераций