//Implementation of class called Data
#include "stdafx.h"
#include "Data.h"
#include <string>
#include <iostream>


using namespace std;
extern int n;
void Data(int size) {
	n = size;
}

//Fill Vector with 1
int* Vector_Input() {
	int* A = new int[n];
#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		A[i] = 1;
	}
	return A;
}

//Print Vector on screen
void Vector_Output(int* A)
{
	for (int i = 0; i < n; i++)
	{
		cout << A[i] << " ";
	}
}

//Fill Matrix with 1
int** Matrix_Input()
{
	int** A = new int*[n];
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		A[i] = new int[n];
#pragma omp parallel for
		for (int j = 0; j < n; j++)
		{
			A[i][j] = 1;
		}
	}
	return A;
}

//Print Matrix on screen
void Matrix_Output(int** A)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
}

//Adds the vector A to the vector B
int* Vector_Add(int* A, int* B, int* C)
{
	int* D = new int[n];
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		D[i] = A[i] + B[i] + C[i];
	}
	return D;
}

//Adds the matrix A to the matrix B
int** Matrix_Add(int** A, int** B)
{
	int** C = new int*[n];
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		C[i] = new int[n];
#pragma omp parallel for
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	return C;
}

//Subtracts the matrix B from the matrix A
int** Matrix_Multiply(int** A, int** B)
{
	int** C = new int*[n];
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		C[i] = new int[n];
#pragma omp parallel for
		for (int j = 0; j < n; j++)
		{
			C[i][j] = 0;
#pragma omp parallel for
			for (int k = 0; k < n; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}

//Multiply Vector on Matrix
int* Matrix_Vector_Multiply(int** A, int* B)
{
	int* C = new int[n];
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		C[i] = 0;
#pragma omp parallel for
		for (int j = 0; j < n; j++)
		{
			C[i] += A[j][i] * B[i];
		}
	}
	return C;
}

//Multiply Value on Matrix
int** Matrix_Value_Multiply(int** A, int B)
{
	int** C = new int*[n];
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		C[i] = new int[n];
#pragma omp parallel for
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[j][i] * B;
		}
	}
	return C;
}

//Search for maximum element in Vector
int Vector_Max(int* A)
{
	int B = A[0];
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		if (A[i] > B)
		{
			B = A[i];
		}
	}
	return B;
}

//Sorting Vector. Uses bubble sorting.
int* Vector_Sort(int* A)
{
	bool Finished;
	int Temp = 0;
	int* B = new int[n];
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		B[i] = A[i];
	}
#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		Finished = true;
#pragma omp parallel for
		for (int j = 1; j < (n - i); j++) {
			if (B[j - 1] > B[j]) {
				Temp = B[j - 1];
				B[j - 1] = B[j];
				B[j] = Temp;
				Finished = false;
			}
		}
		if (Finished) {
			break;
		}
	}
	return B;
}

/*
Calculating Func1
MD=MAX(A+B+C)*(MA*ME)
*/
int** Func1(int* A, int* B, int* C, int** MA, int** ME)
{
	int** MD = Matrix_Value_Multiply(Matrix_Multiply(MA, ME), Vector_Max(Vector_Add(A, B, C)));
	return MD;
}

/*
Calculating Func2
MF=(MG+MH)*(MK*ML)*(MG+ML)
*/
int** Func2(int** MG, int** MK, int** ML, int** MH)
{
	int** MF = Matrix_Multiply(Matrix_Multiply(Matrix_Add(MG, MH), Matrix_Multiply(MK, ML)), Matrix_Add(MG, ML));
	return MF;
}

/*
Calculating Func3
S=SORT(O*MO)*(MS*MT)
*/
int* Func3(int* O, int** MO, int** MS, int** MT)
{
	int* S = Matrix_Vector_Multiply(Matrix_Multiply(MS, MT), Vector_Sort(Matrix_Vector_Multiply(MO, O)));
	return S;
}