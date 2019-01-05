//Implementation of class called Data

using System;

namespace Lab3
{
    public class Data
    {

        private int n;

    public Data(int n) {
        this.n = n;
    }

    public int getN() {
        return n;
    }

    //Input Vector from keyboard
    public int[] Vector_Input(String name) {
        int[] A = new int[n];
        for (int i = 0; i < n; i++) {
            Console.Write(name + "[" + i + "] = ");
            A[i] = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine();
        }
        return A;
    }

    //Fill Vector with 1
    public int[] Vector_Input1() {
        int[] A = new int[n];
        for (int i = 0; i < n; i++) {
            A[i] = 1;
        }
        return A;
    }

    //Print Vector on screen
    public void Vector_Output(int[] A) {
        for (int i = 0; i < n; i++) {
                Console.Write(A[i] + " ");
        }
            Console.WriteLine();
    }

    //Input Matrix from keyboard
    public int[,] Matrix_Input(String name) {
        int[,] A = new int[n,n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                    Console.Write(name + "[" + i + "]" + "[" + j + "] = ");
                A[i,j] = Convert.ToInt32(Console.ReadLine());
                Console.WriteLine();
            }
        }
        return A;
    }

    //Fill Matrix with 1
    public int[,] Matrix_Input1() {
        int[,] A = new int[n,n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i,j] = 1;
            }
        }
        return A;
    }

    //Print Matrix on screen
    public void Matrix_Output(int[,] A) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                    Console.Write(A[i,j] + " ");
            }
            Console.WriteLine();
        }
    }

    //Adds the vector A to the vector B
    private int[] Vector_Add(int[] A, int[] B, int[] C) {
        int[] D = new int[n];
        for (int i = 0; i < n; i++) {
            D[i] = A[i] + B[i] + C[i];
        }
        return D;
    }

    //Adds the matrix A to the matrix B
    private int[,] Matrix_Add(int[,] A, int[,] B) {
        int[,] C = new int[n,n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i,j] = A[i,j] + B[i,j];
            }
        }
        return C;
    }

    //Subtracts the matrix B from the matrix A
    private int[,] Matrix_Multiply(int[,] A, int[,] B) {
        int[,] C = new int[n,n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i,j] = 0;
                for (int k = 0; k < n; k++) {
                    C[i,j] += A[i,k] * B[k,j];
                }
            }
        }
        return C;
    }

    //Multiply Vector on Matrix
    private int[] Matrix_Vector_Multiply(int[,] A, int[] B) {
        int[] C = new int[n];
        for (int i = 0; i < n; i++) {
            C[i] = 0;
            for (int j = 0; j < n; j++) {
                C[i] += A[j,i] * B[i];
            }
        }
        return C;
    }

    //Multiply Value on Matrix
    private int[,] Matrix_Value_Multiply(int[,] A, int B) {
        int[,] C = new int[n,n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i,j] = A[j,i] * B;
            }
        }
        return C;
    }

    //Search for maximum element in Vector
    private int Vector_Max(int[] A) {
        int B = A[0];
        for (int i = 0; i < n; i++) {
            if (A[i] > B) {
                B = A[i];
            }
        }
        return B;
    }

    //Sorting Matrix. Uses bubble sorting like sorting simple vector.
    private int[] Vector_Sort(int[] A) {
        Boolean Finished;
        int Temp = 0;
        int[] B = new int[n];
        for (int i = 0; i < n; i++) {
            B[i] = A[i];
        }
        for (int i = 0; i < n; i++) {
            Finished = true;
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
    public int[,] Func1(int[] A, int[] B, int[] C, int[,] MA, int[,] ME) {
        int[,] MD = Matrix_Value_Multiply(Matrix_Multiply(MA, ME), Vector_Max(Vector_Add(A, B, C)));
        return MD;
    }

    /*
    Calculating Func2
    MF=(MG+MH)*(MK*ML)*(MG+ML)
     */
    public int[,] Func2(int[,] MG, int[,] MH, int[,] MK, int[,] ML) {
        int[,] MF = Matrix_Multiply(Matrix_Multiply(Matrix_Add(MG, MH), Matrix_Multiply(MK, ML)), Matrix_Add(MG, ML));
        return MF;
    }

    /*
    Calculating Func3
    S=SORT(O*MO)*(MS*MT)
     */
    public int[] Func3(int[] O, int[,] MO, int[,] MS, int[,] MT) {
        int[] S = Matrix_Vector_Multiply(Matrix_Multiply(MS, MT), Vector_Sort(Matrix_Vector_Multiply(MO, O)));
        return S;
    }
    }
}
