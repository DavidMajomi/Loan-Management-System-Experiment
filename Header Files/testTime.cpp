#include <iostream>
#include <time.h>
#include "timeManip.h"

using namespace std;

int main()
{
    // string value = "Sat Jun 15 16:46:06 2024\n";
    string value = "Mon Jan 18 15:50:49 2027\n";
    time_t now = time(0);
    time_t rawtime;
    time_t bingeTime;
    time_t oneday = 24 * 60 * 60;
    time(&rawtime);
    time(&bingeTime);
    // int numSecondsRaw = rawtime;
    // int numSecondsRawTwo = bingeTime;

    // cout << numSecondsRaw - numSecondsRawTwo << endl;

    // time_t bogTime = now - rawtime;
    // cout << timeManip::getDateAsStr(&bogTime);

    // cout << " Num seconds since unix time thingy = " << now << endl;

    tm * localTime = localtime(&now);
    time_t locTime = mktime(localTime);
    
    // localTime -> tm_mon = localTime -> tm_mon + 13;
    cout << ctime(&locTime);
    cout << timeManip::getDateNMonthsFromDateStr(localTime, 13);
    // cout << localTime -> tm_mon + 13 << endl;
    
    cout << "Now: " << timeManip::getDateAsStr(&now);
    cout << "12 months from now: " << timeManip::getDateNDaysFromDateStr(now, 365);
    
    // cout << timeManip::getDateAsStr(&oneday);

    time_t fake = timeManip::createDateFromString(value);
    cout << "_________" << endl;
    cout << value;
    cout << ctime(&fake);
    // cout 
    time_t check = timeManip::createDateFromStringTimeIrrelevant(value);
    cout << ctime(&check);
    cout << timeManip::getDateAsStr(&check) << endl;

    cout << timeManip::convSecsToDays(86400.00) << endl;
    cout << timeManip::convSecsToHours(86400.0) << endl;
    cout << timeManip::convSecsToHours(5000.00) << endl;
    cout << timeManip::convSecsToMonths(2629746) << endl;

    time_t nowAgain = timeManip::getLocalTimeStruct();

    cout << ctime(&nowAgain);
    cout << timeManip::getLocalTimeStr();

    

    cout << "Shoki" << endl;

    return 0;
}

















    // cout << "Seconds after the minute: " << localTime -> tm_sec << endl;
    // cout << "Minute after hour: " << localTime -> tm_min << endl;
    // cout << "Hours since mid night 24h format: " << localTime -> tm_hour << endl;
    // cout << "Day of the month: " << localTime -> tm_mday << endl;
    // cout << "Month since January: " << 1 + localTime -> tm_mon << endl;
    // cout << "Days since sunday: " << localTime -> tm_wday << endl;
    // cout << "Day of year from jan 1st: " << localTime -> tm_yday << endl;
    // cout << "Year since 1900: " << localTime -> tm_year << endl;
    // cout << endl;
