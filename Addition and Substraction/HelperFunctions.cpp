#include "HelperFunctions.h"

void printHeader(TestParam params)
{
	std::cout << "# Array legnth         : " << params.arrayLength << "\n";
	std::cout << "# Number of repetitions: " << params.numReps << "\n";
	std::cout << "# Loop unroll factor   : " << params.unrollFactor << "\n";
	std::cout << "#\n";
	std::cout << "# Test name, test result, mean CPU cycles, std CPU cycles\n";
}

TestResult getResults(const TestData& testdata, testFunction test)
{
	// Declare and init test results
	TestResult results(testdata.params);

	// Do zero-iteration to kickstart recursion-relation
	cc tick = __rdtsc();
	results.result = test(testdata);
	cc tock = __rdtsc();
	results.cpuCycles[0] = tock - tick;
	results.mu[0] = (double)results.cpuCycles[0];
	results.beta[0] = 0;

	// Begin statistics gathering (params, data, results)
	getStats(testdata, test, results);

	return results;
}

void getStats(const TestData& testdata, testFunction test, TestResult& results)
{
	for (unsigned int i = 1; i < testdata.params.numReps; ++i)
	{
		cc tick = __rdtsc();
		results.result = test(testdata);
		cc tock = __rdtsc();
		results.cpuCycles[i] = tock - tick;

		double factor_mu = 1.0f / (i + 1); // incremented by one because index 1 = 2nd element
		double previous_mu = results.mu[i - 1];
		double factor_beta = factor_mu * factor_mu;
		double previous_beta = results.beta[0];
		double diff = previous_mu - results.cpuCycles[i];

		// update mu_{i + 1} == mu[i] from mu_{i} == mu[i - 1]
		results.mu[i] = previous_mu + factor_mu * (results.cpuCycles[i] - previous_mu);
		// update variance beta
		results.beta[i] = previous_beta + factor_beta * (i * diff * diff - (i + 1) * previous_beta);

	} // End statistics gathering
}

void printArray(double* array, const unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		std::cout << array[i] << " ";
	}
	std::cout << "\n";
}
