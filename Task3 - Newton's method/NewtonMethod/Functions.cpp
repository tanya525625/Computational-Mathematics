#include "Header.h"

Array initialization(double* X) //Инициализация
{
	const int n = 10;
	Array F(n, 1);

	F.arr[0][0] = cos(X[0] * X[1]) - exp(-3.0 * X[2]) + X[3] * X[4] * X[4] - X[5] - sinh(2.0 * X[7]) * X[8] + 2.0 * X[9] + 2.0004339741653854440;
	F.arr[1][0] = sin(X[0] * X[1]) + X[2] * X[8] * X[6] - exp(-X[9] + X[5]) + 3.0 * X[4] * X[4] - X[5] * (X[7] + 1.0) + 10.886272036407019994;
	F.arr[2][0] = X[0] - X[1] + X[2] - X[3] + X[4] - X[5] + X[6] - X[7] + X[8] - X[9] - 3.1361904761904761904;
	F.arr[3][0] = 2.0 * cos(-X[8] + X[3]) + X[4] / (X[2] + X[0]) - sin(X[1] * X[1]) + cos(X[6] * X[9]) * cos(X[6] * X[9]) - X[7] - 0.1707472705022304757;
	F.arr[4][0] = sin(X[4]) + 2.0 * X[7] * (X[2] + X[0]) - exp(-X[6] * (-X[9] + X[5])) + 2.0 * cos(X[1]) - 1.00 / (X[3] - X[8]) - 0.3685896273101277862;
	F.arr[5][0] = exp(X[0] - X[3] - X[8]) + X[4] * X[4] / X[7] + cos(3.0 * X[9] * X[1]) / 2.0 - X[5] * X[2] + 2.0491086016771875115;
	F.arr[6][0] = X[1] * X[1] * X[1] * X[6] - sin(X[9] / X[4] + X[7]) + (X[0] - X[5]) * cos(X[3]) + X[2] - 0.7380430076202798014;
	F.arr[7][0] = X[4] * (X[0] - 2.0 * X[5]) * (X[0] - 2.0 * X[5]) - 2.0 * sin(-X[8] + X[2]) + 1.5 * X[3] - exp(X[1] * X[6] + X[9]) + 3.5668321989693809040;
	F.arr[8][0] = 7.0 / X[5] + exp(X[4] + X[3]) - 2.0 * X[1] * X[7] * X[9] * X[6] + 3.0 * X[8] - 3.0 * X[0] - 8.4394734508383257499;
	F.arr[9][0] = X[9] * X[0] + X[8] * X[1] - X[7] * X[2] + sin(X[3] + X[4] + X[5]) * X[6] - 0.78238095238095238096;

	return F;
}

