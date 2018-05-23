#include "HeaderSLAE.h"

Array::Array()
{
	ifstream fin("Matrix.txt");
	if (!fin.is_open())
	{
		cout << "File wasn't opened";
		fin.clear();
		n = 0; m = 0; 
		arr = new double*[n];
		identArr = new double*[n];
		for (int i = 0; i < n; i++)
		{
			arr[i] = new double[m];
			identArr[i] = new double[n];
		}
	}
	else
	{
		fin >> n;  fin >> m;
		arr = new double*[n];
		identArr = new double*[n];
		b = new double[n];
		lead = new int[n];
		for (int i = 0; i < n; i++)
		{
			arr[i] = new double[m];
			identArr[i] = new double[n];
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				fin >> arr[i][j];
		for (int i = 0; i < n; i++)
		{
			fin >> b[i];
			lead[i] = 0;
		}
			
		fin.close();

	}

	P = new int[n];  //Вектор матрицы перестановок, показывающий расположение строк единичной матрицы
	for (int i = 0; i < n; i++)
		P[i] = i;
	numTransp = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
				identArr[i][j] = 1;
			else
				identArr[i][j] = 0;
	if (n>m)
		Rank = n;
	else 
		Rank = m;
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
		


	P = new int[n];  //Вектор матрицы перестановок, показывающий расположение строк единичной матрицы
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
	/*for (int i = 0; i<n; ++i)
	{
		delete[] arr[i];
	}
	delete[] arr;*/
}

Array Array:: generPosDeterm()
{
	Array temp(true);
	Array res(temp.n, temp.n);
	Array mult(temp.n, temp.n);
	Array* LU = new Array[2];
	Array invArr(temp.n, temp.n);
	
	LU = temp.PLU_decomposition();
	bool isExcist = 1;
	invArr = temp.inverseArray(LU[1], isExcist);
	for (int i = 0; i < temp.n; i++)
		res.arr[i][i] = i + 1;
	mult = temp*res;
	res = mult*invArr;
	/*res.print();*/

	for (int i = 0; i < temp.n; i++)
	{
		res.b[i] = temp.b[i];
		/*cout << res.b[i] << endl;*/
	}
		

	return res;
}

Array::Array (bool isRandom)
{
	srand((unsigned int)time(NULL));
	n = rand() % 30 + 3;
	/*n = 5;*/
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



	P = new int[n];  //Вектор матрицы перестановок, показывающий расположение строк единичной матрицы
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
		b[i] = rand() % 100 * pow(-1, rand()) ;
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
			cout << arr[i][j] << "\t" ;
		}
		cout << endl;
	}
		
}

void Array::printB()
{
	for (int i = 0; i < n; i++)
		cout << b[i] <<  endl;

}

void Array::printP()
{
	for (int i = 0; i < n; i++)
		cout << P[i] << endl;

}

Array operator *(Array &a1, Array &a2)
{
	Array res(a1.n, a2.m);

	if (a1.m == a2.n)
	{
		for (int i = 0; i < a1.n; i++)
		{
			for (int j = 0; j < a2.m; j++)
			{
				for (int k = 0; k < a2.n; k++)
				{
					res.arr[i][j] += a1.arr[i][k] * a2.arr[k][j];
				}
			}
		}

	}
	/*else
	{
		cout << "ERROR. Matrices can not be multiplied" << endl;

	}*/
	res.nullTest();
	return res;
}

Array operator *(double c, Array a)
{
	Array res = a;
	for (int i = 0; i < res.n; i++)
		for (int j = 0; j < res.m; j++)
			res.arr[i][j] = res.arr[i][j] * c;
	return res;
}

double* operator *(Array a, double*  x) //Умножение матрицы на вектор
{
	double* res = new double[a.n];
	if (a.m == a.n)
	{
		for (int i = 0; i < a.n; i++)
			for (int j = 0; j < a.m; j++)
			{
				res[i] += a.arr[i][j] * x[j];
				/*cout << res[i] << endl;*/
			}
				
		
	}
	
	return res;
}

bool operator == (Array a1, Array a2)
{
	bool isEqual = 1;
	if ((a1.n == a2.n) && (a1.m == a2.m))
	{
		for (int i = 0; i < a1.n; i++)
			for (int j = 0; j < a1.m; j++)
				if ((abs(a1.arr[i][j] - a2.arr[i][j])) > 1e-8 )
					isEqual = 0;
	}
	return isEqual;
}

