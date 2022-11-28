#pragma once

#include "TestData.h"
#include "TestResult.h"

void printHeader(TestParam params);
TestResult getResults(const TestData& data, testFunction sum);
TestParam getParams(int argc, char** argv);
void getStats(const TestData& testdata, testFunction test, TestResult& results);
void printArray(double* array, const unsigned int size);