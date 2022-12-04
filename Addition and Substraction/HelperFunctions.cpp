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
	Results.getMean();
	Results.getVariance();

	return Results;
}

void initStats(TestResult& results, testFunction test, const TestData& testdata)
{
	cc tick = __rdtsc();
	results.result = test(testdata);
	cc tock = __rdtsc();
	results.cpuCycles[0] = tock - tick;
	results.onl_mu[0] = (double)results.cpuCycles[0];
	results.onl_beta[0] = 0;
}

void getStats(TestResult& results, testFunction test, const TestData& testdata)
{
	for (unsigned int i = 1; i < testdata.params.numReps; ++i)
	{
		cc tick = __rdtsc();
		results.result = test(testdata);
		cc tock = __rdtsc();

		cc current_cc = tock - tick;
		double previous_mu = results.onl_mu[i - 1];
		double previous_beta = results.onl_beta[i - 1];

		results.cpuCycles[i] = current_cc;
		results.onl_mu[i] = updateMu(i, previous_mu, current_cc);
		results.onl_beta[i] = updateBeta(i, previous_mu, previous_beta, current_cc);
	} // End statistics gathering
}

double updateMu(const unsigned int position, const double previous_mu, const cc current_cc)
{
	double factor = 1.0f / (position + 1); // incremented by one because index 1 = 2nd element
	return previous_mu + factor * (current_cc - previous_mu);
}

double updateBeta(const unsigned int position, const double previous_mu, const double previous_beta, const cc current_cc)
{
	double factor = (1.0f / (position + 1)) * (1.0f / (position + 1));
	double diff = previous_mu - current_cc;
	return previous_beta + factor * (position * diff * diff - (position + 1) * previous_beta);
}

void displayResults(const std::string name, const TestResult& results)
{
	std::cout << "Result of sum : " << results.result << "\n";
	std::cout << "Average number of CPU cycles : " << results.mu << "\n";
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
	fout << "# Arithmetic mean ± error : " << results.mu << " ± " << results.err_mu << "\n";
	fout << "# Variance ± error        : " << results.beta << " ± " << results.err_beta << "\n";
	fout << "#\n";
	fout << "# iteration\t\tof CPU cycles\t\tsliding-average # of CPU cycles\t\tsliding-variance # of CPU cycles\n";
	fout << "#\n";
	for (size_t i = 0; i < results.params.numReps; i++)
	{
		fout << i + 1 << "\t\t" << results.cpuCycles[i] << "\t\t" << results.onl_mu[i] << "\t\t" << results.onl_beta[i] << "\n";
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
