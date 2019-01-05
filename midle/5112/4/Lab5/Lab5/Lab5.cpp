/*
Laboratory work
on the topic "Threads in OpenMP library"
Variant: A = d*C*(MO*MK)+e*sort(Z)
Created: 06.03.2018 8:52 PM
Author: Obozniy Dmitriy IO-51

*/

#include "stdafx.h"
#include "Data.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

int n = 12; // size
int p = 4; //processors count
int h = n / p; //subsize

int d;
int e;
int* A = new int[n];
int* C = new int[n];
int* Z = new int[n];
int** MO = new int*[n];
int** MK = new int*[n];


//Main method of Lab4
int main(void)
{
	cout << "Lab4 started" << endl;
	/*
	Variable n using for rhe size of all matrix and vectors in program.
	data is an exeplar of class Data with parametr n.
	*/
	Data(n,p);

	omp_set_num_threads(p);
	#pragma omp parallel shared (d,e,A,C,Z,MO,MK)
	{
		//Input variables
		cout << "TF"<< omp_get_thread_num() <<" started" << endl;
		if (omp_get_thread_num() == 0) {
				
				if (n < 1)
				{
					C = Vector_Input("C");
					Z = Vector_Input("Z");
				}
				else {
					C = Vector_Input1(1);
					Z = Vector_Input1(1);
				}
				Z[0] = -1;
				Z[1] = 2;
				Z[2] = 1;
				Z[3] = -3;
				Z[9] = 5;
				cout << "Z= ";
				Vector_Output(Z);
		}
		else if (omp_get_thread_num() == 1) {
				if (n < 1)
				{
					cout << "d = ";
					cin >> d;
					MO = Matrix_Input("MO");
				}
				else {
					d = 1;
					MO = Matrix_Input1(1);
				}
			}
		else if (omp_get_thread_num() == 3) {
				if (n < 1)
				{
					cout << "e = ";
					cin >> e;
					MK = Matrix_Input("MK");
				}
				else {
					e = 1;
					MK = Matrix_Input1(1);
				}
		}

		//Input sync
		#pragma omp barrier

		//Sorting Zh
		if (omp_get_thread_num() == 3) {
			Func1(Z, omp_get_thread_num());
		}
		else { Func1(Z, omp_get_thread_num()); }

		#pragma omp barrier
		if (omp_get_thread_num() == 0) {
			cout << "Z= ";
			Vector_Output(Z);
		}
		//Sorting Zh sync
		#pragma omp barrier
		//Sorting Z2h
		if (omp_get_thread_num() == 0) {
			Vector_Together(Z, omp_get_thread_num(),0);
			cout << "Z= ";
			Vector_Output(Z);
		}
		if (omp_get_thread_num() == 3) {
			Vector_Together(Z, omp_get_thread_num(), 0);
		}

		//Splitting Z sync
		#pragma omp barrier

		//Splitting Z
		if (omp_get_thread_num() == 0) {
			Vector_Together(Z, omp_get_thread_num(), 1);
			cout << "Z= ";
			Vector_Output(Z);
		}

		#pragma omp barrier

		int di=0;
		int ei=0;
		int* Ci;
		int** MKi;

		//Copying resources
		#pragma omp atomic
		di += d;

		#pragma omp atomic
		ei += e;

		#pragma omp critical(CS1) 
		{
			Ci = C;
		}

		#pragma omp critical(CS2) 
		{
			MKi = MK;
		}

		//Calculating Ah
		Func2(MO, MKi, A, Ci, Z, di, ei, omp_get_thread_num());

		//Output sync
		#pragma omp barrier
		if (omp_get_thread_num()==0)
		{
			if (n <= 20)
			{
				cout << "A= ";
				Vector_Output(A);
			}
		}

		cout << "TF" << omp_get_thread_num() << " finished" << endl;
	}

	cout << "Lab4 finished" << endl;

	cin >> d;
}

