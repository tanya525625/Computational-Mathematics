#pragma once
using namespace std;

#include <iostream>
#include <cmath>
#include "Array.h"
#include <ctime>
#include <fstream>


double* approximation(double* x, const int n);
double norm(double *x, double* b, int n);
double rootlLocalization();
double initializationF2(double x);
double initializationJ2(double x);
double stMethNewt2(double X, const int n, double eps);