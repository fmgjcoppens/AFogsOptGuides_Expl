#include "TestResult.h"

void TestResult::getTrueMean()
{
	unsigned int size = params.numReps;
	for (size_t i = 0; i < size; i++)
	{
		true_mu += cpuCycles[i];
	}
	true_mu /= size;
	err_mu = mu[size - 1] - true_mu;
}

void TestResult::getTrueVariance()
{
	unsigned int size = params.numReps;
	for (size_t i = 0; i < size; i++)
	{
		true_beta += (cpuCycles[i] - true_mu) * (cpuCycles[i] - true_mu);
	}
	true_beta /= size;
	err_beta = beta[size - 1] - true_beta;
}

TestResult::TestResult() // default constructor
	: result(0.0f),
	cpuCycles(nullptr),
	size(0),
	mu(nullptr),
	true_mu(0),
	err_mu(0),
	beta(nullptr),
	true_beta(0),
	err_beta(0)
{
	//std::cout << "Called TestResult::TestResult default constructor.\n";
}

TestResult::TestResult(const TestParam& params) // constructor that inits arrays
	: params(params),
	result(0.0f),
	size(params.numReps),
	cpuCycles(new cc[params.numReps]),
	mu(new double[params.numReps]),
	true_mu(0),
	err_mu(0),
	beta(new double[params.numReps]),
	true_beta(0),
	err_beta(0)
{
	//std::cout << "Called TestResult::TestResult constructor with "
	//	      << params.numReps << " repetitions.\n";
}

TestResult::TestResult(const TestResult& other) // copy constructor
	: result(other.result),
	cpuCycles(other.cpuCycles),
	size(other.size),
	mu(other.mu),
	true_mu(other.true_mu),
	err_mu(other.err_mu),
	beta(other.beta),
	true_beta(other.true_beta),
	err_beta(other.err_beta)
{
	//std::cout << "Called TestResult::TestResult copy constructor.\n";
}

TestResult::~TestResult() // destructor
{
	//std::cout << "Called TestResult::~TestResult destructor.\n";
	delete [] cpuCycles;
	delete [] mu;
	delete [] beta;
}

