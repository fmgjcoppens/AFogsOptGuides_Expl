#include "TestResult.h"

void TestResult::getMean()
{
	unsigned int size = params.numReps;
	for (size_t i = 0; i < size; i++)
	{
		mu += cpuCycles[i];
	}
	mu /= size;
	err_mu = onl_mu[size - 1] - mu;
	did_mu = true;
}

void TestResult::getVariance()
{
	if (!did_mu)
	{
		std::cout << "PLEASE CALL 'TestResult::getMean()' BEFORE 'TestResult::getVariance()'!\n";
		return;
	}
	unsigned int size = params.numReps;
	for (size_t i = 0; i < size; i++)
	{
		beta += (cpuCycles[i] - mu) * (cpuCycles[i] - mu);
	}
	beta /= size;
	err_beta = onl_beta[size - 1] - beta;
}

TestResult::TestResult() // default constructor
	: result(0.0f),
	cpuCycles(nullptr),
	size(0),
	onl_mu(nullptr),
	mu(0),
	err_mu(0),
	onl_beta(nullptr),
	beta(0),
	err_beta(0)
{
	//std::cout << "Called TestResult::TestResult default constructor.\n";
}

TestResult::TestResult(const TestParam& params) // constructor that inits arrays
	: params(params),
	result(0.0f),
	size(params.numReps),
	cpuCycles(new cc[params.numReps]),
	onl_mu(new double[params.numReps]),
	mu(0),
	err_mu(0),
	onl_beta(new double[params.numReps]),
	beta(0),
	err_beta(0)
{
	//std::cout << "Called TestResult::TestResult constructor with "
	//	      << params.numReps << " repetitions.\n";
}

TestResult::TestResult(const TestResult& other) // copy constructor
	: result(other.result),
	cpuCycles(other.cpuCycles),
	size(other.size),
	onl_mu(other.onl_mu),
	mu(other.mu),
	err_mu(other.err_mu),
	onl_beta(other.onl_beta),
	beta(other.beta),
	err_beta(other.err_beta)
{
	//std::cout << "Called TestResult::TestResult copy constructor.\n";
}

TestResult::~TestResult() // destructor
{
	//std::cout << "Called TestResult::~TestResult destructor.\n";
	delete [] cpuCycles;
	delete [] onl_mu;
	delete [] onl_beta;
}

