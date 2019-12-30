#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include  <conio.h>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;



int main()
{
	int m = 2; //степень аппроксимирующего полинома  
	int N = 11;  ///число измерений   
	const int n = 11;
	double data[n][2];

	initdata(data);

	double **A = soz(m + 1);

	for (int i = 0; i < m + 1; i++)   ///  составляем матрицу
		for (int j = 0; j < m + 1; j++)
			A[i][j] = sum(data, i + j);

	A[0][0] = N;               /// правые части
	for (int i = 0; i < m + 1; i++)
		A[i][m + 1] = sumy(data, i);

	double *a = new double[m + 1];
	gauss(A, m + 1, a);

	for (int i = 0; i < m + 1; i++)  /// вывод
		cout << "a [" << i << "] = " << a[i] << endl;
	cout << endl;

	double b = 0;   // среднеквадратическое отклонение 
	double bi;
	for (int i = 0; i < N; i++)
	{
		bi = data[i][1];
		for (int y = 0; y < m + 1; y++)
			bi -= a[y] * pow(data[i][0], y);  // вычесляем 4.5
		b += bi * bi;						/// и в квадрат
	}
	b /= (N - m - 1);

	cout << "Sigma = " << sqrt(b) << endl;  // среднеквадратическое отклонение 
	/// на сколько близки наши  результаты к исходным
	_getch();
	return 0;
}
void initdata(double data[11][2])
{
	ifstream f("file.txt");
	for (int i = 0; i < 11; i++)
		for (int p = 0; p < 2; p++)
		{
			double v;
			f >> v;
			data[i][p] = v;
		}
}

double sum(double data[11][2], double p)
{
	double s = 0;
	int i;
	for (i = 0; i < 11; i++) {
		s += pow(data[i][0], p);
	}
	return s;
}

double sumy(double data[11][2], double p)
{
	double s = 0;
	int i;
	for (i = 0; i < 11; i++) {
		s += data[i][1] * pow(data[i][0], p);
	}
	return s;
}