#include "../Header Files/Logger.h"

using std::to_string;

int main()
{
    
    Logger display;

    const char ENDLINE = '\n';
    int value = 8080;
    bool test = false;
    string chucks = "chucks";

    display.switchScreenDisplay();
    display.output("This is the first log statement");
    display.switchScreenDisplay();
    display.output("This statemnt should not be visible.");
    display.switchScreenDisplay();
    display.outputWithMoreDetails(__FUNCTION__, test, "test", to_string(__LINE__), "No comments");

    display << "This an operator overloading test " + chucks + " "  + to_string(value);
    display << "This an operator overloading test " << chucks + " "  + to_string(value);
    display << (1234);
    display.display("here we are in the zone", "testing the mic", 1234, "\nThe logger is working");
    display << "hello " << "world" << ENDLINE << ENDLINE;

    return 0;
}