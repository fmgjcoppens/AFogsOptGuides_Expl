#include "HelperFunctions.h"

void printHeader(TestParam params)
{
	std::cout << "Array legnth         : " << params.arrayLength << "\n";
	std::cout << "Number of repetitions: " << params.numReps << "\n";
	std::cout << "Loop unroll factor   : " << params.unrollFactor << "\n\n";
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

void writeResults(const std::string name, const TestParam& param, const TestResult& results)
{
	/*
	# Test           : <test name>
	# Length of data : <arrayLength>
	# Number of reps : <results size>
	#
	# RESULT OF TEST : <result.result>
	#
	# of CPU cycles		sliding - average # of CPU cycles
	312312		343746278		0.2763218
	312312		343746278		0.2763218
	.			.				.
	.			.				.
	*/

	std::fstream fout;
	std::string fname = name + "." + std::to_string(param.arrayLength)
		+ "." + std::to_string(param.numReps)
		+ ".txt";
	std::cout << "Results written to '" << fname << "'.\n";
	fout.open(fname, std::ios::out);

	fout << "# Test           : " << name << "\n";
	fout << "# Length of data : " << param.arrayLength << "\n";
	fout << "# Number of reps : " << param.numReps << "\n";
	fout << "#\n";
	fout << "# RESULT OF TEST : " << results.result << "\n";
	fout << "#\n";
	fout << "# of CPU cycles\t\tsliding-average # of CPU cycles\t\tsliding-variance # of CPU cycles\n";
	fout << "#\n";
	for (size_t i = 0; i < param.numReps; i++)
	{
		fout << results.cpuCycles[i] << "\t\t" << results.mu[i] << "\t\t" << results.beta[i] << "\n";
	}
	fout.close();
}

void printArray(double* array, const unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		std::cout << array[i] << " ";
	}
	std::cout << "\n";
}
