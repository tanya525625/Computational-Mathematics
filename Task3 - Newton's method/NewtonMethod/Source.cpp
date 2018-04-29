#include "Header.h"

int main()
{
	const int n = 10;
	double eps = 1e-8;
	double* X = new double[n];
	Array F(n, 1);
	Array J(n, n);

	cout << fixed;
	cout.precision(3);
	cout << endl;
	X = stMethNewt(X, n, F, J, eps);
	cout << "The solution of the system by Newton's method: " << endl;
	for (int i = 0; i < n; i++)
		cout << X[i] << "\t";
	cout << endl;

	cout << endl;
	X = MethNewt(X, n, F, J, eps);
	cout << "The solution of the system by Newton's method: " << endl;
	for (int i = 0; i < n; i++)
		cout << X[i] << "\t";
	cout << endl;

	cout << endl;
	X = modifiedMethNewt(X, n, F, J, eps);
	cout << "The solution of the system by Newton's method: " << endl;
	for (int i = 0; i < n; i++)
		cout << X[i] << "\t";
	cout << endl;

	cout << endl;
	X = automaticModifiedMethNewt(X, n, F, J, eps);
	cout << "The solution of the system by Newton's method: " << endl;
	for (int i = 0; i < n; i++)
		cout << X[i] << "\t";
	cout << endl;
		



	

	system("pause");
	return 0;
}