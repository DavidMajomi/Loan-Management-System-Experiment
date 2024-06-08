#pragma once

#include <string>
#include <chrono>


namespace timeManip
{

    using namespace std;

    tm * getLocalTIme()
    {
        time_t now = time(0);

        tm * localTime = localtime(&now);

        return localTime;
    }

    time_t getTimeDiff(time_t A, time_t B)
    {
        // return A - B;
    }

    time_t getDateNDaysFromDate(time_t rawtime, int ndays)
    {
        time_t oneday = 24 * 60 * 60;
        time_t ndaysObj = rawtime + (oneday * ndays);

        return ndaysObj;
    }

    string getDateNDaysFromDateStr(time_t rawtime, int ndays)
    {
        time_t ndaysObj = getDateNDaysFromDate(rawtime, ndays);

        return ctime(&ndaysObj);
    }

    time_t getDateNMonthsFromDate(tm * time, int nMonths)
    {
        time -> tm_mon = time -> tm_mon + nMonths;
        time_t timeObj = mktime(time);

        return timeObj;
    }

    string getDateNMonthsFromDateStr(tm * time, int nMonths)
    {
        // time -> tm_mon = time -> tm_mon + nMonths;
        // time_t timeObj = mktime(time);
        time_t timeObj = getDateNMonthsFromDate(time, nMonths);

        return ctime(&timeObj);
    }

    inline string getDateAsStr(time_t * time)
    {
        return ctime(time);
    }

}