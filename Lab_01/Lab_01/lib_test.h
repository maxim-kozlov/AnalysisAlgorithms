#pragma once
#include <time.h>
#include <string>
#include <stdlib.h>
#include "lib_test_time.h"

// ������ ������������ ������
char* getRandomString(std::size_t len);

double getTime(funcDL getDL, std::size_t n, std::size_t m, int samples = 10);