Array* Array::PLU_decomposition()
{
	Array* res = new Array[2];
	double max = 0;
	Array L(n, m);
	Array U (n, m) ;
	U.arr = arr;
	int maxStr = 0;
	int k = 0; //Cчетчик для поиска максимального диагонального элемента
	int num = 0;
	clock_t start = clock();
	double tmp = 0;
	while (k < n)
	{
		//Поиск максимального элемента в столбце
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
				tmp = P[k]; //Был 0
				P[k] = P[maxStr];
				P[maxStr] = tmp;
				tmp = b[k]; //Был 0
				b[k] = b[maxStr];
				b[maxStr] = tmp;
			}
		}
		


		for (int i = k; i < n; i++) //Метод Гаусса 
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
					if (i == k)  continue; //Если строка текущего ведущего элемента
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


	for (int i = 0; i < n; i++) //Построение единичной матрицы 
	{
		for (int j = 0; j < m; j++)
		{
			if (i == j)
				L.arr[i][j] = 1;
		}
	}
	if (abs(determinant(U, false)) == 0) //Перестановка строк, если одна из них == 0 (Чтобы нулевая была последней)
	{
		double* tmp = new double[n];
		bool isNull = true;
		for (int i = 0; i < n-1; i++)
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
	//Проверка
	Array arr2;
	Array arr1(n, m);

	arr1 = L*U;
	arr2 = arr2.transposition(P);
	
	
	if (arr1 == arr2)
	{
		cout << "PLU-decomposition is done. Check is successful" << endl;
		cout << endl;
	}
		

	res[0] = L;
	res[1] = U;
	
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "The time of method's implementation: " << time << endl;
	return res;
}

Array Array:: transpose()
{
	int tmpSize;
	Array tmpArray(m, n);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) 
			tmpArray.arr[i][j] = arr[j][i];
	return tmpArray;
}

double** Array::transposeArr(double** arr)
{
	int tmpSize;
	double** tmpArray = new double* [n];
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

	/*cout << endl*/;
	/*print();*/
	/*cout << endl;*/
	/*double* tmpArr = new double[n];*/
	for (int i = 0; i < n; i++)
	{
		newArr.arr[i] = arr[P[i]];
	}
	cout << endl;
	/*newArr.print();*/

	return newArr;
}

double** Array::transpositionArr(int* P, double** arr)
{

	double** newArr = new double*[n]; //Создание динамического двумерного массива для результата
	for (int i = 0; i < n; i++)
	{
		newArr[i] = new double[n];
	}

	for (int i = 0; i < n; i++)
	{
		newArr[i] = arr[P[i]];
	}
	cout << endl;


	return newArr;
}

void Array::transposition(double* b) //Перестановка строк для вектора
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
		det = pow(-1, numTransp)*det; //Смена знака в соответствии с количеством раз перестановки строк
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
	Array res(n, m);
	double** newIdentArr = new double*[n]; //Создание динамического двумерного массива для преобразованной ед. м-цы
	for (int i = 0; i < n; i++)
	{
		newIdentArr[i] = new double[n];
	}

	if (determinant(U, false) == 0 || m != n) //Если определитель равен 0 или матрица не является квадратной
	{
		cout << "The inverse matrix does not exist" << endl;
		isExcist = 0;
	}
	else
	{
		newIdentArr = transposeArr(identArr); //Транспонирование единичной матрицы
		for (int i = 0; i < n; i++) //Решение СЛАУ
			res.arr[i] = SLAE(U, newIdentArr[i], false);
		res = res.transpose(); //Транспонирование полученной матрицы

		Array comp1;
		Array comp2;
		comp1 = comp1 * res;
		comp2 = res * comp2;
		comp1.nullTest();
		comp2.nullTest();
		res.nullTest();
		if (comp1 == comp2)
			cout << "The inverse matrix is obtained. Check is successful" << endl;
	}

	return res;
}

