#include <iostream>
#include <cmath>
#include <vector>
#define SIZE 4

using namespace std;
vector<double> Nums = {20, 15, 10, 5};
vector<vector<double>> Matrix = {{7.13, 8.21, 4.47, -2.11},
								   {3.25, 1.54, 2.91, 5.43},
								   {-6.34, 6.73, -10.2, 3.93},
								   {4.52, 6.73, 1.37, -9.89}};

double scalar_product(vector<double> mult1, vector<double> mult2)
{
	double sum = 0;
	for (int i = 0; i < mult1.size(); i++)
		sum += mult1[i] * mult2[i];
	return sum;
}

vector<vector<double>> AtA(vector<vector<double>> A)
{
	vector<vector<double>> result(SIZE, vector<double>(SIZE));
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			result[i][j] = 0;
			for (int p = 0; p < SIZE; p++)
				result[i][j] += A[p][j] * A[p][i];
		}
	}
	return result;
}

vector<double> AtAb(vector<vector<double>> A, vector<double> p)
{
	vector<vector<double>> Helping_matrix(SIZE, vector<double>(SIZE));
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			Helping_matrix[i][j] = A[j][i];
	vector<double> result(SIZE);
	for (int i = 0; i < A.size(); i++)
	{
		result[i] = 0;
		for (int j = 0; j < SIZE; j++)
			result[i] += Helping_matrix[i][j] * p[j];
	}
	return result;
}

vector<double> AAtr(vector<vector<double>> A, vector<double> r1)
{
	vector<vector<double>> Helping_matrix(SIZE, vector<double>(SIZE));
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			Helping_matrix[i][j] = 0;
			for (int k = 0; k < SIZE; k++)
				Helping_matrix[i][j] += A[i][k] * A[j][k];
		}
	}
	vector<double> result(SIZE);
	for (int i = 0; i < A.size(); i++)
	{
		result[i] = 0;
		for (int j = 0; j < SIZE; j++)
			result[i] += Helping_matrix[i][j] * r1[j];
	}
	return result;
}

vector<double> muWr(double mu, vector<vector<double>> A, vector<double> r1)
{
	vector<double> result(A.size());
	for (int i = 0; i < A.size(); i++)
	{
		double sum = 0;
		for (int j = 0; j < A.size(); j++)
			sum += A[i][j];
		result[i] = sum * r1[i] * mu;
	}
	return result;
}

double norm(vector<double> rp)
{
	double sum = 0;
	for (int i = 0; i < rp.size(); i++)
		sum += rp[i] * rp[i];
	return sqrt(sum);
}

vector<double> find_rp(vector<vector<double>> A, vector<double> current_x, vector<double> b)
{
	vector<double> result(SIZE);
	for (int i = 0; i < SIZE; i++)
	{
		result[i] = 0;
		for (int j = 0; j < SIZE; j++)
			result[i] += A[i][j] * current_x[j];
		result[i] -= b[i];
	}
	return result;
}

vector<double> DescentMethod(vector<vector<double>> A, vector<double> B, double eps, int *iterations)
{
	vector<double> result(SIZE);
	vector<double> rp;

	*iterations = 0;
	//cout << "It is okey1" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		if (A[i][i] != 0)
			result[i] = B[i] / A[i][i];
		else
			result[i] = 0;
	}
	//cout << "It is okey2" << endl;
	do
	{
		rp = find_rp(A, result, B);
		//cout << "It is okey3" << endl;
		vector<double> AAtR = AAtr(A, rp);
		double mu = scalar_product(rp, AAtR) / scalar_product(AAtR, AAtR);
		//cout << "It is okey4" << endl;
		vector<double> muAr = muWr(mu, A, rp);
		//cout << "It is okey5" << endl;
		for (int i = 0; i < SIZE; i++)
			result[i] -= muAr[i];
		//cout << "It is okey6" << endl;
		(*iterations)++;
		//cout << "norm(rp) = " << norm(rp) << endl;
	} while (norm(rp) > eps);
	return result;
}

vector<double> SoprGrad(vector<vector<double>> A, vector<double> B, double eps, int *iterations)
{
	vector<double> x(SIZE), r(SIZE), r_prev(SIZE), p(SIZE), Ap(SIZE);
	double alpha, beta;
	(*iterations) = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (A[i][i] != 0)
			x[i] = B[i] / A[i][i];
		else
			x[i] = A[i][i];
	}
	for (int i = 0; i < SIZE; i++)
	{
		r[i] = B[i];
		for (int j = 0; j < SIZE; j++)
			r[i] -= A[i][j] * x[j];
		p[i] = r[i];
	}
	do
	{
		(*iterations)++;
		for (int i = 0; i < SIZE; i++)
		{
			r_prev[i] = r[i];
			Ap[i] = 0;
			for (int j = 0; j < SIZE; j++)
			{
				Ap[i] += A[i][j] * p[j];
			}
		}
		alpha = scalar_product(r_prev, r_prev) / scalar_product(Ap, p);
		for (int i = 0; i < SIZE; i++)
		{
			x[i] += alpha * p[i];
			r[i] -= alpha * Ap[i];
		}
		beta = scalar_product(r, r) / scalar_product(r_prev, r_prev);
		for (int i = 0; i < SIZE; i++)
			p[i] = r[i] + beta * p[i];
	} while (norm(r) / norm(B) > eps);
	return x;
}

int main(void)
{
	setlocale(LC_ALL, "RUS");
	double eps = 10e-2;
	int iterations = 0;
	vector<double> spusk;
	vector<vector<double>> NewA = AtA(Matrix);
	vector<double> NewB = AtAb(Matrix, Nums);
	cout << "\t\t\t\t\tМетод наискорейшего спуска" << endl
		 << endl;
	cout << "Eps\t\t x1\t\t\t x2\t\t\t x3\t\t\t x4\t\tчисло итераций" << endl;
	for (int i = 1; i < 8; i++)
	{
		spusk = DescentMethod(Matrix, Nums, eps, &iterations);
		cout.precision(7);
		cout << eps;
		for (int j = 0; j < spusk.size(); j++)
			cout << "\t|\t" << spusk[j];
		cout << "\t|\t" << iterations << endl;
		eps *= 0.1;
	}
	eps = 10e-2;
	cout << endl;
	cout << endl;
	// cout << "\t\t\t\t\tМетод сопряженных градиентов" << endl
	// 	 << endl;
	// cout << "Eps\t\t x1\t\t\t x2\t\t\t x3\t\t\t x4\t\tчисло итераций" << endl;
	// for (int i = 1; i < 8; i++)
	// {
	// 	spusk = SoprGrad(NewA, NewB, eps, &iterations);
	// 	cout.precision(7);
	// 	cout << eps;
	// 	for (int j = 0; j < SIZE; j++)
	// 		cout << "\t|\t" << spusk[j];
	// 	cout << "\t|\t" << iterations << endl;
	// 	eps *= 0.1;
	// }
}
