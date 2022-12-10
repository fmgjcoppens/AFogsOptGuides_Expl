#pragma once

#include "TestParam.h"

typedef struct TestData {

	TestParam params; // the test parameters
	double* data; // the test data
	unsigned int size;

	TestData(); // default constructor
	TestData(const TestParam& params); // constructor that inits arrays
	TestData(const TestData& other); // copy constructor
	~TestData();

	double* initRandom(const unsigned int size);

} TestData;
