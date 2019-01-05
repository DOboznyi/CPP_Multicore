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

//Input Vector from keyboard
int* Vector_Input(char* name) {
	int* A = new int[n];
	for (int i = 0; i < n; i++) {
		cout << name << "[" << i << "] = ";
		cin >> A[i];
		cout << endl;
	}
	return A;
}

//Fill Vector with 1
int* Vector_Input1() {
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

//Input Matrix from keyboard
int** Matrix_Input(char* name)
{
	int** A = new int*[n];
	for (int i = 0; i < n; i++)
	{
		A[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			cout << name << "[" << i << "]" << "[" << j << "] = ";
			cin >> A[i][j];
			cout << endl;
		}
	}
	return A;
}

//Fill Matrix with 1
int** Matrix_Input1()
{
	int** A = new int*[n];
	for (int i = 0; i < n; i++)
	{
		A[i] = new int[n];
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
int* Vector_Add(int* A, int* B)
{
	int* C = new int[n];
	for (int i = 0; i < n; i++)
	{
		C[i] = A[i] + B[i];
	}
	return C;
}

//Subtracts the vector B from the vector A
int* Vector_Sub(int* A, int* B)
{
	int* C = new int[n];
	for (int i = 0; i < n; i++)
	{
		C[i] = A[i] - B[i];
	}
	return C;
}

//Multiply Vectors
int Vector_Multiply(int* A, int* B)
{
	int C = 0;
	for (int i = 0; i < n; i++)
	{
		C += A[i] * B[i];
	}
	return C;
}

//Adds the matrix A to the matrix B
int** Matrix_Add(int** A, int** B)
{
	int** C = new int*[n];
	for (int i = 0; i < n; i++)
	{
		C[i] = new int[n];
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
	for (int i = 0; i < n; i++)
	{
		C[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			C[i][j] = 0;
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
	for (int i = 0; i < n; i++)
	{
		C[i] = 0;
		for (int j = 0; j < n; j++)
		{
			C[i] += A[j][i] * B[i];
		}
	}
	return C;
}

//Search for minimum element in Matrix
int Matrix_Min(int** A)
{
	int B = A[0][0];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (A[i][j] < B)
			{
				B = A[i][j];
			}
		}
	}
	return B;
}

//Search for maximum element in Matrix
int Matrix_Max(int** A)
{
	int B = A[0][0];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (A[i][j] > B)
			{
				B = A[i][j];
			}
		}
	}
	return B;
}

//Sorting Matrix. Uses bubble sorting like sorting simple vector.
int** Matrix_Sort(int** A)
{
	bool Finished;
	int Temp = 0;
	int* B = new int[n * n];
	int** C = new int*[n];
	for (int i = 0; i < n; i++)
	{
		C[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			B[Temp] = A[i][j];
			Temp++;
		}
	}
	for (int i = 0; i < n * n; i++)
	{
		Finished = true;
		for (int j = 1; j < (n * n - i); j++)
		{
			if (B[j - 1] > B[j])
			{
				Temp = B[j - 1];
				B[j - 1] = B[j];
				B[j] = Temp;
				Finished = false;
			}
		}
		if (Finished)
		{
			break;
		}
	}
	Temp = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = B[Temp];
			Temp++;
		}
	}
	return C;
}

/*
Calculating Func1
d=((A+B)*(C*(MA*ME)))
*/
int Func1(int* A, int* B, int* C, int** MA, int** ME)
{
	int d = Vector_Multiply(Vector_Add(A, B), Matrix_Vector_Multiply(Matrix_Multiply(MA, ME), C));
	return d;
}

/*
Calculating Func2
f=MAX(MG*MK)-MIN(ML+MH)
*/
int Func2(int** MG, int** MK, int** ML, int** MH)
{
	int f = Matrix_Max(Matrix_Multiply(MG, MK)) - Matrix_Min(Matrix_Add(ML, MH));
	return f;
}

/*
Calculating Func3
S=SORT(MS*MT)*O-P
*/
int* Func3(int* O, int* P, int** MS, int** MT)
{
	int* S = Vector_Sub(Matrix_Vector_Multiply(Matrix_Sort(Matrix_Multiply(MS, MT)), O), P);
	return S;
}