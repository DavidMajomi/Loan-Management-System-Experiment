#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace cppExternalDebugger
{
    extern "C"{
        inline void __declspec(dllexport) __stdcall logToCLI(string message)
        {
            cout << " Message: " << message << endl;
        }



        inline void __declspec(dllexport) __stdcall log(string message)
        {
            cout << " Message: " << message << endl;
        }

        inline  void __declspec(dllexport) __stdcall logWithDetails(string message, string function, int lineNumber)
        {
            cout << " Line: " <<  lineNumber << " Function: " << function << " Message: " << message << endl;

        }

        // template <typename T, typename ... Types>
        // void __declspec(dllexport) __stdcall log(T message, Types ... nextMessage)
        // {
        //     cout << message << endl;
            
        //     log(nextMessage...);

        // }
    }
};