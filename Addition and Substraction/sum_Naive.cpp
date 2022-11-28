#include "sum_Naive.h"

double sum_Naive(const TestData& testdata)
{
	double total = 0.0;
	for (unsigned int i = 0; i < testdata.size; ++i)
	{
		total += testdata.data[i];
	}
	return total;
}
