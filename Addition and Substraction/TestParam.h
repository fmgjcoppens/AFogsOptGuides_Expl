#pragma once

#include <string>
#include <iostream>

typedef struct TestParam {
	unsigned int arrayLength;
	unsigned int numReps;
	unsigned int unrollFactor;
	char test;

	TestParam();
	TestParam(int argc, char** argv);
	TestParam(const TestParam& other);
	~TestParam();
} TestParam;
