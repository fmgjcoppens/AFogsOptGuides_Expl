#pragma once

#include <iostream>
#include "Types.h"

typedef struct TestResult {
	double result; // result of the testfunction
	cc* cpuCycles; // array with CPU cycles
	unsigned int size; // size of cpuCycles
	double* mu; // array with moving average
	double* beta; // array with moving variance

	TestResult(); // default constructor
	TestResult(TestParam params); // constructor that inits arrays
	TestResult(const TestResult& other); // copy constructor
	~TestResult();

} TestResult;
