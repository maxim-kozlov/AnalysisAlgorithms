// Lab_01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <profileapi.h>
#include <stdlib.h>
#include <time.h>

// ахтунг динамическая память
char* getRandomString(std::size_t len)
{
	char* str = new char[len + 1];
	for (size_t i = 0; i < len; i++)
		str[i] = char(('z' - 'a') * rand() / (double)RAND_MAX) + 'a';
	str[len] = 0;
	return str;
}

std::size_t _getDL(const char* s1, size_t i, const char* s2, size_t j)
{
	std::size_t d;
	if (i == 0)
	{
		if (j == 0)
			d = 0;
		else
			d = j;
	}
	else
	{
		if (j == 0)
			d = i;
		else
		{
			d = min(min(
				_getDL(s1, i, s2, j-1) + 1,
				_getDL(s1, i-1, s2, j) + 1),
				_getDL(s1, i-1, s2, j-1) + (s1[i-1] != s2[j-1]));
		}
	}
	return d;
}
std::size_t getDLevRec(const char* s1, const char* s2)
{
	std::size_t i = strlen(s1);
	std::size_t j = strlen(s2);
	return _getDL(s1, i, s2, j);
}


using funcDL = std::size_t(*)(const char*, const char*);
double getTime(funcDL getDL, const char* s1, const char* s2, int samples = 10)
{
	std::cout << "s1: " << s1 << " (len: " << strlen(s1) << ")" << std::endl;
	std::cout << "s2: " << s2 << " (len: " << strlen(s2) << ")" << std::endl;
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

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= (Frequency.QuadPart * samples);
	return ElapsedMicroseconds.QuadPart;
}

double getTime(funcDL getDL, std::size_t n, std::size_t m)
{
	char* s1 = getRandomString(n), *s2 = getRandomString(m);
	double time = getTime(getDLevRec, s1, s2);
	delete s1;  delete s2;
	return time;
}

int main()
{
	srand(NULL);

	std::cout << getDLevRec("КИТ", "СКАТ") << std::endl;	
	std::cout << "time: " << getTime(getDLevRec, 6, 6) << "ms" << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