Array initializationJ(double* X) //Инициализация
{
	const int n = 10;
	Array J(n, n);
	J.arr[0][0] = -sin(X[0] * X[1]) * X[1];
	J.arr[0][1] = -sin(X[0] * X[1]) * X[0];
	J.arr[0][2] = 3 * exp(-(3 * X[2]));
	J.arr[0][3] = X[4] * X[4];
	J.arr[0][4] = 2 * X[3] * X[4];
	J.arr[0][5] = -1;
	J.arr[0][6] = 0;
	J.arr[0][7] = -2 * cosh((2 * X[7])) * X[8];
	J.arr[0][8] = -sinh((2 * X[7]));
	J.arr[0][9] = 2;
	J.arr[1][0] = cos(X[0] * X[1]) * X[1];
	J.arr[1][1] = cos(X[0] * X[1]) * X[0];
	J.arr[1][2] = X[8] * X[6];
	J.arr[1][3] = 0;
	J.arr[1][4] = 6 * X[4];
	J.arr[1][5] = -exp(-X[9] + X[5]) - X[7] - 0.1e1;
	J.arr[1][6] = X[2] * X[8];
	J.arr[1][7] = -X[5];
	J.arr[1][8] = X[2] * X[6];
	J.arr[1][9] = exp(-X[9] + X[5]);
	J.arr[2][0] = 1;
	J.arr[2][1] = -1;
	J.arr[2][2] = 1;
	J.arr[2][3] = -1;
	J.arr[2][4] = 1;
	J.arr[2][5] = -1;
	J.arr[2][6] = 1;
	J.arr[2][7] = -1;
	J.arr[2][8] = 1;
	J.arr[2][9] = -1;
	J.arr[3][0] = -X[4] * pow(X[2] + X[0], -2);
	J.arr[3][1] = -2 * cos(X[1] * X[1]) * X[1];
	J.arr[3][2] = -X[4] * pow(X[2] + X[0], -2);
	J.arr[3][3] = -2 * sin(-X[8] + X[3]);
	J.arr[3][4] = 1 / (X[2] + X[0]);
	J.arr[3][5] = 0;
	J.arr[3][6] = -2 * cos(X[6] * X[9]) * sin(X[6] * X[9]) * X[9];
	J.arr[3][7] = -1;
	J.arr[3][8] = 2 * sin(-X[8] + X[3]);
	J.arr[3][9] = -2 * cos(X[6] * X[9]) * sin(X[6] * X[9]) * X[6];
	J.arr[4][0] = 2 * X[7];
	J.arr[4][1] = -2 * sin(X[1]);
	J.arr[4][2] = 2 * X[7];
	J.arr[4][3] = pow(-X[8] + X[3], -2);
	J.arr[4][4] = cos(X[4]);
	J.arr[4][5] = X[6] * exp((-X[6]) * (-X[9] + X[5]));
	J.arr[4][6] = -(X[9] - X[5]) * exp(-X[6] * (-X[9] + X[5]));
	J.arr[4][7] = (2 * X[2]) + 2 * X[0];
	J.arr[4][8] = -1 * pow(-X[8] + X[3], -2);
	J.arr[4][9] = -X[6] * exp(-X[6] * (-X[9] + X[5]));
	J.arr[5][0] = exp(X[0] - X[3] - X[8]);
	J.arr[5][1] = -3.0 / 2.0 * sin(3 * X[9] * X[1]) * X[9];
	J.arr[5][2] = -X[5];
	J.arr[5][3] = -exp(X[0] - X[3] - X[8]);
	J.arr[5][4] = 2 * X[4] / X[7];
	J.arr[5][5] = -X[2];
	J.arr[5][6] = 0;
	J.arr[5][7] = -X[4] * X[4] * pow(X[7], (-2));
	J.arr[5][8] = -exp(X[0] - X[3] - X[8]);
	J.arr[5][9] = -3.0 / 2.0 * sin(3 * X[9] * X[1]) * X[1];
	J.arr[6][0] = cos(X[3]);
	J.arr[6][1] = 3 * X[1] * X[1] * X[6];
	J.arr[6][2] = 1;
	J.arr[6][3] = -(X[0] - X[5]) * sin(X[3]);
	J.arr[6][4] = cos(X[9] / X[4] + X[7]) * X[9] * pow(X[4], (-2));
	J.arr[6][5] = -cos(X[3]);
	J.arr[6][6] = pow(X[1], 3);
	J.arr[6][7] = -cos(X[9] / X[4] + X[7]);
	J.arr[6][8] = 0;
	J.arr[6][9] = -cos(X[9] / X[4] + X[7]) / X[4];
	J.arr[7][0] = 2 * X[4] * (X[0] - 2 * X[5]);
	J.arr[7][1] = -X[6] * exp(X[1] * X[6] + X[9]);
	J.arr[7][2] = -2 * cos(-X[8] + X[2]);
	J.arr[7][3] = 0.15e1;
	J.arr[7][4] = pow(X[0] - 2 * X[5], 2);
	J.arr[7][5] = -4 * X[4] * (X[0] - 2 * X[5]);
	J.arr[7][6] = -X[1] * exp(X[1] * X[6] + X[9]);
	J.arr[7][7] = 0;
	J.arr[7][8] = 2 * cos(-X[8] + X[2]);
	J.arr[7][9] = -exp(X[1] * X[6] + X[9]);
	J.arr[8][0] = -3;
	J.arr[8][1] = -2 * X[7] * X[9] * X[6];
	J.arr[8][2] = 0;
	J.arr[8][3] = exp((X[4] + X[3]));
	J.arr[8][4] = exp((X[4] + X[3]));
	J.arr[8][5] = -0.7e1 * pow(X[5], -2);
	J.arr[8][6] = -2 * X[1] * X[7] * X[9];
	J.arr[8][7] = -2 * X[1] * X[9] * X[6];
	J.arr[8][8] = 3;
	J.arr[8][9] = -2 * X[1] * X[7] * X[6];
	J.arr[9][0] = X[9];
	J.arr[9][1] = X[8];
	J.arr[9][2] = -X[7];
	J.arr[9][3] = cos(X[3] + X[4] + X[5]) * X[6];
	J.arr[9][4] = cos(X[3] + X[4] + X[5]) * X[6];
	J.arr[9][5] = cos(X[3] + X[4] + X[5]) * X[6];
	J.arr[9][6] = sin(X[3] + X[4] + X[5]);
	J.arr[9][7] = -X[2];
	J.arr[9][8] = X[1];
	J.arr[9][9] = X[0];

	return J;
}

