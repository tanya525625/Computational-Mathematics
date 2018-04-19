#pragma once
#include "HeaderSLAE.h"
class SeidelMethod
{
private:
	int n;
	int m; 
	double* b;
	Array matrix;
public:
	SeidelMethod(Array _matrix);
	~SeidelMethod();
	double* SLAESolution();
	double* SLAEJacobiSolution();
	bool isConverge(double *xk, double *xkp, double eps);
	double norm(double *x, Array matrix, double* b);
};

