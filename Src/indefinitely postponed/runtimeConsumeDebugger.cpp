#include <windows.h>
#include <filesystem>
#include "runtimeExternalDebugger.h"

using namespace std;
namespace fs = std::filesystem;

// namespace std::filesystem = fs;

string CURRENT_FULL_PATH = fs::current_path().string();
string DLLPATHSTR = CURRENT_FULL_PATH + "\\externDebugger.dll";
const char* DLLPATH = DLLPATHSTR.c_str();

int main()
{
    // system("make externDebugger.dll");
    compileDllFromCppFile();

    HINSTANCE instanceOfDebbugger = LoadLibrary((DLLPATH));

    if(!instanceOfDebbugger)
    {
        exit(1);
    }
    else
    {
        cppExternalDebugger::initializeExternalFunctions(instanceOfDebbugger);
        cppExternalDebugger::log("In the building");
        cppExternalDebugger::logWithDetails("The best of us", __FUNCTION__, __LINE__);
        
        system("pause");

        FreeLibrary(instanceOfDebbugger);

    }

    return 0;

}