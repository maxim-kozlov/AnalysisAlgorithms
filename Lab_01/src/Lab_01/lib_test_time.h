#pragma once
#include <iostream>

using funcDL = std::size_t(*)(const char*, const char*);
double getTime(funcDL getDL, const char* s1, const char* s2, int samples = 10);