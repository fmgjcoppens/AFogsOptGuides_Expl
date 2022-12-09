#pragma once

#include "TestParam.h"
#include "Types.h"

typedef struct TestResult {
	TestParam params; // the test parameters
	double result; // result of the testfunction
	cc* cpuCycles; // array with CPU cycles
	unsigned int size; // size of cpuCycles
	bool did_mu = false;
	double* onl_mu; // array with moving mean
	double mu; // true mean
	double err_mu; // error in mean
	double* onl_beta; // array with moving variance
	double beta; // true variance
	double err_beta; // error in variance

	void getMean();
	void getVariance();

	TestResult(); // default constructor
	TestResult(const TestParam& params); // constructor that inits arrays
	TestResult(const TestResult& other); // copy constructor
	~TestResult();

} TestResult;
