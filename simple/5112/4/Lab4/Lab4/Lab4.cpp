/*
Laboratory work
on the topic "Threads in WIN32 library"
Variant: 1.16 2.30 3.22
T1: d=((A+B)*(C*(MA*ME)))
T2: f=MAX(MG*MK)-MIN(ML+MH)
T3: S=SORT(MS*MT)*O-P
Created: 29.09.2017 8:52 PM
Author: Obozniy Dmitriy IO-51

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
	hThreadC = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TF3, NULL, CREATE_SUSPENDED, &TidC);

	//Setting priority of threads
	SetThreadPriority(hThreadA, THREAD_PRIORITY_LOWEST);
	SetThreadPriority(hThreadB, THREAD_PRIORITY_NORMAL);
	SetThreadPriority(hThreadC, THREAD_PRIORITY_HIGHEST);

	//Starting thread C
	ResumeThread(hThreadC);

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
		A = Vector_Input1("A");
		B = Vector_Input1("B");
		C = Vector_Input1("C");
		MA = Matrix_Input1("MA");
		ME = Matrix_Input1("ME");
	}
	Sleep(10);
	int d = Func1(A, B, C, MA, ME);
	Sleep(10);
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
		MG = Matrix_Input1("MG");
		MK = Matrix_Input1("MK");
		ML = Matrix_Input1("ML");
		MH = Matrix_Input1("MH");
	}
	Sleep(10);
	int f = Func2(MG, MK, ML, MH);
	Sleep(10);
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
		O = Vector_Input1("O");
		P = Vector_Input1("P");
		MS = Matrix_Input1("MS");
		MT = Matrix_Input1("MT");
	}
	Sleep(10);
	int* S = Func3(O, P, MS, MT);
	Sleep(10);
	if (n < 10) {
		cout << "S = ";
		Vector_Output(S);
	}
	cout << "TF3 finished" << endl;
}