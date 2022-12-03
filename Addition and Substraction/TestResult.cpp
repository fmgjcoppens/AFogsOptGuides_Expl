#include "TestResult.h"

TestResult::TestResult() // default constructor
	: result(0.0f),
	cpuCycles(nullptr),
	size(0),
	mu(nullptr),
	beta(nullptr)
{
	//std::cout << "Called TestResult::TestResult default constructor.\n";
}

TestResult::TestResult(const TestParam& params) // constructor that inits arrays
	: params(params),
	result(0.0f),
	size(params.numReps),
	cpuCycles(new cc[params.numReps]),
	mu(new double[params.numReps]),
	beta(new double[params.numReps])
{
	//std::cout << "Called TestResult::TestResult constructor with "
	//	      << params.numReps << " repetitions.\n";
}

TestResult::TestResult(const TestResult& other) // copy constructor
	: result(other.result),
	cpuCycles(other.cpuCycles),
	size(other.size),
	mu(other.mu),
	beta(other.beta)
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
