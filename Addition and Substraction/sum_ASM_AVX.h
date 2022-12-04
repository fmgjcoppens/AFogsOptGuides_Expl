#pragma once
#include "TestData.h"

extern "C" double __sum_ASM_AVX(double*, unsigned int);
double sum_ASM_AVX(const TestData& testdata);
