#pragma once

#include <fstream>

#include "TestData.h"
#include "TestResult.h"

void printHeader(TestParam params);
TestResult getResults(const TestData& data, testFunction sum);
void initStats(TestResult& results, testFunction test, const TestData& testdata);
void getStats(TestResult& results, testFunction test, const TestData& testdata);
void displayResults(const std::string name, const TestResult& results);
void writeResults(const std::string name, const TestResult& results);
void printArray(double* array, const unsigned int size);