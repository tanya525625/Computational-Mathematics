#include "Header.h"

int main()
{
	double begN = 0.1; 
	double step = 0.01; 
	double finN = 0.2; 

	cout << "    x" << '\t' << '\t' << "classFunc" << '\t' <<  " myFunc" << '\t' << '\t' << "   dFunc"  << endl;
	for (double x = begN; x < finN+step; x = x + step)
	{
		cout.setf(ios::showpoint); 
		cout << x << '\t'  << classFunc(x) <<'\t' << myFunc(x) << '\t' << abs(classFunc(x) - myFunc(x)) << endl;
		
	}




	system("pause");
	return 0;
}
