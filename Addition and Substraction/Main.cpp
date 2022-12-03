#include "Main.h"

int main(int argc, char** argv)
{	/*
		test:	(n)aive
				(u)nrolled
				(v)ectorised
				(b)oth vectorised and unrolled
				(a)ll

		Invocation:

			$ test_add  <# of array elements> <# of repetitions> <unroll factor> <test>

		* Perform all tests with user defined values

			$ test_add  <# of elements> <# of repetitions> <unroll factor>

		equivalent to:

			$ test_add  <# of elements> <# of repetitions> <unroll factor> a

		* Perform all tests with sensible default values:

			$ test_add

		equivalent to:

			$ test_add 1024 1000 4 a
	*/
	
	// Hash table containing test names and test function-pointers
	std::unordered_map<char, Test> Tests; 
	Tests['n'] = { "Naive", &sum_Naive };
	Tests['u'] = { "Unrolled", &sum_AF1 };

	// Declare and initialize test parameters and data
	const TestParam Params(argc, argv);
	const TestData Data(Params);

	// Perform all tests or just one
	printHeader(Params);
	switch (Params.test)
	{
		case 'a': // do all tests in Tests
			for (auto& iterator : Tests)
			{
				testFunction test = iterator.second.testFunction;
				TestResult Results = getResults(Data, test);
				writeResults(iterator.second.testName, Results);
			}
			break;

		default: // do just one specific test in Tests
			testFunction test = Tests[Params.test].testFunction;
			TestResult Results = getResults(Data, test);
			writeResults(Tests[Params.test].testName, Results);
			break;
	}
	return 0;
}
