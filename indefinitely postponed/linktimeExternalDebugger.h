#pragma once
    
// #include <windows.h>
#include <string>

using namespace std;

// system("make externDebugger.dll");

// namespace cppExternalDebugger
// {
// }

namespace cppExternalDebugger
{
    extern "C" inline void log(string message);
    extern "C" inline  void logToCLI(string message);
    extern "C" inline void logWithDetails(string message, string functionName, int lineNumber);

}
