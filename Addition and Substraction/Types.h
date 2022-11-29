#pragma once

#include <intrin.h>
#pragma intrinsic(__rdtsc)
typedef unsigned __int64 cc;

typedef struct TestParam {
	unsigned int arrayLength;
	unsigned int numReps;
	unsigned int unrollFactor;
	char test;
} TestParam;
