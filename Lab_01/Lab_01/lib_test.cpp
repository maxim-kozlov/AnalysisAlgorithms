#include "lib_test.h"

char* getRandomString(std::size_t len)
{
	char* str = new char[len + 1];
	for (size_t i = 0; i < len; i++)
		str[i] = char(('b' - 'a') * rand() / (double)RAND_MAX) + 'a';
	str[len] = 0;
	return str;
}

double getTime(funcDL getDL, std::size_t n, std::size_t m, int samples)
{
	char* s1 = getRandomString(n), * s2 = getRandomString(m);
	double time = getTime(getDL, s1, s2, samples);
	if (time == 0)
		time = getTime(getDL, s1, s2, samples * 10);
	delete s1;  delete s2;
	return time;
}