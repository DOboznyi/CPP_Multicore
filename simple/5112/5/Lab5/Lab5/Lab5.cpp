/*
Laboratory work
on the topic "Threads in OpenMP library"
Variant: 1.16 2.30 3.22
T1: d=((A+B)*(C*(MA*ME)))
T2: f=MAX(MG*MK)-MIN(ML+MH)
T3: S=SORT(MS*MT)*O-P
Created: 06.10.2017 8:52 PM
Author: Obozniy Dmitriy IO-51

*/

//The specifications of main program Lab5

#include "stdafx.h"
#include "Data.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

void TF1(void); 
void TF2(void);
void TF3(void);
int n;


//Main method of Lab5
int main(void)
{
	cout << "Lab5 started" << endl;
	/*
	Variable n using for rhe size of all matrix and vectors in program.
	data is an exeplar of class Data with parametr n.
	*/
	n = 1000;
	Data(n);

	
	omp_set_num_threads(3);
#pragma omp parallel
	{
#pragma omp sections
		{
#pragma omp section
			{int i = omp_get_num_threads();
			 cout << "Number of threads " << i << endl;
			 TF1();}
#pragma omp section
			{TF2();}
#pragma omp section
			{TF3();}
		}
	}

	cout << "Lab5 finished" << endl;

	system("pause");
}

//Thread function TF1 
void TF1(void) {
	cout << "TF1 started" << endl;
	int* A;
	int* B;
	int* C;
	int** MA;
	int** ME;
	if (n < 1)
	{
		A = Vector_Input("A");
		B = Vector_Input("B");
		C = Vector_Input("C");
		MA = Matrix_Input("MA");
		ME = Matrix_Input("ME");
	}
	else {
		A = Vector_Input1();
		B = Vector_Input1();
		C = Vector_Input1();
		MA = Matrix_Input1();
		ME = Matrix_Input1();
	}
	Sleep(100);
	int d = Func1(A, B, C, MA, ME);
	Sleep(100);
	if (n < 10) {
		cout << "d = " << d << endl;
	}
	cout << "TF1 finished" << endl;
}

//Thread function TF2
void TF2(void) {
	cout << "TF2 started" << endl;
	int** MG;
	int** MK;
	int** ML;
	int** MH;
	if (n < 1)
	{
		MG = Matrix_Input("MG");
		MK = Matrix_Input("MK");
		ML = Matrix_Input("ML");
		MH = Matrix_Input("MH");
	}
	else {
		MG = Matrix_Input1();
		MK = Matrix_Input1();
		ML = Matrix_Input1();
		MH = Matrix_Input1();
	}
	Sleep(100);
	int f = Func2(MG, MK, ML, MH);
	Sleep(100);
	if (n < 10) {
		cout << "f = " << f << endl;
	}
	cout << "TF2 finished" << endl;
}

//Thread function TF3
void TF3(void) {
	cout << "TF3 started" << endl;
	int* O;
	int* P;
	int** MS;
	int** MT;
	if (n < 1)
	{
		O = Vector_Input("O");
		P = Vector_Input("P");
		MS = Matrix_Input("MS");
		MT = Matrix_Input("MT");
	}
	else {
		O = Vector_Input1();
		P = Vector_Input1();
		MS = Matrix_Input1();
		MT = Matrix_Input1();
	}
	Sleep(100);
	int* S = Func3(O, P, MS, MT);
	Sleep(100);
	if (n < 10) {
		cout << "S = ";
		Vector_Output(S);
	}
	cout << "TF3 finished" << endl;
}