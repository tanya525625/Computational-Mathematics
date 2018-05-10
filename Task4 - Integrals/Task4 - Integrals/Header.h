#pragma once
#include <iostream>
#include <cmath>
#include "Array.h"

using namespace std;

double F(double x);
double NewtonCotesMethod(double a, double b, double aa, double bb, double h);
double moment0(double iA, double iB, double a, double b, double aa, double bb);
double moment1(double iA, double iB, double a, double b, double aa, double bb, double mom0);
double moment2(double iA, double iB, double a, double b, double aa, double bb, double mom0, double mom1);
double IKFSpecifiedAccuracy(double a, double b, double aa, double bb, double L, double &m, double &Rh2, double h, double e);
double findHopt(double a, double b, double aa, double bb, double L, double n, double eps);
