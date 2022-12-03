#include "TestParam.h"

TestParam::TestParam() // default constructor
	: arrayLength(0),
	numReps(0),
	unrollFactor(0),
	test('a')
{
	//std::cout << "Called TestParam::TestParam constructor.\n";
}

TestParam::TestParam(int argc, char** argv)
{
	switch (argc)
	{
	case 1: // no arguments, run all tests with default values
		arrayLength = 1024;
		numReps = 1000;
		unrollFactor = 4;
		test = 'a';
		break;
	case 4: // all tests with user defined values
		arrayLength = atoi(argv[1]);
		numReps = atoi(argv[2]);
		unrollFactor = atoi(argv[3]);
		test = 'a';
		break;
	case 5: // specific test with user defined values
		arrayLength = atoi(argv[1]);
		numReps = atoi(argv[2]);
		unrollFactor = atoi(argv[3]);
		test = *argv[4];
		break;
	default: // exit with message if none of the above
		std::cout << "This mode is not supported! Exiting...\n";
		std::exit(1);
		break;
	}
}

TestParam::TestParam(const TestParam& other) // copy constructor
	: arrayLength(other.arrayLength),
	numReps(other.numReps),
	unrollFactor(other.unrollFactor),
	test(other.test)
{
	//std::cout << "Called TestParam::TestParam copy constructor.\n";
}

TestParam::~TestParam() // destructor
{
	//std::cout << "Called TestParam::TestParam destructor.\n";
}