double* Array::SLAE(Array U, double* b, bool isPrint)
{
	Array extArr(n, m + 1);  //Создание и заполнение расширенной матрицы
	for (int i=0; i<n; i++)
		for (int j = 0; j < m + 1; j++)
		{
			if (j == m)
				extArr.arr[i][j] = b[i];
			else
				extArr.arr[i][j] = U.arr[i][j];

		}

	int rankExt = extArr.rank(extArr); // Ранг расширенной матрицы
	int rankInit = rank(U); //Ранг исходной матрицы
	double* res = new double[m];
	for (int i = 0; i < m; i++)
		res[i] = 0;
	double sum = 0;
		
	if (rankExt == rankInit)  // Теорема Кронекера — Капелли
	{
		if (m > n)
		{
			for (int i = m - 1; i > n-1; i--)
				res[i] = 0;			

		}
		/*else
		{*/ 
		int j = 0;
			for (int i = rankInit-1; i >= 0; i--)
			{
				sum = 0;
				for (j = 0; j < m; j++) 
				{
					sum = sum + res[j] * U.arr[i][j];
				}
				if (U.arr[i][i] != 0)
					res[i] = (b[i] - sum) / U.arr[i][i];
				else														
				{
					res[n+i-rankInit] = (b[i] - sum) / U.arr[i][lead[i]];   //Для вырожденных систем
				}
				
				if (m > n)
				{
					res[i+1] = b[i]/U.arr[i][i+1];
					res[i] = 0;
				}
			}

			for (int i = 0; i < n; i++)
			{
				if (abs(res[i]) <= 1e-8) //Проверка на отрицательный ноль
					res[i] = abs(res[i]);
			}

			if (isPrint == true)
			{
				if (rankExt < n)
					cout << "Vector of one of the possible solutions: " << endl;
				else
					cout << "The solution: " << endl;
				for (int i = 0; i < m; i++)
					cout << res[i] << endl;
			}
			bool isOk = true;
			for (int i = 0; i < n; i++)
				if (((U*res)[i] - b[i]) >= 1e-10)
					isOk = false;
			if (isOk == true && isPrint == true)
				cout << "The solution of the SLAE is obtained. Check is successful" << endl;

		//}
	}
	else
		cout << "The system is incompatible" << endl;

	
	
	return res;
}

double* Array::resultSLAE(Array U, bool isPrint) // Для внешнего вызова функции SLAE
{
	double* res = new double[n];
	for (int i = 0; i < n; i++)
		res[i] = 0;
	res = SLAE(U, b, isPrint);

	return res;
}

void Array::nullTest() //Избежание ошибки отрицательного 0
{
	for (int i=0; i<n; i++)
		for (int j = 0; j < m; j++)
		{
			if (std::abs(arr[i][j]) <= 1e-5)
				arr[i][j] = abs(arr[i][j]);
		}
	//std::numeric_limits<double>::epsilon()
}

double Array::norm() //Норма по столбцам
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
	double normInvArr = 0; //Норма обратной матрицы
	double normArr = arr1.norm(); //Норма исходной матрицы
	if (arr1.determinant(U, false) != 0 && m == n)
	{
		bool isExcist = 1;
		Array invArr = inverseArray(U, isExcist); //Поиск обратной матрицы
		normInvArr = invArr.norm();
	}
	else
	{
		cout << "The inverse matrix does not exist. Conditional of the array tends to infinity." << endl;
		normInvArr = pow(2, 8*sizeof(double));
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
		for (int i=0; i<n; i++)
			b[i] = QRDecArr.b[i];
	}
	else
		cout << "QR_decomposition is impossible" << endl;
	/*res[0].print();
	res[1].print();*/
	return res;
}

double* Array::SeidelMethodSolution(bool isPrint)
{
	double* res = new double[m];
	for (int i = 0; i < m; i++)
		res[i] = 0;
	SeidelMethod solution(*this);

	res = solution.SLAESolution();
	if (isPrint == true)
	{
		for (int i = 0; i < m; i++)
			cout << res[i] << endl;
	}

	
	
	return res;
}

double* Array::JacobiMethodSolution(bool isPrint)
{
	double* res = new double[m];
	for (int i = 0; i < m; i++)
		res[i] = 0;
	SeidelMethod solution(*this);

	res = solution.SLAEJacobiSolution();
	if (isPrint == true)
	{
		for (int i = 0; i < m; i++)
			cout << res[i] << endl;
	}

	return res;
}