double* approximation(double* x, const int n)
{
	double* rez = new double[n];
	rez[0] = 0.5; 
	rez[1] = 0.5; 
	rez[2] = 1.5;
	rez[3] = -1; 
	rez[4] = -0.5;
	rez[5] = 1.5; 
	rez[6] = 0.5; 
	rez[7] = -0.5; 
	rez[8] = 1.5; 
	rez[9] = -1.5;

	return rez;
}

double* stMethNewt(double*X, const int n, Array F, Array J, double eps) //Стандартный метод Ньютона - 1
{
	double* Xk = new double[n];
	Array temp(n, 1);
	Array invJ(n, n);

	clock_t start = clock();
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		Xk[i] = 0;
		temp.arr[0][i] = 0;
	}
	X = approximation(X, n); //Начальное приближение
	
	Array* LU = new Array[2];
	bool isExcist = true; //Для невырожд. матрицы
	bool isCont = true;
	double diff = 0;
	while (isCont == true)
	{
		k++;
		diff = 0;
		J = initializationJ(X);
		F = initialization(X);
		LU = J.PLU_decomposition();
		invJ = J.inverseArray(LU[1], isExcist);
		temp = invJ*F;



		for (int i = 0; i < n; i++)
		{
			Xk[i] = X[i] - temp.arr[i][0];
			if (abs(Xk[i] - X[i]) > diff)
			{
				diff = abs(Xk[i] - X[i]);
			}
			X[i] = Xk[i];
		
			if (abs(diff) < eps)
				isCont = false;
		}

	} 
	clock_t end = clock();
	double time = (double) (end - start) / CLOCKS_PER_SEC;
	cout << "The number of iterations: " << k << endl;
	cout << "The time of method's implementation: " << time << endl;
	return X;
}

double* MethNewt(double*X, const int n, Array F, Array J, double eps) //Метод Ньютона Через PLU
{
	double* dX = new double[n];
	double* Xk = new double[n];
	double* tmp = new double[n];
	Array* LU = new Array[2];
	for (int i = 0; i < n; i++)
	{
		dX[i] = 0;
	}

	int k = 0; //Количество итераций
	bool isCont = true;
	double diff = 0;
	clock_t start = clock();
	X = approximation(X, n); //Начальное приближение

	while (isCont == true)
	{
		diff = 0;
		k++;
		F = initialization(X);
		J = initializationJ(X);
		for (int i = 0; i < n; i++)
		{
			J.b[i] = -F.arr[i][0];
		}
		LU = J.PLU_decomposition();
		dX = J.SLAE(LU[1], J.b, false);
		for (int i = 0; i < n; i++)
		{
			Xk[i] = X[i] + dX[i];
			
			if (abs(Xk[i] - X[i]) > diff)
			{
				diff = abs(Xk[i] - X[i]);
			}
			X[i] = Xk[i];
		}
		if (abs(diff) < eps)
			isCont = false;
	}
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "The number of iterations: " << k << endl;
	cout << "The time of method's implementation: " << time << endl;
	return X;
}

double* modifiedMethNewt(double*X, const int n, Array F, Array J, double eps) //Модифицированный метод Ньютона - 2
{
	double* dX = new double[n];
	double* Xk = new double[n];
	double* tmp = new double[n];
	Array* LU = new Array[2];
	for (int i = 0; i < n; i++)
	{
		dX[i] = 0;
	}
		
	int k = 0; //Количество итераций
	bool isCont = true;
	double diff = 0;
	clock_t start = clock();
	X = approximation(X, n); //Начальное приближение
	F = initialization(X);
	J = initializationJ(X);

	LU = J.PLU_decomposition();
	
	while (isCont == true)
	{
		diff = 0;
		k++;
		F = initialization(X);
		
		F = convertingVect(F, LU[0], J.P);
		for (int i = 0; i < n; i++)
		{
			J.b[i] = F.arr[i][0];
		}
		
		dX = J.SLAE(LU[1], J.b, false);
		for (int i = 0; i < n; i++)
		{
			Xk[i] = X[i] - dX[i];
			if (abs(Xk[i] - X[i]) > diff)
			{
				diff = abs(Xk[i] - X[i]);
			}
			X[i] = Xk[i];
		}
			
		if (abs(diff) < eps)
			isCont = false;
	}
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "The number of iterations: " << k << endl;
	cout << "The time of method's implementation: " << time << endl;
	return X;
}

