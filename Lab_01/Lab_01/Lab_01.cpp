// Lab_01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "lib_test_time.h"
#include "lib_distance_word.h"
#include "lib_test.h"
#include <vector>

using namespace std;

vector<double> TestFunc(funcDL getDL, size_t step, size_t max_len, double timeout = 60000)
{
	auto time = vector<double>(ceil(max_len / (double)step) + 1, -1);
	for (size_t len = 1, i = 0; len < max_len; len += step, i++)
	{
		time[i] = getTime(getDL, len, len, 100);
		if (time[i] > timeout)
			return time;
	}
	return time;
}

int TestMode(size_t step, size_t max_len)
{
	std::cout << "run testing..." << std::endl;
	
	char buffer[150];
	const char* line = "------------------------------------------------------------------------------------------------------------\n";
	const char* format = "| %-8d | %-21.3f | %-21.3f | %-21.3f | %-21.3f |\n";

	sprintf_s(buffer, "| %-5s | %-21s | %-21s | %-21s | %-21s |\n", "len(str)", "Dam-Lev no rec", "Lev no rec with matr", "Lev rec with matr", "Lev rec without matr");
	std::cout << line << "           |                                            time (ms)                                          |\n" << line;
	std::cout << buffer << line;

	auto timeDamLevMatr = TestFunc(getDamLevMatr, step, max_len);
	auto timeLevMatr = TestFunc(getLevMatr, step, max_len);
	auto timeLevRecMatr = TestFunc(getLevRecMatr, step, max_len);
	auto timeLevRec = TestFunc(getLevRec, step, _min(11u, max_len));
	
	for (size_t len = 1, i = 0; len < max_len; len += step, i++)
	{
		sprintf_s(buffer, format, len, timeDamLevMatr[i], timeLevMatr[i], timeLevRecMatr[i], i < timeLevRec.size() ? timeLevRec[i] : -1);
		std::cout << buffer << line;
	}

	return 0;
}

std::string InputString(std::string message)
{
	std::string buf;
	std::cout << message;
	std::getline(std::cin, buf);
	return buf;
}

int InputMode()
{
	std::string buf1 = InputString("Input s1: ");
	std::string buf2 = InputString("Input s2: ");
	const char* s1 = buf1.c_str(), * s2 = buf2.c_str();

	size_t n = buf1.length(), m = buf2.length();

	Matrix matr = getMatrixLev(s1, s2);
	std::cout << "Lev no rec with matr: " << matr[n][m] << std::endl;
	std::cout << matr << std::endl;

	matr = getMatrixLevRec(s1, s2);
	std::cout << "Lev rec with matr   : " << matr[n][m] << std::endl;
	std::cout << matr << std::endl;

	matr = getMatrixDamLev(s1, s2);
	std::cout << "Dam-Lev no rec      : " << matr[n][m] << std::endl;
	std::cout << matr << std::endl;

	std::cout << "Lev rec without matr: " << getLevRec(s1, s2) << std::endl;

	return 0;
}

int main(int argc, char* argv[])
{
	int code_error = 0;
	srand(NULL);
	if (argc > 1 && !strcmp(argv[1], "-t"))
		if (argc > 3)
			code_error = TestMode(atoi(argv[2]), atoi(argv[3]));
		else
			code_error = TestMode(50, 1000);
	else
		code_error = InputMode();
	return code_error;
}
