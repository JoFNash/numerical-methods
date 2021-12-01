// #include <iostream>
// #include <cmath>
// #include <vector>
// #include <iomanip>
// #define SIZE 4

// using namespace std;

// double Matrix[SIZE][SIZE] = {{7.13, 8.21, 4.47, -2.11},
// 								{3.25, 1.54, 2.91, 5.43},
// 								{-6.34, 6.73, -10.2, 3.93},
// 								{4.52, 6.73, 1.37, -9.89}};
// double Nums[SIZE] = {20, 15, 10, 5};

// void GaussMethod(double *x) 
// {
// 	int i;
// 	int j;
// 	int k;

// 	for (i = 0; i < SIZE; i++)
// 	{
// 		double koeff = Matrix[i][i];
// 		Nums[i] /= koeff;
// 		for (j = 0; j < SIZE; j++)
// 		{
// 			Matrix[i][j] /= koeff;
// 		}
// 		for (k = i + 1; k < SIZE; k++)
// 		{
// 			double tmp = Matrix[k][i] / Matrix[i][i];
// 			Nums[k] -= tmp * Nums[i];
// 			for (int tmp_col = 0; tmp_col < SIZE; tmp_col++)
// 			{
// 				Matrix[k][tmp_col] -= Matrix[i][tmp_col] * tmp;
// 			}
// 		}
// 	}
// 	x[SIZE - 1] = Nums[SIZE - 1];
// 	for (i = SIZE - 2; i >= 0; i--)
// 	{
// 		x[i] = Nums[i];
// 		for (j = SIZE - 1; j > i; j--)
// 		{
// 			x[i] -= Matrix[i][j] * x[j];
// 		}
// 		x[i] /= Matrix[i][i];
// 	}
// }

// // int main(void)
// // {
// // 	double *Mass;

// // 	setlocale(LC_ALL, "RUS");
// // 	Mass = new double[SIZE];
// // 	GaussMethod(Mass);
// // 	cout << "---------------------Вариант №7---------------------" << endl;
// // 	cout << "Метод Гаусса:" << endl;
// // 	for (int i = 0; i < SIZE; i++)
// // 		cout << "x" << i + 1 << " = " << std::setprecision(8) << Mass[i] << endl;
// // 	cout << endl;
// // 	delete[] Mass;
// // }