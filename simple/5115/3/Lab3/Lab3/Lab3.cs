/*
Lab on the topic "Threads in C# language. Tasks"
Variant: 1.15 2.29 3.21
T1: MD=MAX(A+B+C)*(MA*ME)
T2: MF=(MG+MH)*(MK*ML)*(MG+ML)
T3: S=SORT(O*MO)*(MS*MT)
Created: 26.09.2017 8:52 AM
Author: Poshtatska Katerina IO-51
 */

using System;
using System.Threading;

namespace Lab3
{
    class Lab3
    {
        static Data data;

        static void Main()
        {
            Console.WriteLine("Lab3 started");

            int n = 5;
            data = new Data(n);

            Thread T1 = new Thread(TF1);

            Thread T2 = new Thread(TF2);

            Thread T3 = new Thread(TF3);

            //Starting the threads
            T1.Start();
            T2.Start();
            T3.Start();

            //The message will be displayed after all thread ending
            try
            {
                T1.Join();
            }
            catch (ThreadInterruptedException e)
            {
                Console.WriteLine(e.ToString());
            }
            try
            {
                T2.Join();
            }
            catch (ThreadInterruptedException e)
            {
                Console.WriteLine(e.ToString());
            }
            try
            {
                T3.Join();
            }
            catch (ThreadInterruptedException e)
            {
                Console.WriteLine(e.ToString());
            }
            Console.WriteLine("Lab3 finished");
            Console.ReadKey();
        }

        //Thread function TF1
        static void TF1()
        {
            Console.WriteLine("Task T1 started");
            int[] A = new int[data.getN()];
            int[] B = new int[data.getN()];
            int[] C = new int[data.getN()];
            int[,] MA = new int[data.getN(),data.getN()];
            int[,] ME = new int[data.getN(),data.getN()];
            if (data.getN() <= 1)
            {
                A = data.Vector_Input("T1 A");
                B = data.Vector_Input("T1 B");
                C = data.Vector_Input("T1 C");
                MA = data.Matrix_Input("T1 MA");
                ME = data.Matrix_Input("T1 ME");
            }
            else
            {
                A = data.Vector_Input1();
                B = data.Vector_Input1();
                C = data.Vector_Input1();
                MA = data.Matrix_Input1();
                ME = data.Matrix_Input1();
            }
            int[,] MD = { { } };
            try
            {
                Thread.Sleep(1000);
                MD = data.Func1(A, B, C, MA, ME);
                Thread.Sleep(1000);
            }
            catch (ThreadInterruptedException e)
            {
                Console.WriteLine(e);
            }
            if (data.getN() <= 10)
            {
                Console.WriteLine("MD = ");
                data.Matrix_Output(MD);
                Console.WriteLine("");
            }
            Console.WriteLine("Task T1 finished");
        }

        //Thread function TF2
        static void TF2()
        {
            Console.WriteLine("Task T2 started");
            int[,] MG = new int[data.getN(),data.getN()];
            int[,] MH = new int[data.getN(),data.getN()];
            int[,] ML = new int[data.getN(),data.getN()];
            int[,] MK = new int[data.getN(),data.getN()];
            if (data.getN() <= 1)
            {
                MG = data.Matrix_Input("T2 MG");
                MH = data.Matrix_Input("T2 MH");
                ML = data.Matrix_Input("T2 ML");
                MK = data.Matrix_Input("T2 MK");
            }
            else
            {
                MG = data.Matrix_Input1();
                MK = data.Matrix_Input1();
                ML = data.Matrix_Input1();
                MH = data.Matrix_Input1();
            }
            int[,] MF = { { } };
            try
            {
                Thread.Sleep(1000);
                MF = data.Func2(MG, MK, ML, MH);
                Thread.Sleep(1000);
            }
            catch (ThreadInterruptedException e)
            {
                Console.WriteLine(e);
            }
            if (data.getN() <= 10)
            {
                Console.WriteLine("MF = ");
                data.Matrix_Output(MF);
            }
            Console.WriteLine("Task T2 finished");
        }

        //Thread function TF3
        static void TF3()
        {
            Console.WriteLine("Task T3 started");
            int[] O = new int[data.getN()];
            int[,] MO = new int[data.getN(),data.getN()];
            int[,] MS = new int[data.getN(),data.getN()];
            int[,] MT = new int[data.getN(),data.getN()];
            if (data.getN() <= 1)
            {
                O = data.Vector_Input("T3 O");
                MO = data.Matrix_Input("T3 MO");
                MS = data.Matrix_Input("T3 MS");
                MT = data.Matrix_Input("T3 MT");
            }
            else
            {
                O = data.Vector_Input1();
                MO = data.Matrix_Input1();
                MS = data.Matrix_Input1();
                MT = data.Matrix_Input1();
            }
            int[] S = { };
            try
            {
                Thread.Sleep(1000);
                S = data.Func3(O, MO, MS, MT);
                Thread.Sleep(1000);
            }
            catch (ThreadInterruptedException e)
            {
                Console.WriteLine(e);
            }
            if (data.getN() <= 10)
            {
                Console.WriteLine("S =");
                data.Vector_Output(S);
            }
            Console.WriteLine("Task T3 finished");
        }
    }
}
