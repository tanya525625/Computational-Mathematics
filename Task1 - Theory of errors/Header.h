#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double pi = 4.*atan(1.);

const double c1 = 0.6;
const double c2 = 0.9;
const double c3 = 1;
const double e1 = pow(10, -6) / (3*c1); //Вычисление погрешностей через принцип равных влияний
const double e2 = pow(10, -6) / (3*c2);
const double e3 = pow(10, -6) / (3*c3);


double classFunc(double x);
double myFunc(double x);
double mySin(double x);
double mySh(double x);
double mySqrt(double x, int k);
int factorial(int i);



