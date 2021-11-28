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

double DichotomyMethod(double A, double B, double (*Foo)(double))
{
	int		count_operations;
	double	X;

	count_operations = 0;
	X = (A + B) / 2.0;

	while (abs(A - B) > E)
	{
		if (Foo(X) * Foo(A) < 0)
		{
			B = X;
		}
		else if ((Foo(X) * Foo(B) < 0))
		{
			A = X;
		}
		X = (A + B) / 2.0;
		count_operations++;
	}
	std::cout << "Operations: " << count_operations << std::endl;
	return (X);
}

double IterationMethod(double A, double B, double (*Foo)(double))
{
	int		count_operations;
	double	X;
	double	parameter;
	int		sign;
	
	sign = 1;
	count_operations = 0;
	if (myFooDerivative(A) < 0)
		sign = -1;
	parameter = 2.0 / (myFooDerivative(A) + myFooDerivative(B));
	X = B;
	while (abs(Foo(X) > E))
	{
		X = X - parameter * sign * Foo(X);
		count_operations++;
	}
	cout << "Число итераций:" << count_operations << endl;
	return (X);
}



int	main(void)
{
	cout << "Answer = " << DichotomyMethod(1, 2, &myFoo) << endl << endl;
	cout << "Answer = " << DichotomyMethod(-2, 0, &myFoo) << endl << endl;
	cout << "Answer = " << DichotomyMethod(-1, 0, &myFoo) << endl << endl;

	cout << "Answer = " << IterationMethod(1, 2, &myFoo) << endl << endl;
	cout << "Answer = " << IterationMethod(-2, 0, &myFoo) << endl << endl;
	cout << "Answer = " << IterationMethod(-1, 0, &myFoo) << endl << endl;

}