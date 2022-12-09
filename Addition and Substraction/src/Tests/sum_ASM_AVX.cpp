#include "sum_ASM_AVX.h"

double sum_ASM_AVX(const TestData& testdata)
{
	return __sum_ASM_AVX(testdata.data, testdata.size);
}
