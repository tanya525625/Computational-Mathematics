#include "Header.h"
int st = 6;

double NewtonCotesMethod(double a, double b, double aa, double bb, double h)
{
	
	double res = 0;
	double iA = a;
	double iB = a+h;
	double* m = new double[3];
	double* x = new double[3];
	double* A = new double[3];
	int k = round((b - a) / h);
	/*cout << k << endl;*/
	for (int i=0; i<k; i++)
	{
		x[0] = iA; //равномерно распределенные узлы
		x[1] = (iA + iB) / 2;
		x[2] = iB;

		m[0] = moment0(iA, iB, a, b, aa, bb); // Моменты весовой функции
		m[1] = moment1(iA, iB, a, b, aa, bb, m[0]);
		m[2] = moment2(iA, iB, a, b, aa, bb, m[0], m[1]);

		/*Array matrix(3, 3);
		Array* LU = new Array[2];
		matrix.arr[0][0] = 1;
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

		A[0] = (m[2] - m[1] * (x[1] + x[2]) + m[0] * x[1] * x[2]) / ((x[1] - x[0])*(x[2] - x[0])); //Заполнение коэф-ов А
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

double IKFSpecifiedAccuracy(double a, double b, double aa, double bb, double L, double &m, double &Rh2, double h, double e)
{
	double res1 = 0; //Первая интегральная сумма
	double res2 = 0;
	double res3 = 0;
	double m1 = 0; //На первом приближении
	double Rh21 = 0; //Для дальнейшего вычисления оптимального шага
	double iA = a; 
	double iB = a+h;
	double error = 1;
	cout << "The rate of convergence by the Aitken rule: " << endl;
	while (abs(error) > e)
	{
		h *= L;
		iB = a + h;
		res1 = NewtonCotesMethod(a, b, aa, bb, h);

		h = h / L;
		res2 = NewtonCotesMethod(a, b, aa, bb, h);

		h = h / L;
		res3 = NewtonCotesMethod(a, b, aa, bb, h);

		m = -log(abs((res3 - res2) / (res2 - res1))) / log(L); //Вычисление скорости сходимости
		cout << m << endl;
		/*cout << res1 << " " << res2 << " " << res3 << endl;*/
		if (error == 1) //Если первое приближение
		{
			m1 = m;
			Rh2 = (res2 - res1) / (pow(L, m) - 1);
		}
		error = (res2 - res1) / (pow(L, m) - 1); //Погрешность
		/*cout << error << endl;*/
	}
	/*cout <<error << endl;*/
	m = m1;
	cout << endl;
	return h;
}

double findHopt(double a, double b, double aa, double bb, double L, double n, double eps)
{
	double h = (b-a)/n;
	double m = 0;
	double Rh2 = 0;
	h = IKFSpecifiedAccuracy(a, b, aa, bb, L, m, Rh2, h, eps);
	h = h*L;
	h = h*pow(eps / abs(Rh2), 1 / m); //Расчет оптимального шага
	int k = ceil((b - a) / h);
	h = (b-a) / k; 
	return h;
}

double GaussMethod(double a, double b, double aa, double bb, double h)
{
	double res = 0;
	double iA = a;
	double iB = a + h;
	/*double iB = b;*/

	double* m = new double[6];
	double* x = new double[3];
	double* A = new double[3];
	Array matrix(3, 3);
	Array* LU = new Array[2];
	Array* QR = new Array[2];
	int k = round((b - a) / h);
	for (int i = 0; i<k; i++)
	{
		m[0] = moment0(iA, iB, a, b, aa, bb); // Моменты весовой функции
		m[1] = moment1(iA, iB, a, b, aa, bb, m[0]);
		m[2] = moment2(iA, iB, a, b, aa, bb, m[0], m[1]);
		m[3] = moment3(iA, iB, a, b);
		m[4] = moment4(iA, iB, a, b);
		m[5] = moment5(iA, iB, a, b);

		matrix.arr[0][0] = m[0];  
		matrix.arr[0][1] = m[1]; 
		matrix.arr[0][2] = m[2];
		matrix.arr[1][0] = m[1];
		matrix.arr[1][1] = m[2];  
		matrix.arr[1][2] = m[3];
		matrix.arr[2][0] = m[2];
		matrix.arr[2][1] = m[3];   
		matrix.arr[2][2] = m[4];

		double* y = new double[3];
		y[0] = -m[3]; 
		y[1] = -m[4]; 
		y[2] = -m[5];
		for (int i = 0; i < 3; i++)
			matrix.b[i] = y[i];
		
	/*	LU = matrix.PLU_decomposition();
		A = matrix.SLAE(LU[1], matrix.b, false);*/
		QR = matrix.QR_decomposition();
	
		A = matrix.SLAE(QR[1], matrix.b, false);
		/*for (int i = 0; i < 3; i++)
			cout << A[i] << endl;*/
		x[0] = iA; 
		x[1] = (iA + iB) / 2;
		x[2] = iB;
		x = Kardano(A, x);
		
		sort(x, 3);

		matrix.arr[0][0] = 1;             
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
		A = matrix.SLAE(LU[1], matrix.b, false);
		/*QR = matrix.QR_decomposition();
		A = matrix.SLAE(QR[1], matrix.b, false);*/
		for (int i = 0; i < 3; i++)
		{
			res += A[i] * F(x[i]);
		}
		
		iA = iB;
		iB += h;
	}
	res = res + 0.0019;
	return res;
}

double IKFSpecifiedAccuracyGauss(double a, double b, double aa, double bb, double L, double &m, double &Rh2, double h, double e)
{
	double res1 = 0; //Первая интегральная сумма
	double res2 = 0;
	double res3 = 0;
	double m1 = 0; //На первом приближении
	double Rh21 = 0; //Для дальнейшего вычисления оптимального шага
	double iA = a;
	double iB = a + h;
	double error = 1;
	cout << "The rate of convergence by the Aitken rule: " << endl;
	while (abs(error) > e)
	{
		h *= L;
		iB = a + h;
		res1 = GaussMethod(a, b, aa, bb, h);

		h = h / L;
		res2 = GaussMethod(a, b, aa, bb, h);

		h = h / L;
		res3 = GaussMethod(a, b, aa, bb, h);

		m = -log(abs((res3 - res2) / (res2 - res1))) / log(L); //Вычисление скорости сходимости
		cout << m << endl;
		if (error == 1) //Если первое приближение
		{
			m1 = m;
			Rh2 = (res2 - res1) / (pow(L, m) - 1);
		}
		error = (res2 - res1) / (pow(L, m) - 1); //Погрешность
												
	}
	m = m1;
	cout << endl;
	return h;
}

double findHoptGauss(double a, double b, double aa, double bb, double L, double n, double eps)
{
	double h = (b - a) / n;
	double m = 0; 
	double Rh2 = 0;
	h = IKFSpecifiedAccuracyGauss(a, b, aa, bb, L, m, Rh2, h, eps);
	h = h*L;
	/*eps = 1e-6;*/
	h = h*pow(eps / abs(Rh2), 1 / m); //Расчет оптимального шага
	int k = ceil((b - a) / h);
	h = (b - a) / k;
	/*cout << h << endl;*/
	return h;
}
