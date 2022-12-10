# Exploration of Agner Fog's optimisation guides

Various functions to test loop unrolling , pipelining and assebly optimisations.

### How to use with Visual Studio
1. From the repository root, run
 ```
 .\vendor\premake\premake5.exe vs<version>
 ```
 2. Open the solution file `Agner Fog's Optimisation Guide.sln` with Visual Studio
 3. Select `Build -> Build Solution` or press `F7`
 4. Run
 ```
 bin/Release-windows-x86_64/Addition and Substraction/Addition and Substraction.exe <arrays size> <# of repetitions> <unroll factor> <test>
 ```
 
### How to use with CMake
*(WIP: not working yet with Assembly)*
1. From the repository root, run
 ```
 .\vendor\premake\premake5.exe cmake
 ```
 2. Open the solution file `Agner Fog's Optimisation Guide.sln` with Visual Studio
 3. Select `Build -> Build Solution` or press `F7`
 4. Run
 ```
 bin/Release-windows-x86_64/Addition and Substraction/Addition and Substraction.exe <arrays size> <# of repetitions> <unroll factor> <test>
 ```
 
 ### How to add tests
 [See 'Adding tests'](Adding_tests.md)
  
