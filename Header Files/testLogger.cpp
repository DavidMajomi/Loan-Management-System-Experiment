#include "Logger.h"

using std::to_string;

Logger display;

int main()
{
    bool test = false;

    display.switchScreenDisplay();
    display.output("This is the first log statement");
    display.switchScreenDisplay();
    display.output("This statemnt should not be visible.");
    display.switchScreenDisplay();
    display.outputWithMoreDetails(__FUNCTION__, test, "test", to_string(__LINE__), "No comments");

    display << "This an operator overloading test";
    display << (1234);
    display.display("here we are in the zone", "testing the mic", 1234, "\nThe logger is working");

    return 0;
}