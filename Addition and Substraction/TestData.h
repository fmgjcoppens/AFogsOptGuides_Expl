#pragma once

#include <string>
#include <iostream>
#include "Types.h"

typedef struct TestData {
	TestParam params; // the test parameters
	double* data; // the test data
	unsigned int size;


	TestParam getParams(int argc, char** argv);
	double* initRandom(const unsigned int size);
	TestData(); // default constructor
	TestData(int argc, char** argv); // constructor that inits arrays
	TestData(const TestData& other); // copy constructor
	~TestData();

} TestData;

typedef double (*testFunction)(const TestData&); // typedef of a function pointer to a summing function
typedef struct Test {
	std::string testName;
	testFunction testFunction;
} Test;
