/*
Laboratory work
on the topic "Threads in OpenMP library"
Variant: A = d*B*(MO*MK)-e*sort(Z)
Author: Poshtatska Katerina IO-51

*/

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

int n = 12000; // size
int p = 6; //processors count
int H = n / p; //subsize

int d;
int e;
int* A = new int[n];
int* B = new int[n];
int* Z = new int[n];
int** MO = new int*[n];
int** MK = new int*[n];
int** MR = new int*[n];


//Main method of Lab4
int main(void)
{
	cout << "Lab4 started" << endl;

	for (int i = 0; i < n; i++)
	{
		MR[i] = new int[n];
	}

	omp_set_num_threads(p);
	#pragma omp parallel shared (d,e,A,B,Z,MO,MK,MR)
	{
		cout << "TF"<< omp_get_thread_num() <<" started" << endl;
		//Input variables
		if (omp_get_thread_num() == 0) {
			for (int i = 0; i < n; i++) {
				Z[i] = 1;
			}
			Z[0] = -1;
			Z[1] = 2;
			Z[2] = 1;
			Z[3] = -3;
			e = 1;
		}
		else if (omp_get_thread_num() == 1) {
			for (int i = 0; i < n; i++)
			{
				B[i] = 1;
				MK[i] = new int[n];
				for (int j = 0; j < n; j++)
				{
					MK[i][j] = 1;
				}
			}
		}
		else if (omp_get_thread_num() == 3) {
			for (int i = 0; i < n; i++)
			{
				MO[i] = new int[n];
				for (int j = 0; j < n; j++)
				{
					MO[i][j] = 1;
				}
			}
			d = 1;
		}

		//Input sync
		#pragma omp barrier

		//Sorting Zh
		int* X = new int[n];
		int num = omp_get_thread_num();
		bool Finished;
		int Temp = 0;
		#pragma omp parallel
		for (int i = 0; i < H; i++)
		{
			Finished = true;
			#pragma omp parallel
			for (int j = 1; j < (H - i); j++)
			{
				if (Z[j - 1 + H* num] > Z[j + H * num])
				{
					Temp = Z[j - 1 + H * num];
					Z[j - 1 + H * num] = Z[j + H * num];
					Z[j + H * num] = Temp;
					Finished = false;
				}
			}
			if (Finished)
			{
				break;
			}
		}

		//Sorting Z2h
		#pragma omp barrier
		if (num % 2 == 0) {
			int num_T = 0;
			int* C = new int[2]{ num * H, (num+1) * H };
			int* C1 = new int[2]{ num * H, (num + 1) * H };
			int* C2 = new int[2]{ H, H };
			#pragma omp parallel
			for (int i = num * H; i < n; i++)
			{
				Temp = INT_MAX;
				for (int j = 0; j < 2; j++)
				{
					if ((C[j] - C1[j]) < C2[j])
					{
						if (Z[C[j]] < Temp)
						{
							num_T = j;
							Temp = Z[C[j]];
						}
					}
				}
				X[i] = Temp;
				C[num_T]++;
			}
			#pragma omp parallel
			for (int i = num * H; i < (num+2)*H; i++)
			{
				Z[i] = X[i];
			}
		}
		
		//Sorting Zh = Sort(Z2h,Z2h,Z2h)
		#pragma omp barrier
		if (num == 0) {
			int num_T = 0;
			int*C = new int[3]{ 0, 2 * H, 4*H };
			int* C1 = new int[3]{ 0, 2 * H, 4 * H };
			int* C2 = new int[3]{ 2 * H, 2 * H, 2 * H };
			#pragma omp parallel
			for (int i = 0; i < n; i++)
			{
				Temp = INT_MAX;
				#pragma omp parallel
				for (int j = 0; j < 3; j++)
				{
					if ((C[j] - C1[j]) < C2[j])
					{
						if (Z[C[j]] < Temp)
						{
							num_T = j;
							Temp = Z[C[j]];
						}
					}
				}
				X[i] = Temp;
				C[num_T]++;
			}
			#pragma omp parallel
			for (int i = 0; i < n; i++)
			{
				Z[i] = X[i];
			}
		}

		//Sort sync
		#pragma omp barrier

		int di=0;
		int ei=0;
		int* Bi;
		int** MKi;

		//Copying resources
		#pragma omp atomic
		di += d;

		#pragma omp atomic
		ei += e;

		#pragma omp critical(CS1) 
		{
			Bi = B;
		}

		#pragma omp critical(CS2) 
		{
			MKi = MK;
		}

		//Calculating Ah
		#pragma omp parallel
		for (int i = num * H; i < (num+1) * H; i++)
		{
			#pragma omp parallel
			for (int j = 0; j < n; j++)
			{
				MR[i][j] = 0;
				#pragma omp parallel
				for (int k = 0; k < n; k++)
				{
					MR[i][j] += MO[i][k] * MKi[k][j];
				}
				MR[i][j] *= di;
			}
		}
		#pragma omp parallel
		for (int i = num * H; i < (num + 1) * H; i++)
		{
			A[i] = 0;
			#pragma omp parallel
			for (int j = 0; j < n; j++)
			{
				A[i] += MR[i][j] * Bi[j];
			}
			A[i] -= ei * Z[i];
		}

		//Output sync
		#pragma omp barrier
		if (omp_get_thread_num()==0)
		{
			if (n < 36) {
				cout << "A = ";
				for (int i = 0; i < n; i++)
				{
					cout << A[i] << " ";
				}
				cout << endl;
			}
		}

		cout << "TF" << omp_get_thread_num() << " finished" << endl;
	}

	cout << "Lab4 finished" << endl;

	cin >> d;
}

