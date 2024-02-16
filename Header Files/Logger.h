#pragma once

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Logger
{
private:
    bool startScreenDisplay = false;
public:
    Logger()
    {

    }
    void output(string line);

    template <typename T>
    void operator << (T line);

    template <typename T, typename...  Args>
    void display(T value, Args... args);

    void display();
    
    template <typename T>
    void outputWithMoreDetails(string function, T variable, string variableName, string lineNumber, string comments);

    void switchScreenDisplay(){
        startScreenDisplay = !(startScreenDisplay);
    }
    bool getLoggingState() const{
        return startScreenDisplay;
    }
};


void Logger::output(string line)
{
    if(startScreenDisplay)
    {
        cout << line << endl << endl;
    }
}


template <typename T>
void Logger::outputWithMoreDetails(string function, T variable, string variableName, string lineNumber, string comments)
{
    if(startScreenDisplay)
    {
         string todaysDate;

        time_t rawtime;

        time (&rawtime);

        todaysDate = ctime (&rawtime);

        cout << "Date: " << todaysDate;
        cout << "Function Name: " << function << endl;
        cout << "Line Number: " << lineNumber << endl;
        cout << "Variable Name: " << variableName << endl;
        cout << "Variable type: " << typeid(variable).name() << endl;
        cout << "Variable Value: " << variable << endl;
        cout << "Comments: " << comments << endl;
        cout << endl;
    }
}


template <typename T>
void Logger::operator << (T line)
{
    
    if(startScreenDisplay)
    {
        cout << line << endl;
    }   
}


void Logger::display()
{
    if(startScreenDisplay)
    {
        cout << endl;
    }
}


template <typename T, typename...  Args>
void Logger::display(T value, Args... args)
{
    if(startScreenDisplay)
    {
        cout << value << " ";

        Logger::display(args...);    
    }
    
}
