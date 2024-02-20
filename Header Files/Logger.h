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
    Logger& operator << (T line);

    template <typename T, typename...  Args>
    void display(T value, Args... args);

    void display();

    void endline();
    
    template <typename T>
    void outputWithMoreDetails(string function, T variable, string variableName, string lineNumber, string comments);

    void switchScreenDisplay(){
        startScreenDisplay = !(startScreenDisplay);
    }
    void startLogging(){
        startScreenDisplay = true;
    }
    void stopLogging(){
        startScreenDisplay = false;
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
Logger& Logger::operator << (T line)
{
    
    if(startScreenDisplay)
    {
        cout << line;
    }

    return *this;
}


void Logger::display()
{
    cout << endl;
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

void endline()
{
    cout << endl;
}
