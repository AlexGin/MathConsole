// Math.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <tchar.h>

#include <Windows.h>
#include <math.h>
#include <time.h>
// ==========================================================================
// Stop watch class.
class CStopWatch
{
public:
	// Constructor.
	CStopWatch()
	{
		// Ticks per second.
		QueryPerformanceFrequency(&liPerfFreq);
	}

	// Start counter.
	void Start()
	{
		liStart.QuadPart = 0;
		QueryPerformanceCounter(&liStart);
	}

	// Stop counter.
	void Stop()
	{
		liEnd.QuadPart = 0;
		QueryPerformanceCounter(&liEnd);
	}

	// Get duration.
	long double GetDuration()
	{
		return ((liEnd.QuadPart - liStart.QuadPart) / long double(liPerfFreq.QuadPart)) * 1000;    //return result in milliseconds
	}

private:
	LARGE_INTEGER liStart;
	LARGE_INTEGER liEnd;
	LARGE_INTEGER liPerfFreq;
};

// ==========================================================================
int N_MULTIPLY = 10000000;
const int N_GENERATED = 1000;

int randoms[N_GENERATED];
int outputs[N_GENERATED];

double randDbl[N_GENERATED];
double outpDbl[N_GENERATED];

static void generate_randoms()
{
	CStopWatch watch;
	watch.Start();

	for (int i = 0; i < N_GENERATED; i++)
		randoms[i] = rand();

	watch.Stop();
	long double dur = watch.GetDuration();
	printf("Generating int randoms took %lf msec\n", dur);
}

static void nativeCompute()
{
	CStopWatch watch;
	watch.Start();

	int result = 0;
	for (int i = 2; i < N_MULTIPLY; i++)
	{
		for (int j = 0; j < N_GENERATED; j++)
		{
			result = randoms[j] * i;
			result++;
			outputs[j] = result;
		}

		//if (!(i % 100000))
		//{
		//	MSG msg;
		//	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//	{    /* Loop of message-processing: */
		//		::DispatchMessage(&msg);
		//	}
		//}
	}
	watch.Stop();
	long double dur = watch.GetDuration();
	printf("Native took %lf msec\n", dur);
}

static void generate_dbl_randoms()
{
	CStopWatch watch;
	watch.Start();

	for (int i = 0; i < N_GENERATED; i++)
		randDbl[i] = double(1.11 * (double)rand());

	watch.Stop();
	long double dur = watch.GetDuration();
	printf("Generating double randoms took %lf msec\n", dur);
}

static void nativeComputeDbl() // Floating Point
{
	CStopWatch watch;
	watch.Start();

	double resultDbl = 0.0;
	for (int i = 2; i < N_MULTIPLY; i++)
	{
		for (int j = 0; j < N_GENERATED; j++)
		{
			double dbMult = (double)(i * 1.1);
			resultDbl = randDbl[j] * dbMult;
			resultDbl += 1.555;
			outpDbl[j] = resultDbl;
		}
		//if (!(i % 100000))
		//{
		//	MSG msg;
		//	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//	{    /* Loop of message-processing: */
		//		::DispatchMessage(&msg);
		//	}
		//}
	}
	watch.Stop();
	long double dur = watch.GetDuration();
	printf("Double took %lf msec\n", dur);
}

static void nativeComputeTrg() // Trigonometry
{
	CStopWatch watch;

	watch.Start();
	double resultDbl = 0.0;
	for (int i = 2; i < N_MULTIPLY; i++)
	{
		double dbMult = (double)(i * 2 * M_PI);
		double dbSinValue = sin(dbMult);
		for (int j = 0; j < N_GENERATED; j++)
		{
			// double dbMult = (double)(i * 2 * M_PI);
			resultDbl = randDbl[j] + dbSinValue; // sin(dbMult); // ;
			resultDbl += 0.375;
			outpDbl[j] = resultDbl;
		}

		//if (!(i % 100000))
		//{			
		//	MSG msg;
		//	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//	{    /* Loop of message-processing: */
		//		::DispatchMessage(&msg);
		//	}
		//}
	}
	watch.Stop();
	long double dur = watch.GetDuration();
	printf("Trig took %lf msec\n", dur);
}


int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		N_MULTIPLY = atol(argv[1]);
	}

	time_t tt;
	srand(time(&tt));

	generate_dbl_randoms();
	nativeComputeTrg();
	nativeComputeDbl();

	generate_randoms();
	nativeCompute();

	printf("Finita\n");
	getchar();
    return 0;
}

