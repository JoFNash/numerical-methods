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

double DichotomyMethod(double A, double B, double (*Foo)(double), int *count_operations)
{
	double	X;

	(*count_operations) = 0;
	X = (A + B) / 2.0;

	while (fabs(A - B) > E)
	{
		if (Foo(X) * Foo(A) < 0)
			B = X;
		else if ((Foo(X) * Foo(B) < 0))
			A = X;
		X = (A + B) / 2.0;
		(*count_operations)++;
	}
	return (X);
}


double IterationMethod(double A, double B, double (*Foo)(double), double (*myFooDerivative)(double), int *count_operations)
{
	double	X;
	double	parameter;
	int		sign;
	
	sign = 1;
	(*count_operations) = 0;
	X = B;
	if (myFooDerivative(A) < 0)
		sign = -1;
	parameter = 2 / (abs(myFooDerivative(A) + myFooDerivative(B)));
	while (abs(Foo(X)) > E)
	{
		X = X - parameter * sign * Foo(X);
		(*count_operations)++;
	}
	return (X);
}


// int	main(void)
// {
// 	int count_operations;

// 	cout << "----------------------Âàðèàíò ¹7----------------------" << endl;
// 	cout << "1. Ìåòîä äèõîòîìèè" << endl;
// 	cout << "Êîðåíü = " << DichotomyMethod(1, 2, &myFoo, &count_operations) << endl <<
// 				"×èñëî èòåðàöèé äî ïîëó÷åíèÿ ðåçóëüòàòà: " << count_operations << endl << endl;
// 	cout << "Êîðåíü = " << DichotomyMethod(-2, -1, &myFoo, &count_operations) << endl <<
// 				"×èñëî èòåðàöèé äî ïîëó÷åíèÿ ðåçóëüòàòà: " << count_operations << endl << endl;
// 	cout << "Êîðåíü = " << DichotomyMethod(-0.5, 0, &myFoo, &count_operations) << endl << 
// 				"×èñëî èòåðàöèé äî ïîëó÷åíèÿ ðåçóëüòàòà: " << count_operations << endl << endl;

// 	cout << "2. Ìåòîä ïðîñòîé èòåðàöèè ñ âûáîðîì îïòèìàëüíîãî ïàðàìåòðà" << endl;
// 	cout << "Êîðåíü = " << IterationMethod(1, 2, &myFoo, myFooDerivative, &count_operations) << endl << 
// 				"×èñëî èòåðàöèé äî ïîëó÷åíèÿ ðåçóëüòàòà: " << count_operations << endl << endl;
// 	cout << "Êîðåíü = " << IterationMethod(-2, -1, &myFoo, myFooDerivative, &count_operations) << endl <<
// 				"×èñëî èòåðàöèé äî ïîëó÷åíèÿ ðåçóëüòàòà: " << count_operations << endl << endl;
// 	cout << "Êîðåíü = " << IterationMethod(-0.5, 0, &myFoo, myFooDerivative, &count_operations) << endl <<
// 				"×èñëî èòåðàöèé äî ïîëó÷åíèÿ ðåçóëüòàòà: " << count_operations << endl << endl;

// }
