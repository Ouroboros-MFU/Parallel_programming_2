#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "time.h"
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include "omp.h"
#include <Windows.h>
using namespace std;

double go(const char* path, double** a, double** b, double** c, int N)
{
	a = new double* [N];
	//cout << "Ввод элементов первой матрицы..." << endl;
	for (int i = 0; i < N; i++)
	{
		a[i] = new double[N];
		for (int j = 0; j < N; j++)
		{
			a[i][j] = rand() % 10;
		}
	}
	ofstream fout;
	fout.open((string)path + (string)"A.txt");
	//fout << N << '\n';

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) //запись элементов первой матрицы
			fout << a[i][j] << ' ';
		fout << '\n';
	}
	fout.close();
	//cout << "comlete write file A.txt!\n";





	ifstream fin;
	fin.open((string)path + (string)"A.txt");
	//fin >> Na;
	double** A = new double* [N];
	//int Af[N][N];
	//cout << "new A: \n";
	for (int i = 0; i < N; i++)
	{
		A[i] = new double[N];
		for (int j = 0; j < N; j++) //чтение элементов первой матрицы
		{
			fin >> A[i][j];
			//cout << Af[i][j] << ' ';
		}
		//cout << "\n";
	}
	fin.close();



	b = new double* [N];
	//cout << "Ввод элементов второй матрицы..." << endl;
	for (int i = 0; i < N; i++)
	{
		b[i] = new double[N];
		for (int j = 0; j < N; j++)
		{
			b[i][j] = rand() % 10;
		}
	}

	fout.open((string)path + (string)"B.txt");
	//fout << N << '\n';

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) //запись элементов второй матрицы
			fout << b[i][j] << ' ';
		fout << '\n';

	}
	fout.close();
	//cout << "comlete write file B.txt!\n";


	fin.open((string)path + (string)"B.txt");
	//int Bf[N][N];
	double** B = new double* [N];
	//cout << "new B: \n";
	for (int i = 0; i < N; i++)
	{
		B[i] = new double[N];
		for (int j = 0; j < N; j++) //чтение элементов второй матрицы
		{
			fin >> B[i][j];
		}
	}
	fin.close();
	//cout << "complete read files!\n";


	// Умножение матриц
	c = new double* [N];
	size_t count = 0;
	clock_t start = clock();
	double start_time, end_time, tick;
	start_time = omp_get_wtime();
	//Устанавливаем число потоков
	int threadsNum = 8;
	omp_set_num_threads(threadsNum);
	//#pragma omp for
#pragma omp parallel for shared(A, B, c)

	for (int i = 0; i < N; i++)
	{
		//cout << count++;
		c[i] = new double[N];
		for (int j = 0; j < N; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < N; k++)
				c[i][j] += A[i][k] * B[k][j];
		}

	}
	end_time = omp_get_wtime();
	tick = omp_get_wtick();
	//cout << tick << ' ';
	double result_time = double(end_time - start_time);
	cout << result_time << ' ';
	//double result_time = double(clock() - start) / CLOCKS_PER_SEC;
	//cout << endl << "Calculation time:" << result_time << " seconds" << endl;
	// Вывод матрицы произведения
	//cout << "Матрица произведения посчитана!" << endl;
	fout.open((string)path + (string)"C.txt");

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) //запись элементов
			fout << c[i][j] << ' ';
		fout << '\n';
	}
	fout.close();

	return result_time;
}

int main()
{
	int N = 500;
	double** a = NULL, ** b = NULL, ** c = NULL;
	system("chcp 1251");
	system("cls");

	ofstream fiout;
	fiout.open("log.txt");
	for (int i = 0; i < 9; i++)
	{
		const string path = "matrix/" + to_string(N) + "/";
		cout << path << endl;
		const char* PATH = path.c_str();
		fiout << N;
		fiout << '\n';
		fiout << "Calculation time for " << N << '*' << N << " matrix = " << go(PATH, a, b, c, N) << " seconds\n";
		N += 250;
		cout << i + 1 << endl;
	}


	fiout.close();

	system("python ../pp/pp.py");

	return 0;
}