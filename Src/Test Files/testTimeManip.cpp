#include <cassert>
#include <iostream>
#include <ctime>
#include "../../Header Files/timeManip.h"

using namespace std;
using namespace timeManip;

int main() {

    // Test getLocalTIme
    tm * localTime1 = getLocalTIme();
    assert(localTime1 != nullptr);  
    cout << "getLocalTIme passed." << endl;


    // Test getLocalTimeStruct
    time_t localTimeStruct = getLocalTimeStruct();
    assert(localTimeStruct != 0); 
    cout << "getLocalTimeStruct passed." << endl;


    // Test getLocalTimeStr
    string localTimeStr = getLocalTimeStr();
    assert(!localTimeStr.empty());
    cout << "getLocalTimeStr passed." << endl;


    // Test getDateNDaysFromDate and getDateNDaysFromDateStr
    time_t today = time(0);
    time_t futureDate = getDateNDaysFromDate(today, 5);
    assert(difftime(futureDate, today) >= (5 * 24 * 60 * 60) - 60);  
    cout << "getDateNDaysFromDate passed." << endl;

    string futureDateStr = getDateNDaysFromDateStr(today, 5);
    assert(!futureDateStr.empty());
    cout << "getDateNDaysFromDateStr passed." << endl;


    // Test getDateNMonthsFromDate and getDateNMonthsFromDateStr
    tm futureMonthStruct = *localTime1;
    time_t futureMonth = getDateNMonthsFromDate(&futureMonthStruct, 2);
    assert(futureMonth > today);  
    cout << "getDateNMonthsFromDate passed." << endl;

    string futureMonthStr = getDateNMonthsFromDateStr(&futureMonthStruct, 2);
    assert(!futureMonthStr.empty());
    cout << "getDateNMonthsFromDateStr passed." << endl;


    // Test convertMonthToInt
    assert(convertMonthToInt("Jan") == 1);
    assert(convertMonthToInt("Dec") == 12);
    cout << "convertMonthToInt passed." << endl;

    // Test convSecsToMins, convSecsToHours, convSecsToDays, convSecsToWeeks, and convSecsToMonths
    assert(convSecsToMins(120) == 2);
    assert(convSecsToHours(3600) == 1);
    assert(convSecsToDays(86400) == 1);
    assert(convSecsToWeeks(604800) == 1);
    assert(convSecsToMonths(2592000) == 1); 
    cout << "Time conversion functions passed." << endl;

    // Test convertDateStrToTmStruct
    string testDate = "Mon Oct 25 12:34:56 2021";
    tm dateStruct = convertDateStrToTmStruct(testDate);
    assert(dateStruct.tm_year == 2021 - 1900);
    assert(dateStruct.tm_mon == 9);  
    assert(dateStruct.tm_mday == 25);
    assert(dateStruct.tm_hour == 12);
    assert(dateStruct.tm_min == 34);
    assert(dateStruct.tm_sec == 56);
    cout << "convertDateStrToTmStruct passed." << endl;

    // Test createDateFromString
    time_t createdDate = createDateFromString("Mon Oct 25 12:34:56 2021");
    tm * createdDateTm = localtime(&createdDate);
    assert(createdDateTm->tm_year == 2021 - 1900);
    assert(createdDateTm->tm_mon == 9);
    assert(createdDateTm->tm_mday == 25);
    cout << "createDateFromString passed." << endl;

    // Test createDateFromStringTimeIrrelevant
    time_t createdDateNoTime = createDateFromStringTimeIrrelevant("Mon Oct 25 12:34:56 2021");
    tm * createdDateNoTimeTm = localtime(&createdDateNoTime);
    assert(createdDateNoTimeTm->tm_year == 2021 - 1900);
    assert(createdDateNoTimeTm->tm_mon == 9);
    assert(createdDateNoTimeTm->tm_mday == 25);
    assert(createdDateNoTimeTm->tm_hour == 0);
    assert(createdDateNoTimeTm->tm_min == 0);
    assert(createdDateNoTimeTm->tm_sec == 0);
    cout << "createDateFromStringTimeIrrelevant passed." << endl;

    cout << "All tests passed successfully." << endl;
    return 0;
}
