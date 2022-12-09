#pragma once

#include <intrin.h>

#include "TestData.h"

#pragma intrinsic(__rdtsc)
typedef unsigned __int64 cc;

// typedef of function pointer to a test function
typedef double (*testFunction)(const TestData&);

// typedef of a test containing a name and a 
// function pointer to the test function
typedef struct Test {
	std::string testName;
	testFunction testFunction;
} Test;
