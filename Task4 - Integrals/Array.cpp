#include "Header.h"

Array::Array()
{
	numTransp = 0;
	n = 3;
	m = 3;

	identArr = new double*[n];
	arr = new double*[n];
	lead = new int[n];
	b = new double[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new double[m];
		identArr[i] = new double[n];
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			arr[i][j] = i+j+1;

	for (int i = 0; i < n; i++)
	{
		lead[i] = 0;
		b[i] = 0;
	}
}

Array::Array(int _n, int _m)
{
	numTransp = 0;
	n = _n;
	m = _m;
	if (n > m)
		Rank = _n;
	else
		Rank = _m;
	identArr = new double*[n];
	arr = new double*[n];
	lead = new int[n];
	b = new double[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new double[m];
		identArr[i] = new double[n];
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			arr[i][j] = 0;

	for (int i = 0; i < n; i++)
	{
		lead[i] = 0;
		b[i] = 0;
	}



	P = new int[n];  //������ ������� ������������, ������������ ������������ ����� ��������� �������
	for (int i = 0; i < n; i++)
		P[i] = i;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
				identArr[i][j] = 1;
			else
				identArr[i][j] = 0;

}

Array::~Array()
{
	//for (int i = 0; i < n; i++)
	//{
	//	delete[] arr[i];
	//}
	//delete[] arr;
}

Array Array::generPosDeterm()
{
	Array temp(true);
	Array rez(temp.n, temp.n);
	Array mult(temp.n, temp.n);
	Array* LU = new Array[2];
	Array invArr(temp.n, temp.n);

	LU = temp.PLU_decomposition();
	bool isExcist = 1;
	invArr = temp.inverseArray(LU[1], isExcist);
	for (int i = 0; i < temp.n; i++)
		rez.arr[i][i] = i + 1;
	mult = temp*rez;
	rez = mult*invArr;
	/*rez.print();*/

	for (int i = 0; i < temp.n; i++)
	{
		rez.b[i] = temp.b[i];
		/*cout << rez.b[i] << endl;*/
	}


	return rez;
}

Array::Array(bool isRandom)
{
	srand((unsigned int)time(NULL));
	/*n = rand() % 50 + 3;*/
	n = 3;
	m = n;
	identArr = new double*[n];
	arr = new double*[n];
	lead = new int[n];
	b = new double[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new double[m];
		identArr[i] = new double[n];
	}

	for (int i = 0; i < n; i++)
	{
		lead[i] = 0;
		b[i] = rand() % 100 * pow(-1, rand()) + 1;
	}



	P = new int[n];  //������ ������� ������������, ������������ ������������ ����� ��������� �������
	for (int i = 0; i < n; i++)
		P[i] = i;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
				identArr[i][j] = 1;
			else
				identArr[i][j] = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			arr[i][j] = rand() % 100 * pow(-1, rand());

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			arr[i][i] += abs(arr[i][j]);
		}
		b[i] = rand() % 100 * pow(-1, rand());
	}


}

void Array::print()
{
	cout << fixed;
	cout.precision(3);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}

}

void Array::printB()
{
	for (int i = 0; i < n; i++)
		cout << b[i] << endl;

}

Array operator *(Array &a1, Array &a2)
{
	Array rez(a1.n, a2.m);

	if (a1.m == a2.n)
	{
		for (int i = 0; i < a1.n; i++)
		{
			for (int j = 0; j < a2.m; j++)
			{
				for (int k = 0; k < a2.n; k++)
				{
					rez.arr[i][j] += a1.arr[i][k] * a2.arr[k][j];
				}
			}
		}

	}
	/*else
	{
	cout << "ERROR. Matrices can not be multiplied" << endl;

	}*/
	rez.nullTest();
	return rez;
}

Array operator *(double c, Array a)
{
	Array rez = a;
	for (int i = 0; i < rez.n; i++)
		for (int j = 0; j < rez.m; j++)
			rez.arr[i][j] = rez.arr[i][j] * c;
	return rez;
}

