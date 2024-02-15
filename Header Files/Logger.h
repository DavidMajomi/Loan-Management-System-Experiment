#pragma once

#include <iostream>
#include <string>

using namespace std;

class Logger
{
private:
    bool startScreenDisplay = false;
public:
    Logger()
    {

    }
    void output(string line);
    void operator << (string line);

    void outputWithMoreDetails(string function, string variableName, string variableType,string lineNumber, string variableValue, string comments);

    void switchScreenDisplay(){
        startScreenDisplay = !(startScreenDisplay);
    }
};


void Logger::output(string line)
{
    if(startScreenDisplay)
    {
        cout << line << endl << endl;
    }
}

void Logger::outputWithMoreDetails(string function, string variableName, string variableType,string lineNumber, string variableValue, string comments)
{
    if(startScreenDisplay)
    {
        cout << "Function Name: " << function << endl;
        cout << "Line Number: " << lineNumber << endl;
        cout << "Variable Name: " << variableName << endl;
        cout << "Variable type: " << variableType << endl;
        cout << "Variable Value: " << variableValue << endl;
        cout << "Comments: " << comments << endl;
        cout << endl;
    }
}


void Logger::operator << (string line)
{
    if(startScreenDisplay)
    {
        cout << line << endl << endl;
    }
}
