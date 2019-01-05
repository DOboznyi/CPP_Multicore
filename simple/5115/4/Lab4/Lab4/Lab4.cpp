/*
Laboratory work
on the topic "Threads in WIN32 library"
Variant: 1.15 2.29 3.21
T1: MD=MAX(A+B+C)*(MA*ME)
T2: MF=(MG+MH)*(MK*ML)*(MG+ML)
T3: S=SORT(O*MO)*(MS*MT)
Created: 26.09.2017 8:52 AM
Author: Poshtatska Katerina IO-51

*/

//The specifications of main program Lab4

#include "stdafx.h"
#include "Data.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

void TF1(void);
void TF2(void);
void TF3(void);
int n;


//Main method of Lab4
int main(void)
{
	cout << "Lab4 started" << endl;

	DWORD TidA, TidB, TidC;
	HANDLE hThreadA, hThreadB, hThreadC;

	/*
	Variable n using for rhe size of all matrix and vectors in program.
	data is an exeplar of class Data with parametr n.
	*/
	n = 3;
	Data(n);

	//Announcement of threads with their parametrs. Getting their handles
	hThreadA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TF1, NULL, 0, &TidA);
	hThreadB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TF2, NULL, 0, &TidB);
	hThreadC = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TF3, NULL, 0, &TidC);

	//Setting priority of threads
	SetThreadPriority(hThreadA, THREAD_PRIORITY_LOWEST);
	SetThreadPriority(hThreadB, THREAD_PRIORITY_NORMAL);
	SetThreadPriority(hThreadC, THREAD_PRIORITY_HIGHEST);

	//Waiting the end of running thread
	WaitForSingleObject(hThreadA, INFINITE);
	WaitForSingleObject(hThreadB, INFINITE);
	WaitForSingleObject(hThreadC, INFINITE);

	//Closing the descriptors
	CloseHandle(hThreadA);
	CloseHandle(hThreadB);
	CloseHandle(hThreadC);

	cout << "Lab4 finished" << endl;

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
	Sleep(10);
	int** MD = Func1(A, B, C, MA, ME);
	Sleep(10);
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
	Sleep(10);
	int** MF = Func2(MG, MK, ML, MH);
	Sleep(10);
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
	Sleep(10);
	int* S = Func3(O, MO, MS, MT);
	Sleep(10);
	if (n < 10) {
		cout << "S = ";
		Vector_Output(S);
	}
	cout << "TF3 finished" << endl;
}