double* operator *(Array a, double*  x) //��������� ������� �� ������
{
	double* rez = new double[a.n];
	if (a.m == a.n)
	{
		for (int i = 0; i < a.n; i++)
			for (int j = 0; j < a.m; j++)
			{
				rez[i] += a.arr[i][j] * x[j];
			}


	}

	return rez;
}

bool operator == (Array a1, Array a2)
{
	bool isEqual = 1;
	if ((a1.n == a2.n) && (a1.m == a2.m))
	{
		for (int i = 0; i < a1.n; i++)
			for (int j = 0; j < a1.m; j++)
				if ((abs(a1.arr[i][j] - a2.arr[i][j])) > 1e-8)
					isEqual = 0;
	}
	return isEqual;
}

Array* Array::PLU_decomposition()
{
	Array* rez = new Array[2];
	double max = 0;
	Array L(n, m);
	Array U(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			U.arr[i][j] = arr[i][j];
	int maxStr = 0;
	int k = 0; //C������ ��� ������ ������������� ������������� ��������
	int num = 0;

	double tmp = 0;
	while (k < n)
	{
		//����� ������������� �������� � �������
		max = abs(U.arr[k][k]);
		maxStr = k;
		num = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(U.arr[i][k]) > max)
			{
				max = abs(U.arr[i][k]);
				maxStr = i;
				numTransp++;
				for (int j = 0; j < n; j++)
				{
					double tmp = U.arr[k][j];
					U.arr[k][j] = U.arr[maxStr][j];
					U.arr[maxStr][j] = tmp;
					double tmpL = L.arr[k][j];
					L.arr[k][j] = L.arr[maxStr][j];
					L.arr[maxStr][j] = tmpL;
					double tmpIdent = identArr[k][j];
					identArr[k][j] = identArr[maxStr][j];
					identArr[maxStr][j] = tmpIdent;
				}
				tmp = P[k]; //��� 0
				P[k] = P[maxStr];
				P[maxStr] = tmp;
				tmp = b[k]; //��� 0
				b[k] = b[maxStr];
				b[maxStr] = tmp;
			}
		}



		for (int i = k; i < n; i++) //����� ������ 
		{
			while (U.arr[k][num] == 0)
			{
				num++;
				Rank--;
			}
			/*if (U.arr[k][num] != 0)
			{*/
			double d = U.arr[i][num] / U.arr[k][num];
			if (i != k)
			{
				b[i] = b[i] - b[k] * d; //k
			}
			for (int j = 0; j < m; j++)
			{
				if (i == k)  continue; //���� ������ �������� �������� ��������
				else
				{
					L.arr[i][k] = d; // k
					lead[k] = num;
					U.arr[i][j] = U.arr[i][j] - U.arr[k][j] * d;
					identArr[i][j] = identArr[i][j] - identArr[k][j] * d;
				}
			}
			/*}*/


		}
		k++;
	}


	for (int i = 0; i < n; i++) //���������� ��������� ������� 
	{
		for (int j = 0; j < m; j++)
		{
			if (i == j)
				L.arr[i][j] = 1;
		}
	}
	if (abs(determinant(U, false)) == 0) //������������ �����, ���� ���� �� ��� == 0 (����� ������� ���� ���������)
	{
		double* tmp = new double[n];
		bool isNull = true;
		for (int i = 0; i < n - 1; i++)
		{
			isNull = true;
			for (int j = 0; j < m; j++)
			{
				if (U.arr[i][j] != 0)
					isNull = false;
			}
			if (isNull == true)
			{
				tmp = U.arr[i + 1];
				U.arr[i + 1] = U.arr[i];
				U.arr[i] = tmp;
			}
		}
	}
	/*print();*/
	//��������
	Array arr2;
	Array arr1(n, m);

	arr1 = L*U;
	arr2 = arr2.transposition(P);


	/*if (arr1 == arr2)
	{
		cout << "PLU-decomposition is done. Check is successful" << endl;
		cout << endl;
	}*/


	rez[0] = L;
	rez[1] = U;


	return rez;
}

