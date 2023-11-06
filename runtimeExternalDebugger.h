#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <stdio.h>

using std::string;

typedef void(__stdcall *f_funci)(string);
typedef void(__stdcall *accessFunc)(string, string , int);

void compileDllFromCppFile()
{
    system("g++ -fpic -shared -o externDebugger.dll externalDebugger.cpp");
}



// HINSTANCE signal = LoadLibrary(("C:\\Users\\David\\Documents\\GitHub\\Loan-Management-System-Experiment\\experimentalDLL.dll"));
namespace cppExternalDebugger
{

    // void(__stdcall *value)();
    
    // void __declspec(dllexport) __stdcall log(string message)
    f_funci log;


    // void __declspec(dllexport) __stdcall logWithDetails(string message, string function, int lineNumber)
    accessFunc logWithDetails;


    void initializeExternalFunctions(HINSTANCE signal)
    {
        log = (f_funci)GetProcAddress(signal,("log"));
        logWithDetails = (accessFunc)GetProcAddress(signal,("logWithDetails"));
        
    }


}