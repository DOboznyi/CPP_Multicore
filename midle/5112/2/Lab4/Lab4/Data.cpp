//Implementation of class called Data
#include "stdafx.h"
#include "Data.h"
#include <string>
#include <iostream>
#include <windows.h>


using namespace std;
extern int n;
int p;
void Data(int size, int count) {
	n = size;
	p = count;
}

void Find_Borders(int& s, int& f, int num) {
	s = num * n / p;
	f = (num + 1)*n / p;
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
int* Vector_Input1(int num) {
	int* A = new int[n];
	for (int i = 0; i < n; i++) {
		A[i] = num;
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
int** Matrix_Input1(int num)
{
	int** A = new int*[n];
	for (int i = 0; i < n; i++)
	{
		A[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			A[i][j] = num;
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
void Vector_Add(int* A, int* B, int* C, int num)
{
	int s = 0;
	int f = 0;
	Find_Borders(s, f, num);
	for (int i = s; i < f; i++)
	{
		C[i] = A[i] + B[i];
	}
}

//Subtracts the vector B from the vector A
void Vector_Sub(int* A, int* B, int* C, int num)
{
	int s = 0;
	int f = 0;
	Find_Borders(s, f, num);
	for (int i = s; i < f; i++)
	{
		C[i] = A[i] - B[i];
	}
}

//Multiply Vectors
void Vector_Multiply(int* A, int* B, int C, int num)
{
	int s = 0;
	int f = 0;
	Find_Borders(s, f, num);
	C = 0;
	for (int i = s; i < f; i++)
	{
		C += A[i] * B[i];
	}
}

//Adds the matrix A to the matrix B
void Matrix_Add(int** A, int** B, int** C, int num)
{
	int s = 0;
	int f = 0;
	Find_Borders(s, f, num);
	for (int i = s; i < f; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i-s][j] = A[i-s][j] + B[i-s][j];
		}
	}
}

//Subtracts the matrix B from the matrix A
void Matrix_Multiply(int** A, int** B, int **C, int num)
{
	int s = 0;
	int f = 0;
	Find_Borders(s, f, num);
	for (int i = s; i < f; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i - s][j] = 0;
			for (int k = 0; k < n; k++)
			{
				C[i - s][j] += A[i][k] * B[k][j];
			}
		}
	}
}

//Multiply Vector on Matrix
void Matrix_Vector_Multiply(int** A, int* B, int* C, int num)
{
	int s = 0;
	int f = 0;
	Find_Borders(s, f, num);
	for (int i = s; i < f; i++)
	{
		C[i] = 0;
		for (int j = 0; j < n; j++)
		{
			C[i] += A[j][i] * B[i];
		}
	}
}

//Multiply Number on Matrix
void Matrix_Value_Multiply(int** A, int N, int num)
{
	int s = 0;
	int f = 0;
	Find_Borders(s, f, num);
	for (int i = s; i < f; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A[i-s][j] *= N;
		}
	}
}

//Search for minimum element in Vector
void Vector_Min(int* A, int& B, int num)
{
	int s = 0;
	int f = 0;
	Find_Borders(s, f, num);
	B = INT_MAX;
	for (int i = s; i < f; i++)
	{
		if (A[i] < B)
		{
			B = A[i];
		}
	}
}


//Search for maximum element in Vector
void Vector_Max(int* A, int& B, int num)
{
	int s = 0;
	int f = 0;
	Find_Borders(s, f, num);
	B = INT_MIN;
	for (int i = s; i < f; i++)
	{
		if (A[i] > B)
		{
			B = A[i];
		}
	}
}

void Func1(int* Z, int* S, int& max, int& min, int num) {
	Vector_Max(Z, max, num);
	Vector_Min(S, min, num);
}


void Func2(int** MA, int** MB, int** MO, int** MK, int d, int max, int min, int num) {
	int s = 0;
	int f = 0;
	Find_Borders(s, f, num);
	int** Res = new int*[n];
	int** Res1 = MB;
	int** Res2 = new int*[n];
	for (int i = 0; i < n/p; i++)
	{
		Res[i] = new int[n];
		Res2[i] = new int[n];
	}
	Matrix_Multiply(MK, MO, Res, num);
	Matrix_Value_Multiply(Res, min, num);
	Matrix_Value_Multiply(Res, d, num);
	Matrix_Value_Multiply(Res1, max, num);
	Matrix_Add(Res, Res1, Res2, num);
	for (int i = s; i < f; i++) {
		for (int j = 0; j < n; j++) {
			MA[i][j] = Res2[i - s][j];
		}
	}
}
