#include <iostream>
#include <cmath>
#define E 1e-5

using namespace std;

double myFoo1(double x, double y)
{
	return (tan(x + y) + 0.4 - x * x);
}

double myFoo2(double x, double y)
{
	return (0.9 * x * x + 2 * y * y - 1);
}

double myFoo1Derivative_X(double x, double y)
{
	return (1 / pow(cos(x + y), 2) - 2 * x);
}

double myFoo2Derivative_X(double x, double y)
{ 
	return (1.8 * x);
}

double myFoo1Derivative_Y(double x, double y)
{
	return (1 / pow(cos(x + y), 2));
}

double myFoo2Derivative_Y(double x, double y)
{
	return (4 * y);
}

