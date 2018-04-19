#include "HeaderSLAE.h"

int main()
{
	Array* LU = new Array[2];
	Array* QR = new Array[2];
	Array arr1;
	Array arr2;
	
	double det = 0;
	Array invArr;
	cout.precision(3); //�������� ������

	cout << "Your matrix: " << endl;
	arr1.print();
	cout << endl;
	cout << "Your vector b: " << endl;
	arr1.printB();
	cout << endl;

	LU = arr1.PLU_decomposition();
	cout << "U:" << endl;
	LU[1].print();
	cout << endl;
	cout << "L: " << endl;
	LU[0].print();
	cout << endl;
	det = arr1.determinant(LU[1], true);
	cout << endl;
	cout << "Rank of the array:  " << arr1.rank(LU[1]) << endl;
	cout << endl;
	arr1.resultSLAE(LU[1], true);
	cout << endl;
	bool isExcist = 1;
	invArr = arr1.inverseArray(LU[1], isExcist);
	if (isExcist == 1)
		invArr.print();
	cout << endl;

	cout << "The calculation of the conditional number was started " << endl;
	cout << "Conditional number: " << arr1.conditionNumber(LU[1]) << endl;
	cout << endl;

	if (det != 0)
	{
		QR = arr2.QR_decomposition();
		cout << "Q:" << endl;
		QR[0].print();
		cout << endl;
		cout << "R: " << endl;
		QR[1].print();
		cout << endl;
		arr2.resultSLAE(QR[1], true);
	}
	else
		cout << "The determinant == 0. QR-decomposition isn't done" << endl;

	Array arr3(true);
	Array arr4;
	Array arr5;
	

	cout << endl;
	/*arr3.SeidelMethodSolution(false);*/
	arr4 = arr4.generPosDeterm();
	arr4.SeidelMethodSolution(false);
	/*arr5.SeidelMethodSolution(false);*/
	
	/*arr5.SeidelMethodSolution(false);*/

	
	cout << endl;
	/*arr3.JacobiMethodSolution(false);*/
	arr4.JacobiMethodSolution(false);
	/*arr5.JacobiMethodSolution(false);*/
	//arr5.JacobiMethodSolution(false);
	

	system("pause");
	return 0;
}