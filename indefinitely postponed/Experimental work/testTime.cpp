#include <time.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

int main()
{
    cout << "start counting................." << endl;
    // systemwait();

    clock_t time;

    time = clock();

    for(int count = 0; count < 100000; count++)
    {
        // cout << " Test " << endl;
    }
    time = clock() - time;

    int timeInt = int(time);

    double timeInSeconds = double(time) / 1000;

    cout << "time taken = " <<  timeInt << " millisecond(s), which is equal to " << timeInSeconds << " seconds" << endl;


    return 0;   
}