Array Array::transpose()
{
	Array tmpArray(m, n);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			tmpArray.arr[i][j] = arr[j][i];
	return tmpArray;
}

double** Array::transposeArr(double** arr)
{
	int tmpSize;
	double** tmpArray = new double*[n];
	for (int i = 0; i < n; i++)
	{
		tmpArray[i] = new double[n];
	}

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			tmpArray[i][j] = arr[j][i];
	return tmpArray;
}

Array Array::transposition(int* P)
{
	Array newArr(n, m);


	for (int i = 0; i < n; i++)
	{
		newArr.arr[i] = arr[P[i]];
	}

	return newArr;
}

double** Array::transpositionArr(int* P, double** arr)
{

	double** newArr = new double*[n]; //�������� ������������� ���������� ������� ��� ����������
	for (int i = 0; i < n; i++)
	{
		newArr[i] = new double[n];
	}

	for (int i = 0; i < n; i++)
	{
		newArr[i] = arr[P[i]];
	}


	return newArr;
}

void Array::transposition(double* b) //������������ ����� ��� �������
{
	double temp = 0;

	for (int i = 0; i <= (n / 2); i++)
	{
		temp = b[i];
		b[i] = b[P[i]];
		b[P[i]] = temp;
	}
}

double Array::determinant(Array U, bool isPrint)
{
	double det = 1;
	if (m != n)
	{
		cout << "The determinant doesn't excist" << endl;
		det = -0;
	}
	else
	{
		for (int i = 0; i < n; i++)
			det = det * U.arr[i][i];
		det = pow(-1, numTransp)*det; //����� ����� � ������������ � ����������� ��� ������������ �����
		if (abs(det) < 1e-10)
			det = abs(det);
		if (isPrint == true)
		{
			cout << endl;
			cout << "The determinant of the array: " << det << endl;
		}

	}



	return det;
}

int Array::rank(Array U)
{
	int rank = 0;
	int k = 0;
	bool isNull = true;
	for (int i = 0; i < n; i++)
	{
		isNull = true;
		for (int j = 0; j < m; j++)
		{
			if (abs(U.arr[i][j]) > 1e-12)
				isNull = false;
		}
		if (isNull == true)
			k++;
	}
	rank = n - k;
	return rank;
}

Array Array::inverseArray(Array U, bool &isExcist)
{
	Array rez(n, m);
	double** newIdentArr = new double*[n]; //�������� ������������� ���������� ������� ��� ��������������� ��. �-��
	for (int i = 0; i < n; i++)
	{
		newIdentArr[i] = new double[n];
	}

	/*for (int i=0; i<n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i != j)
				newIdentArr[i][j] = 0;
			else
				newIdentArr[i][j] = 1;
		}*/

	if (determinant(U, false) == 0 || m != n) //���� ������������ ����� 0 ��� ������� �� �������� ����������
	{
		cout << "The inverse arr does not exist" << endl;
		isExcist = 0;
	}
	else
	{
		newIdentArr = transposeArr(identArr); //���������������� ��������� �������
		for (int i = 0; i < n; i++) //������� ����
			rez.arr[i] = SLAE(U, newIdentArr[i], false);
		rez = rez.transpose(); //���������������� ���������� �������

		//Array comp1;
		//Array comp2;
		//comp1 = comp1 * rez;
		//comp2 = rez * comp2;
		//comp1.nullTest();
		//comp2.nullTest();
		//rez.nullTest();
		/*if (comp1 == comp2)
			cout << "The inverse arr is obtained. Check is successful" << endl;*/
	}

	return rez;
}

