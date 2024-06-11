#include <iostream>
#include <time.h>       /* time_t, time, ctime */
#include <string>

using namespace std;

int main ()
{
  string todaysDate;

  time_t rawtime;

  time (&rawtime);

  todaysDate = ctime (&rawtime);

  cout << todaysDate;
  // printf("The current local time is: %s", todaysDate);

  return 0;
}