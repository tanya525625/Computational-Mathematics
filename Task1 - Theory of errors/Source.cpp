#include "Header.h"

int main()
{
	double begN = 0.1; //Начальное значение x
	double step = 0.01; //Шаг x
	double finN = 0.2; //Конечное значение x

	/*cout << fixed;
	cout.precision(11);*/
	cout << "    x" << '\t' << '\t' << "classFunc" << '\t' <<  " myFunc" << '\t' << '\t' << "   dFunc"  << endl;
	for (double x = begN; x < finN+step; x = x + step)
	{
		cout.setf(ios::showpoint); 
		cout << x << '\t'  << classFunc(x) <<'\t' << myFunc(x) << '\t' << abs(classFunc(x) - myFunc(x)) << endl;
	}

	system("pause");
	return 0;
}