#include "Logger.h"

Logger display;

int main()
{
    bool test = false;

    display.switchScreenDisplay();
    display.output("This is the first log statement");
    display.switchScreenDisplay();
    display.output("This statemnt should not be visible.");
    display.switchScreenDisplay();
    display.outputWithMoreDetails(__FUNCTION__, "test", "bool",to_string(__LINE__), to_string(test), "No comments");

    display << "This an operator overloading test";
    // display << "This an operator overloading test";

    return 0;
}