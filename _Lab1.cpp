#include <iostream>
#include <cmath>
#define E 1e-5

using namespace std;

double myFoo(double x)
{
	return (x * x * x - 4 * sin(x) - 0.5);
}

double myFooDerivative(double x)
{
	return (3 * x * x - 4 * cos(x));
}

double DichotomyMethod(double A, double B, double (*Foo)(double), int &count_operations)
{
	double	X;

	count_operations = 0;
	X = (A + B) / 2.0;

	while (fabs(A - B) > E)
	{
		if (Foo(X) * Foo(A) < 0)
			B = X;
		else if ((Foo(X) * Foo(B) < 0))
			A = X;
		X = (A + B) / 2.0;
		count_operations++;
	}
	return (X);
}


double IterationMethod(double A, double B, double (*Foo)(double), double (*myFooDerivative)(double), int &count_operations)
{
	double	X;
	double	parameter;
	int		sign;
	
	sign = 1;
	count_operations = 0;
	X = B;
	if (myFooDerivative(A) < 0)
		sign = -1;
	parameter = 2 / (abs(myFooDerivative(A) + myFooDerivative(B)));
	while (abs(Foo(X)) > E)
	{
		X = X - parameter * sign * Foo(X);
		count_operations++;
	}
	return (X);
}


// int	main(void)
// {
// 	int count_operations;

// 	cout << "----------------------Вариант №7----------------------" << endl;
// 	cout << "1. Метод дихотомии" << endl;
// 	cout << "Корень = " << DichotomyMethod(1.5, 2, &myFoo, count_operations) << endl <<
// 				"Число итераций до получения результата: " << count_operations << endl << endl;
// 	cout << "Корень = " << DichotomyMethod(-2, -1, &myFoo, count_operations) << endl <<
// 				"Число итераций до получения результата: " << count_operations << endl << endl;
// 	cout << "Корень = " << DichotomyMethod(-0.5, 0, &myFoo, count_operations) << endl << 
// 				"Число итераций до получения результата: " << count_operations << endl << endl;

// 	cout << "2. Метод простой итерации с выбором оптимального параметра" << endl;
// 	cout << "Корень = " << IterationMethod(1.5, 2, &myFoo, myFooDerivative, count_operations) << endl << 
// 				"Число итераций до получения результата: " << count_operations << endl << endl;
// 	cout << "Корень = " << IterationMethod(-2, -1, &myFoo, myFooDerivative, count_operations) << endl <<
// 				"Число итераций до получения результата: " << count_operations << endl << endl;
// 	cout << "Корень = " << IterationMethod(-0.5, 0, &myFoo, myFooDerivative, count_operations) << endl <<
// 				"Число итераций до получения результата: " << count_operations << endl << endl;

// }