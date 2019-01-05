//Specification of class called data
#include <windows.h>
#pragma once
void Data(int size, int count);
int* Vector_Input(char* name);
int* Vector_Input1(int num);
void Vector_Output(int* A);
int** Matrix_Input(char* name);
int** Matrix_Input1(int num);
void Matrix_Output(int** A);
void Func1(int* Z, int* S, int& max, int& min, int num);
void Func2(int** MA, int** MB, int** MO, int** MK, int d, int max, int min, int num);