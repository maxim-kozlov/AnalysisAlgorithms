#include "lib_test_time.h"

#include <Windows.h>
#include <profileapi.h>

double getTime(funcDL getDL, const char* s1, const char* s2, int samples)
{
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	// Activity to be timed
	for (size_t i = 0; i < samples; i++)
	{
		getDL(s1, s2);
	}

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	// return ElapsedMicroseconds.QuadPart / (double)samples;
	ElapsedMicroseconds.QuadPart *= 1000000; // sec -> ms
	return ElapsedMicroseconds.QuadPart / (double)(Frequency.QuadPart * samples);
}