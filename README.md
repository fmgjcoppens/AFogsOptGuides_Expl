To add an instance of 'double myTest(const TestData&);' to the testing
framework, do

	1. Add an empty 'myTest.h' file to 'Addition and Substraction\include\Tests'
	   with minimal contents

		#pragma once
		#include "TestData.h"
		double myTest(const TestData& testdata);

	2. Add an empty 'myTest.cpp' file to 'Addition and Substraction\src\Tests'
	   with minimal contents

		#include "myTest.h"
		double myTest(const TestData& testdata)
		{
			// your test code
		}

	3. Add 'myTest' to the unordered_map 'Tests' in 
	   'Addition and Substraction\src\Main.cpp:33'

		Tests['m'] = { "my test", &myTest };

	   Make sure the index 'm' is unique.
