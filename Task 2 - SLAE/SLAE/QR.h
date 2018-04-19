#pragma once
#include "HeaderSLAE.h"
#include "Array.h"

class QR
{
private:
	int n;
	Array matrix;
	double* b;
public:
	Array Q;
	Array R;
	QR (Array _matrix, int _n);
	~QR();
	void decomposition();
	friend class Array;
};