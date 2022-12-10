# Exploration of Agner Fog's optimisation guides

### Adding an instance of `double myTest(const TestData&);` (C/C++)
1. Add a new header file `myTest.h` to `Addition and Substraction/include/Tests` with minimal contents
	```
	#pragma once
	#include "TestData.h"
	
	double myTest(const TestData& testdata);
	```
2. Add a new source file `myTest.cpp` to `Addition and Substraction/src/Tests` with minimal contents
	```
	#include "myTest.h"
	
	double myTest(const TestData& testdata)
	{
		// test code
	}
	```
3. Add `myTest` to the unordered_map `Tests` at `Addition and Substraction/src/Main.cpp:33`
	```
	Tests['m'] = { "my test", &myTest };
	```

### Adding an instance of `double myTest(const TestData&);` (Assembly)
1. Add a new header file `myTest.h` to `Addition and Substraction/include/Tests` with minimal contents
	```
	#pragma once
	#include "TestData.h"

	extern "C" double __myTest(double*, unsigned int);
	double myTest(const TestData& testdata);
	```
2. Add a new source file `myTest.cpp` to `Addition and Substraction/src/Tests` with minimal contents
	```
	#include "myTest.h"

	double myTest(const TestData& testdata)
	{
		return __myTest(testdata.data, testdata.size);
	}
	```
3. Add new assembly source file `__myTest.asm` to `Addition and Substraction/src/Tests` with minimal contents
	```
	.code
	__myTest proc
		push rbx
		
		; ASM code here
		
		pop rbx
		ret
	__myTest endp
	end
	```
3. Add `myTest` to the unordered_map `Tests` at `Addition and Substraction/src/Main.cpp:33`
	```
	Tests['m'] = { "my test", &myTest };
	```

***Make sure the index `m` is unique otherwise it overwrites the previous instance of `m`!***
