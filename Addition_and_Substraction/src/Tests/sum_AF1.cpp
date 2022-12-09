#include "sum_AF1.h"

double sum_AF1(const TestData& testdata)
{
	double total1 = 0.0;
	double total2 = 0.0;
	double total3 = 0.0;
	double total4 = 0.0;

	double* tmp = testdata.data;
	unsigned int reduced_size = testdata.size / 4;
	for (unsigned int i = 0; i < reduced_size; ++i)
	{
		total1 += tmp[0];
		total2 += tmp[1];
		total3 += tmp[2];
		total4 += tmp[3];
		tmp += 4;
	}

	unsigned int remainder = testdata.size & 3;
	for (unsigned int i = 0; i < remainder; ++i)
	{
		total1 += *tmp++;
	}

	return (total1 + total2) + (total3 + total4);
}
