#include <iostream>
#include <cmath>
#define E 1e-5

using namespace std;

double myFoo1(double x, double y)
{
	return (tan(x + y) + 0.4 - pow(x, 2));
}

double myFoo2(double x, double y)
{
	return (0.9 * pow(x, 2) + 2 * pow(y, 2) - 1);
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

double getNumFoo_X(double x, double y, double (*Foo)(double, double)) 
{
	return ((Foo(x + E, y) - Foo(x, y)) / E);
}

double getNumFoo_Y(double x, double y, double (*Foo)(double, double))
{
	return ((Foo(x, y + E) - Foo(x, y)) / E);
}

void invertMatrix(double matrix[2][2])
{
	double determinant;
	double tmp_value;

    determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	tmp_value = matrix[0][0];
	matrix[0][0] = matrix[1][1] / determinant;
    matrix[0][1] = -matrix[0][1] / determinant;
    matrix[1][0] = -matrix[1][0] / determinant;
    matrix[1][1] = tmp_value / determinant;
}

void analyticalSolution(double x, double y, double *x_result, double *y_result, long *iter)
{
	double ArrayDerivatives[2][2];
	double dx;
	double dy;
	double tmp[2];
	double norm;
	*iter = 0;
	norm = 1;
	while (norm >= E)
	{
		ArrayDerivatives[0][0] = myFoo1Derivative_X(x, y);
        ArrayDerivatives[0][1] = myFoo1Derivative_Y(x, y);
        ArrayDerivatives[1][0] = myFoo2Derivative_X(x, y);
        ArrayDerivatives[1][1] = myFoo2Derivative_Y(x, y);

		invertMatrix(ArrayDerivatives);
		dx = -ArrayDerivatives[0][0] * myFoo1(x, y) - ArrayDerivatives[0][1] * myFoo2(x, y);
        dy = -ArrayDerivatives[1][0] * myFoo1(x, y) - ArrayDerivatives[1][1] * myFoo2(x, y);

		x = x + dx;
		y = y + dy;
		tmp[0] = myFoo1(x, y);
		tmp[1] = myFoo2(x, y);
		norm = sqrt(pow(tmp[0], 2) + pow(tmp[1], 2));
		(*iter)++;
		if (norm < E)
		{
			*x_result = x;
			*y_result = y;
		}
	}
}

void numericalSolution(double x, double y, double *x_result, double *y_result, long *iter)
{
	double ArrayDerivatives[2][2];
	double dx;
	double dy;
	double tmp[2];
	double norm;
	*iter = 0;
	norm = 1;
	while (norm >= E)
	{
		ArrayDerivatives[0][0] = getNumFoo_X(x, y, myFoo1);
        ArrayDerivatives[0][1] = getNumFoo_Y(x, y, myFoo1);
        ArrayDerivatives[1][0] = getNumFoo_X(x, y, myFoo2);
        ArrayDerivatives[1][1] = getNumFoo_Y(x, y, myFoo2);

		invertMatrix(ArrayDerivatives);
		dx = -ArrayDerivatives[0][0] * myFoo1(x, y) - ArrayDerivatives[0][1] * myFoo2(x, y);
        dy = -ArrayDerivatives[1][0] * myFoo1(x, y) - ArrayDerivatives[1][1] * myFoo2(x, y);

		x = x + dx;
		y = y + dy;
		tmp[0] = myFoo1(x, y);
		tmp[1] = myFoo2(x, y);
		norm = sqrt(pow(tmp[0], 2) + pow(tmp[1], 2));
		(*iter)++;
		if (norm < E)
		{
			*x_result = x;
			*y_result = y;
		}
	}
}

// int main(void)
// {
// 	double	x;
// 	double	y;
// 	double	x_result;
// 	double	y_result;
// 	long	iter;

// 	iter = 0;
// 	cout << "Ïðèáëèæåííîå âû÷èñëåíèÿ êîðíåé ñèñòåìû íåëèíåéíûõ óðàâíåíèé ìåòîäîì Íüþòîíà" << endl;
//  	cout << "---------------------Âàðèàíò ¹7---------------------" << endl;
// 	cout << "1. ×àñòíûå ïðîèçâîäíûå íàõîäÿòñÿ àíàëèòè÷åñêè:" << endl;
// 	analyticalSolution(-0.6, 0.5, &x_result, &y_result, &iter);
// 	cout << "x1 = " << x_result << " y1 = " << y_result << endl;
// 	cout << "×èñëî èòåðàöèé äî ïîëó÷åíèÿ ðåçóëüòàòà: " << iter << endl << endl;

// 	iter = 0;
// 	analyticalSolution(0.4, -0.6, &x_result, &y_result, &iter);
// 	cout << "x2 = " << x_result << " y2 = " << y_result << endl;
// 		cout << "×èñëî èòåðàöèé äî ïîëó÷åíèÿ ðåçóëüòàòà: " << iter << endl << endl;

// 	cout << "2. ×àñòíûå ïðîèçâîäíûå íàõîäÿòñÿ ÷èñëåííî:" << endl;
// 	iter = 0;
// 	numericalSolution(-0.6, 0.5, &x_result, &y_result, &iter);
// 	cout << "x1 = " << x_result << " y1 = " << y_result << endl;
// 	cout << "×èñëî èòåðàöèé äî ïîëó÷åíèÿ ðåçóëüòàòà: " << iter << endl << endl;

// 	numericalSolution(0.4, -0.6, &x_result, &y_result, &iter);
// 	cout << "x2 = " << x_result << " y2 = " << y_result << endl;
// 	cout << "×èñëî èòåðàöèé äî ïîëó÷åíèÿ ðåçóëüòàòà: " << iter << endl << endl;
// 	return 0;
// }
