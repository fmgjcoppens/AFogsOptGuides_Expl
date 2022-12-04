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
	TestResult Results(testdata.params);

	// Do zero-iteration to kickstart recursion-relations
	initStats(Results, test, testdata);

	// Gather statistics (params, data, results)
	getStats(Results, test, testdata);

	// Compute true mean/variance and error in moving mean/variance
	Results.getTrueMean();
	Results.getTrueVariance();

	return Results;
}

void initStats(TestResult& results, testFunction test, const TestData& testdata)
{
	cc tick = __rdtsc();
	results.result = test(testdata);
	cc tock = __rdtsc();
	results.cpuCycles[0] = tock - tick;
	results.mu[0] = (double)results.cpuCycles[0];
	results.beta[0] = 0;
}

void getStats(TestResult& results, testFunction test, const TestData& testdata)
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

void displayResults(const std::string name, const TestResult& results)
{
	std::cout << "Result of sum : " << results.result << "\n";
	std::cout << "Average number of CPU cycles : " << results.true_mu << "\n";
}

void writeResults(const std::string name, const TestResult& results)
{
	/*
	# Test           : <test name>
	# Length of data : <arrayLength>
	# Number of reps : <results size>
	#
	# RESULT OF TEST : <result.result>
	#
	# iteration		of CPU cycles		sliding - average # of CPU cycles
	1		312312		343746278		0.2763218
	2		312312		343746278		0.2763218
	.			.				.
	.			.				.
	*/

	std::fstream fout;
	std::string fname = name + "." + std::to_string(results.params.arrayLength)
		+ "." + std::to_string(results.params.numReps)
		+ ".txt";
	fout.open(fname, std::ios::out);

	fout << "# Test                    : " << name << "\n";
	fout << "# Length of data          : " << results.params.arrayLength << "\n";
	fout << "# Number of reps          : " << results.params.numReps << "\n";
	fout << "#\n";
	fout << "# Test result             : " << results.result << "\n";
	fout << "# Arithmetic mean ± error : " << results.true_mu << " ± " << results.err_mu << "\n";
	fout << "# Variance ± error        : " << results.true_beta << " ± " << results.err_beta << "\n";
	fout << "#\n";
	fout << "# iteration\t\tof CPU cycles\t\tsliding-average # of CPU cycles\t\tsliding-variance # of CPU cycles\n";
	fout << "#\n";
	for (size_t i = 0; i < results.params.numReps; i++)
	{
		fout << i + 1 << "\t\t" << results.cpuCycles[i] << "\t\t" << results.mu[i] << "\t\t" << results.beta[i] << "\n";
	}
	fout.close();
	std::cout << "Results written to '" << fname << "'.\n\n";
}

void printArray(double* array, const unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		std::cout << array[i] << " ";
	}
	std::cout << "\n";
}
