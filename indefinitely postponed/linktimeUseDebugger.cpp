// #include <string>
#include "linktimeExternalDebugger.h"
// #include <iostream>
using namespace std;

int main()
{
    // cout << " Test " << endl;
    cppExternalDebugger::logToCLI(" Hello World form log");
    cppExternalDebugger::logWithDetails(" Hello World", __PRETTY_FUNCTION__, __LINE__);
    cppExternalDebugger::logToCLI(" Hello test this");
    cppExternalDebugger::log(" Why is log not working");


    return 0;
}