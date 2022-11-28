#include "TestData.h"
#include "HelperFunctions.h"

TestParam TestData::getParams(int argc, char** argv)
{
	TestParam params;
	switch (argc)
	{
	case 1: // no arguments, run all tests with default values
		params.arrayLength = 1024;
		params.numReps = 1000;
		params.unrollFactor = 4;
		params.test = 'a';
		break;
	case 4: // all tests with user defined values
		params.arrayLength = atoi(argv[1]);
		params.numReps = atoi(argv[2]);
		params.unrollFactor = atoi(argv[3]);
		params.test = 'a';
		break;
	case 5: // specific test with user defined values
		params.arrayLength = atoi(argv[1]);
		params.numReps = atoi(argv[2]);
		params.unrollFactor = atoi(argv[3]);
		params.test = *argv[4];
		break;
	default: // exit with message if none of the above
		std::cout << "This mode is not supported! Exiting...\n";
		std::exit(1);
		break;
	}
	return params;
}

double* TestData::initRandom(const unsigned int size)
{
	srand((unsigned int)time(0));
	double* tmp = new double[size];
	for (unsigned int i = 0; i < size; ++i)
	{
		tmp[i] = rand() / float(RAND_MAX);
	}
	return tmp;
}

TestData::TestData()
	: params({0,0,0,'a'}), data(nullptr), size(0)
{
	//std::cout << "Called TestData::TestData default constructor.\n";
}

TestData::TestData(int argc, char** argv)
	: params(getParams(argc, argv)),
	data(initRandom(params.arrayLength)),
	size(params.arrayLength)
{
	//std::cout << "Called TestData::TestData constructor with size "
	//		  << params.arrayLength << ".\n";
}

TestData::TestData(const TestData& other)
	: params(other.params), data(other.data), size(other.size)
{
	//std::cout << "Called TestData::~TestData copy constructor.\n";
}

TestData::~TestData()
{
	//std::cout << "Called TestData::~TestData destructor.\n";
	delete[] data;
}
