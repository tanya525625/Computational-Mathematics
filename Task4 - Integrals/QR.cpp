#include "Header.h"


QR::QR(Array _matrix, int _n)
{
	n = _n;
	Q = Array();
	R = Array();
	matrix = _matrix;
	b = new double[n];
	b = _matrix.b;
}

QR:: ~QR()
{

}

void QR::decomposition()
{
	Array T(n, n);
	Q = Q.createIdentArr();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			R.arr[i][j] = matrix.arr[i][j];
	double* tmp = new double[n];

	double* tmp1 = new double[4];
	double* tmp2 = new double[2];
	double c = 1;
	double s = 0;
	double c12 = 1;
	double s12 = 0;
	for (int i = 0; i<n - 1; i++)
		for (int j = i + 1; j < n; j++)
		{
			for (int i = 0; i < n; i++)
				tmp[i] = b[i];

			T = T.createIdentArr(); //Ñîçäàíèå åäèíè÷íîé ìàòðèöû
			double sqrtC = sqrt(pow(R.arr[i][i], 2) + pow(R.arr[j][i], 2));
			c = R.arr[i][i] / sqrtC;
			s = R.arr[j][i] / sqrtC;
			T.arr[i][i] = c;
			T.arr[i][j] = s;
			T.arr[j][i] = -s;
			T.arr[j][j] = c;
			T.nullTest();


			R = T*R;

			b[i] = c*tmp[i] + s*tmp[j]; //Óìíîæåíèå ìàòðèöû T íà âåêòîð b 
			b[j] = -s*tmp[i] + c*tmp[j];

			T = T.transpose(); //Òðàíñïîíèðîâàíèå ìàòðèöû T

			Q = Q*T;

		}
	//Array L = Q*R;
	//if (L == matrix)
	//{
	//	cout << "QR-decomposition is done. Check is successful" << endl;
	//	cout << endl;
	//}
	Q = Q.transpose();

}