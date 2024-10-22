#include <iostream>
#include <time.h>
#include <assert.h>
#include "timeManip.h"

using namespace std;

int main()
{
    // string value = "Sat Jun 15 16:46:06 2024\n";
    string value = "Mon Jan 18 15:50:49 2027";
    time_t check = timeManip::createDateFromStringTimeIrrelevant(value);
    string check_str = ctime(&check);

    time_t now = time(0);

    // cout << "Num seconds since unix time thingy = " << now << endl << endl;

    tm * localTime = localtime(&now);
    time_t locTime = mktime(localTime);
    string currLocTime = ctime(&locTime);
    
    cout << "Current Time: " << currLocTime;
    // string twelve_months_from_now 
    cout << "String Date 12 months from now: " << timeManip::getDateNMonthsFromDateStr(localTime, 13);
    
    cout << "Current Date and Time using Library: " << timeManip::getDateAsStr(&now);
    assert(currLocTime == timeManip::getDateAsStr(&now));


    cout << "12 months from now: " << timeManip::getDateNDaysFromDateStr(now, 365);
    
    time_t fake = timeManip::createDateFromString(value);
    cout << "__________________________" << endl;
    cout << value;
    cout << ctime(&fake);

    cout << "Checking conversion of " << value << " to Mon Jan 18 00:00:00 2027\n" << endl;
    assert(check_str == "Mon Jan 18 00:00:00 2027\n");

    cout << ctime(&check);
    cout << "__________________________" << endl;
    cout << endl;
    // cout 
    cout << timeManip::getDateAsStr(&check) << endl;

    cout << timeManip::convSecsToDays(86400.00) << endl;
    cout << timeManip::convSecsToHours(86400.0) << endl;
    cout << timeManip::convSecsToHours(5000.00) << endl;
    cout << timeManip::convSecsToMonths(2629746) << endl;

    time_t nowAgain = timeManip::getLocalTimeStruct();

    cout << "Local Time Struct: " << ctime(&nowAgain);
    
    string currTime = timeManip::getLocalTimeStr();
    
    cout << currTime << endl;

    tm currTimeTm = timeManip::convertDateStrToTmStruct(currTime);

    // cout << asctime(&currTimeTm);
    cout << "January is the " << timeManip::convertMonthToInt("Jan") << " month of the year" << endl;

    return 0;
}
