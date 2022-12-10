#include "TestData.h"


TestData::TestData()
	: data(nullptr),
	size(0)
{
	//std::cout << "Called TestData::TestData default constructor.\n";
}

TestData::TestData(const TestParam& params)
	: params(params),
	data(initRandom(params.arrayLength)),
	size(params.arrayLength)
{
	//std::cout << "Called TestData::TestData constructor with size "
	//		  << params.arrayLength << ".\n";
}

TestData::TestData(const TestData& other)
	: params(other.params),
	data(other.data),
	size(other.size)
{
	//std::cout << "Called TestData::~TestData copy constructor.\n";
}

TestData::~TestData()
{
	//std::cout << "Called TestData::~TestData destructor.\n";
	delete[] data;
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