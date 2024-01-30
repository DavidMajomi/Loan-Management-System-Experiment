#include <time.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

int main()
{
    clock_t time;

    time = clock();

    for(int count = 0; count < 1000000; count++)
    {

    }
    time = clock() - time;

    cout << "time taken = " << time << endl;


    return 0;   
}