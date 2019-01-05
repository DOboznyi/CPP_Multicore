/*
Laboratory work
on the topic "Threads in OpenMP library"
Variant: 1.15 2.29 3.21
T1: MD=MAX(A+B+C)*(MA*ME)
T2: MF=(MG+MH)*(MK*ML)*(MG+ML)
T3: S=SORT(O*MO)*(MS*MT)
Created: 26.09.2017 8:52 AM
Author: Poshtatska Katerina IO-51

*/

//The specifications of main program Lab5

#include "stdafx.h"
#include "Data.h"
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
	int* A = Vector_Input();
	int* B = Vector_Input();
	int* C = Vector_Input();
	int** MA = Matrix_Input();
	int** ME = Matrix_Input();
	int** MD = Func1(A, B, C, MA, ME);
	if (n < 10) {
		cout << "MD =" << endl;
		Matrix_Output(MD);
	}
	cout << "TF1 finished" << endl;
}

//Thread function TF2
void TF2(void) {
	cout << "TF2 started" << endl;
	int** MG = Matrix_Input();
	int** MH = Matrix_Input();
	int** ML = Matrix_Input();
	int** MK = Matrix_Input();
	int** MF = Func2(MG, MK, ML, MH);
	if (n < 10) {
		cout << "MF =" << endl;
		Matrix_Output(MF);
	}
	cout << "TF2 finished" << endl;
}

//Thread function TF3
void TF3(void) {
	cout << "TF3 started" << endl;
	int* O = Vector_Input();
	int** MO = Matrix_Input();
	int** MS = Matrix_Input();
	int** MT = Matrix_Input();
	int* S = Func3(O, MO, MS, MT);
	if (n < 10) {
		cout << "S = ";
		Vector_Output(S);
	}
	cout << "TF3 finished" << endl;
}