#include "lib_distance_word.h"
#include <string>

std::size_t _getLevRec(const char* s1, size_t i, const char* s2, size_t j)
{
	std::size_t d;
	if (i == 0)
		d = j;
	else if (j == 0)
		d = i;
	else
	{
		d = _min(_min(
			_getLevRec(s1, i, s2, j - 1) + 1,
			_getLevRec(s1, i - 1, s2, j) + 1),
			_getLevRec(s1, i - 1, s2, j - 1) + (s1[i - 1] != s2[j - 1])
		);
	}
	return d;
}
std::size_t getLevRec(const char* s1, const char* s2)
{
	std::size_t i = strlen(s1);
	std::size_t j = strlen(s2);
	return _getLevRec(s1, i, s2, j);
}

std::size_t getLevMatr(const char* s1, const char* s2)
{
	std::size_t n = strlen(s1);
	std::size_t m = strlen(s2);
	auto matr = Matrix(n + 1, m + 1);

	for (size_t i = 0; i <= n; i++)
		matr[i][0] = i;

	for (size_t j = 1; j <= m; j++)
		matr[0][j] = j;

	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = 1; j <= m; j++)
		{
			matr[i][j] = _min(_min(
				matr[i - 1][j] + 1,
				matr[i][j - 1] + 1),
				matr[i - 1][j - 1] + (s1[i - 1] != s2[j - 1])
			);
		}
	}

	return matr[n][m];
}

// אכדמנטעל ױטנרבונדא


std::size_t _getLevRecMatr(const char* s1, size_t i, const char* s2, size_t j, std::size_t** matr)
{
	if (i == 0)
		matr[i][j] = j;
	else if (j == 0)
		matr[i][j] = i;
	else
	{
		if (matr[i][j - 1] == -1)
			matr[i][j - 1] = _getLevRecMatr(s1, i, s2, j - 1, matr);
		if (matr[i - 1][j] == -1)
			matr[i - 1][j] = _getLevRecMatr(s1, i - 1, s2, j, matr);
		if (matr[i - 1][j - 1] == -1)
			matr[i - 1][j - 1] = _getLevRecMatr(s1, i - 1, s2, j - 1, matr);
		matr[i][j] = _min(_min(matr[i][j - 1], matr[i - 1][j]) + 1, matr[i - 1][j - 1] + (s1[i - 1] != s2[j - 1]));
	}

	return matr[i][j];
}
std::size_t getLevRecMatr(const char* s1, const char* s2)
{
	std::size_t n = strlen(s1);
	std::size_t m = strlen(s2);
	auto matr = Matrix(n + 1, m + 1);

	for (size_t i = 0; i <= n; i++)
		matr[i][0] = i;

	for (size_t j = 1; j <= m; j++)
		matr[0][j] = j;

	for (size_t i = 1; i <= n; i++)
		for (size_t j = 1; j <= m; j++)
			matr[i][j] = -1;

	return _getLevRecMatr(s1, n, s2, m, matr.GetData());
}

std::size_t getDamLevMatr(const char* s1, const char* s2)
{
	std::size_t n = strlen(s1);
	std::size_t m = strlen(s2);
	auto matr = Matrix(n + 1, m + 1);

	for (size_t i = 0; i <= n; i++)
		matr[i][0] = i;

	for (size_t j = 1; j <= m; j++)
		matr[0][j] = j;

	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = 1; j <= m; j++)
		{
			matr[i][j] = _min(_min(
				matr[i - 1][j] + 1,
				matr[i][j - 1] + 1),
				matr[i - 1][j - 1] + (s1[i - 1] != s2[j - 1]
					));

			if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1])
				matr[i][j] = _min(matr[i][j], matr[i - 2][j - 2] + 1);
		}
	}

	return matr[n][m];
}


Matrix getMatrixLev(const char* s1, const char* s2)
{
	std::size_t n = strlen(s1);
	std::size_t m = strlen(s2);
	auto matr = Matrix(n + 1, m + 1);

	for (size_t i = 0; i <= n; i++)
		matr[i][0] = i;

	for (size_t j = 1; j <= m; j++)
		matr[0][j] = j;

	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = 1; j <= m; j++)
		{
			matr[i][j] = _min(_min(
				matr[i - 1][j] + 1,
				matr[i][j - 1] + 1),
				matr[i - 1][j - 1] + (s1[i - 1] != s2[j - 1]
					));
		}
	}

	return matr;
}

Matrix getMatrixLevRec(const char* s1, const char* s2)
{
	std::size_t n = strlen(s1);
	std::size_t m = strlen(s2);
	auto matr = Matrix(n + 1, m + 1);
	
	for (size_t i = 0; i <= n; i++)
		matr[i][0] = i;

	for (size_t j = 1; j <= m; j++)
		matr[0][j] = j;

	for (size_t i = 1; i <= n; i++)
		for (size_t j = 1; j <= m; j++)
			matr[i][j] = -1;
	_getLevRecMatr(s1, n, s2, m, matr.GetData());
	return matr;
}
Matrix getMatrixDamLev(const char* s1, const char* s2)
{
	std::size_t n = strlen(s1);
	std::size_t m = strlen(s2);
	auto matr = Matrix(n + 1, m + 1);

	for (size_t i = 0; i <= n; i++)
		matr[i][0] = i;

	for (size_t j = 1; j <= m; j++)
		matr[0][j] = j;

	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = 1; j <= m; j++)
		{
			matr[i][j] = _min(_min(
				matr[i - 1][j] + 1,
				matr[i][j - 1] + 1),
				matr[i - 1][j - 1] + (s1[i - 1] != s2[j - 1]
					));

			if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1])
				matr[i][j] = _min(matr[i][j], matr[i - 2][j - 2] + 1);
		}
	}
	return matr;
}