double* Array::SLAE(Array U, double* b, bool isPrint)
{
	Array extArr(n, m + 1);  //�������� � ���������� ����������� �������
	for (int i = 0; i<n; i++)
		for (int j = 0; j < m + 1; j++)
		{
			if (j == m)
				extArr.arr[i][j] = b[i];
			else
				extArr.arr[i][j] = U.arr[i][j];

		}

	int rankExt = extArr.rank(extArr); // ���� ����������� �������
	int rankInit = rank(U); //���� �������� �������
	double* rez = new double[m];
	for (int i = 0; i < m; i++)
		rez[i] = 0;
	double sum = 0;

	if (rankExt == rankInit)  // ������� ��������� � �������
	{
		if (m > n)
		{
			for (int i = m - 1; i > n - 1; i--)
				rez[i] = 0;

		}
		/*else
		{*/
		int j = 0;
		for (int i = rankInit - 1; i >= 0; i--)
		{
			sum = 0;
			for (j = 0; j < m; j++)
			{
				sum = sum + rez[j] * U.arr[i][j];
			}
			if (U.arr[i][i] != 0)
				rez[i] = (b[i] - sum) / U.arr[i][i];
			else
			{
				rez[n + i - rankInit] = (b[i] - sum) / U.arr[i][lead[i]];   //��� ����������� ������
			}

			if (m > n)
			{
				rez[i + 1] = b[i] / U.arr[i][i + 1];
				rez[i] = 0;
			}
		}

		//for (int i = 0; i < n; i++)
		//{
		//	if (abs(rez[i]) <= 1e-8) //�������� �� ������������� ����
		//		rez[i] = abs(rez[i]);
		//}

		if (isPrint == true)
		{
			if (rankExt < n)
				cout << "Vector of one of the possible solutions: " << endl;
			else
				cout << "The solution: " << endl;
			for (int i = 0; i < m; i++)
				cout << rez[i] << endl;
		}
		bool isOk = true;
		for (int i = 0; i < n; i++)
			if (((U*rez)[i] - b[i]) >= 1e-10)
				isOk = false;
		if (isOk == true && isPrint == true)
			cout << "The solution of the SLAE is obtained. Check is successful" << endl;

		//}
	}
	else
		cout << "The system is incompatible" << endl;



	return rez;
}

double* Array::resultSLAE(Array U, bool isPrint) // ��� �������� ������ ������� SLAE
{
	double* rez = new double[n];
	for (int i = 0; i < n; i++)
		rez[i] = 0;
	rez = SLAE(U, b, isPrint);

	return rez;
}

void Array::nullTest() //��������� ������ �������������� 0
{
	for (int i = 0; i<n; i++)
		for (int j = 0; j < m; j++)
		{
			if (std::abs(arr[i][j]) <= 1e-5)
				arr[i][j] = abs(arr[i][j]);
		}
	//std::numeric_limits<double>::epsilon()
}

double Array::norm() //����� �� ��������
{
	double norm = 0;
	double* normArr = new double[m];
	for (int i = 0; i < m; i++)
		normArr[i] = 0;
	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < n; i++)
		{
			normArr[j] += abs(arr[i][j]);
		}
		if (abs(normArr[j]) > norm)
			norm = normArr[j];
	}
	return norm;
}

double Array::conditionNumber(Array U)
{
	Array arr1;
	double condN = 0;
	double normInvArr = 0; //����� �������� �������
	double normArr = arr1.norm(); //����� �������� �������
	if (arr1.determinant(U, false) != 0 && m == n)
	{
		bool isExcist = 1;
		Array invArr = inverseArray(U, isExcist); //����� �������� �������
		normInvArr = invArr.norm();
	}
	else
	{
		cout << "The inverse arr does not exist. Conditional of the array tends to infinity." << endl;
		normInvArr = pow(2, 8 * sizeof(double));
	}

	condN = normArr * normInvArr;

	return condN;
}

Array Array::createIdentArr()
{
	Array identArr(n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
				identArr.arr[i][j] = 1;
			else
				identArr.arr[i][j] = 0;
	return identArr;
}

Array* Array::QR_decomposition()
{
	Array* res = new Array[2];
	if (m == n)
	{
		QR QRDecArr((*this), n);
		QRDecArr.decomposition();
		res[0] = QRDecArr.Q;
		res[1] = QRDecArr.R;
		for (int i = 0; i<n; i++)
			b[i] = QRDecArr.b[i];
	}
	else
		cout << "QR_decomposition is impossible" << endl;
	/*res[0].print();
	res[1].print();*/
	return res;
}