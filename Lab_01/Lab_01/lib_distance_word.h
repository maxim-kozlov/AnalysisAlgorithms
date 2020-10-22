#pragma once
#include "Matrix.h"

template <typename T>
const T& _min(const T& a, const T& b)
{
	return a <= b ? a : b;
}

std::size_t getLevRec(const char* s1, const char* s2);
std::size_t getLevMatr(const char* s1, const char* s2);
std::size_t getLevRecMatr(const char* s1, const char* s2);
std::size_t getDamLevMatr(const char* s1, const char* s2);

Matrix getMatrixLev(const char* s1, const char* s2);
Matrix getMatrixLevRec(const char* s1, const char* s2);
Matrix getMatrixDamLev(const char* s1, const char* s2);