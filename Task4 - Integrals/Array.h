#pragma once
#include "Header.h"

class Array
{

private:
	int n; //���-�� �����
	int m; //���-�� ��������
	int Rank;
	double** identArr; //��������� �������
	
	
	int* lead;
	

	int numTransp;

public:
	double** arr;
	int* P;
	double* b;
	Array();
	Array(int _n, int _m);
	Array(bool isRandom);
	~Array();
	void print();
	void printB();
	Array* PLU_decomposition();
	Array generPosDeterm();
	Array transposition(int* P);
	void transposition(double* b);
	friend Array operator *(Array &a1, Array &a2);
	friend Array operator *(double c, Array a);
	friend double* operator *(Array a, double* x);
	friend bool operator == (Array a1, Array a2);
	Array transpose();
	double determinant(Array U, bool isPrint);
	int rank(Array U);
	double* SLAE(Array U, double* b, bool isPrint);
	Array inverseArray(Array U, bool &isExcist);
	double* resultSLAE(Array U, bool isPrint);
	double** transpositionArr(int* P, double** arr);
	double** transposeArr(double** arr);
	void nullTest();
	double norm();
	double conditionNumber(Array U);
	Array createIdentArr();
	Array* QR_decomposition();
};