double* automaticModifiedMethNewt(double*X, const int n, Array F, Array J, double eps)
{
	double* dX = new double[n];
	double* Xk = new double[n];
	double* tmp = new double[n];
	Array* LU = new Array[2];
	for (int i = 0; i < n; i++)
	{
		dX[i] = 0;
	}

	int k = 0; //Количество итераций
	bool isCont = true;
	double diff = 0;
	clock_t start = clock();
	X = approximation(X, n); //Начальное приближение

	while (isCont == true)
	{
		F = initialization(X);

		if ( diff > eps * 1000 || diff == 0)
		{
			J = initializationJ(X);
			for (int i = 0; i < n; i++)
			{
				J.b[i] = -F.arr[i][0];
			}
			LU = J.PLU_decomposition();

		}
		else
		{
			F = (-1) * F;
			F = convertingVect(F, LU[0], J.P);
			for (int i = 0; i < n; i++)
			{
				J.b[i] = F.arr[i][0];
			}
		}
		dX = J.SLAE(LU[1], J.b, false);
		diff = 0;
		for (int i = 0; i < n; i++)
		{
			Xk[i] = X[i] + dX[i];

			if (abs(Xk[i] - X[i]) > diff)
			{
				diff = abs(Xk[i] - X[i]);
			}
			X[i] = Xk[i];
		}
		k++;
		if (abs(diff) < eps)
			isCont = false;
	}
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "The number of iterations: " << k << endl;
	cout << "The time of method's implementation: " << time << endl;
	

	return X;
}

double* hybridModifiedMethNewt(double*X, const int n, Array F, Array J, double eps)
{
	double* dX = new double[n];
	double* Xk = new double[n];
	double* tmp = new double[n];
	Array* LU = new Array[2];
	for (int i = 0; i < n; i++)
	{
		dX[i] = 0;
	}

	int k = 0; //Количество итераций
	bool isCont = true;
	double diff = 0;
	clock_t start = clock();
	X = approximation(X, n); //Начальное приближение

	while (isCont == true)
	{
		diff = 0;
		int reuser = 2; //Регулятор перехода на модифицированный метод
		
		F = initialization(X);
		
		if (k % reuser == 0)
		{
			J = initializationJ(X);
			for (int i = 0; i < n; i++)
			{
				J.b[i] = -F.arr[i][0];
			}
			LU = J.PLU_decomposition();
			
		}
		else
		{
			F = (-1) * F;
			F = convertingVect(F, LU[0], J.P);
			for (int i = 0; i < n; i++)
			{
				J.b[i] = F.arr[i][0];
			}
		}
		dX = J.SLAE(LU[1], J.b, false);
		for (int i = 0; i < n; i++)
		{
			Xk[i] = X[i] + dX[i];

			if (abs(Xk[i] - X[i]) > diff)
			{
				diff = abs(Xk[i] - X[i]);
			}
			X[i] = Xk[i];
		}
			k++;
			if (abs(diff) < eps)
				isCont = false;
	}
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "The number of iterations: " << k << endl;
	cout << "The time of method's implementation: " << time << endl;


	return X;
}


double norm(double *x, double* b, int n)
{
	double normVal = 0;
	double* temp = new double[n];
	for (int i = 0; i < n; i++)
		temp[i] = 0;

	for (int i = 0; i < n; i++)
	{
		normVal = normVal + (temp[i] - b[i])*(temp[i] - b[i]);
	}
	normVal = sqrt(normVal);

	return normVal;
}

Array convertingVect(Array F, Array L, int* P) //Изменение вектора в соответствии с проведенными преобразованиями над системой
{
	Array tmpL(F.n, F.n);
	tmpL = tmpL.createIdentArr();
	for (int i = 0; i < F.n; i++)
	{
		for (int j = 0; j < i; j++)
			if (abs(L.arr[i][j]) != 0)
				tmpL.arr[i][j] = -L.arr[i][j];
	}

	double temp = 0;
	Array tmp(F.n, 1);

	for (int i = 0; i < F.n ; i++)  //Перестановка строк
	{
		tmp.arr[i][0] = F.arr[P[i]][0];
	}

	Array rez(F.n, 1);
	int j = 0;

	for (int i = 0; i < F.n; i++)
	{
		for (j = 0; j < F.m; j++)
		{
			
			for (int k = 0; k < F.n; k++)
			{
				
				rez.arr[i][j] += tmpL.arr[i][k] * tmp.arr[k][j];
				
			}
		}
		tmp.arr[i][j-1] = rez.arr[i][j-1];
	}
	return rez;
} 