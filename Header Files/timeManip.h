#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <chrono>
#include <vector>
#include <map>


namespace timeManip
{

    using namespace std;

    // enum 

    tm * getLocalTIme()
    {
        time_t now = time(0);

        tm * localTime = localtime(&now);

        return localTime;
    }


    time_t getLocalTimeStruct()
    {
        time_t now;

        tm * localTime;
        time(&now);

        return now;
    }


    string getLocalTimeStr()
    {
        time_t now;

        tm * localTime;
        time(&now);

        return ctime(&now);
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


    int convertMonthToInt(string month)
    {
        map <string, int> table = {{"Jan", 0}, {"Feb", 1}, {"Mar", 2}, {"Apr", 3}, {"May", 4}, {"Jun", 5}, {"Jul", 6}, {"Aug", 7}, {"Sep", 8}, {"Oct", 9}, {"Nov", 10}, {"Dec", 11}};


        return table[month] + 1;
    }


    inline double convSecsToMins(double vals)
    {
        return vals / 60;
    }


    inline double convSecsToHours(double vals)
    {
        return convSecsToMins(vals) / 60;
    }


    inline double convSecsToDays(double vals)
    {
        return convSecsToHours(vals) / 24;
    }


    inline double convSecsToWeeks(double val)
    {
        return convSecsToDays(val) / 7;
    }


    inline double convSecsToMonths(double val)
    {
        return val / 2592000;
    }


    tm convertDateStrToTmStruct(string timeValue)
    {
        const char * val = timeValue.c_str();

        struct tm timeStruct;
        string timeTokens;
        string weekDay, month, dayOfMonth, time, year;

        int timeHours = 0, timeMinutes = 0, timeSeconds = 0;

        stringstream tokens(val);
        vector <int> timeNums;
        string word;

        tokens >> weekDay >> month >> dayOfMonth >> time >> year;

        stringstream timeVals(time);

        while(getline(timeVals, timeTokens, ':'))
        {
            timeNums.push_back(stoi(timeTokens));
        }

        // cout << "Time nums: ";
        // cout << timeNums[0] << endl;

        timeHours = timeNums[0];
        timeMinutes = timeNums[1];
        timeSeconds = timeNums[2];

        // cout << "Time in hours: " << timeHours << endl;

        // timeStruct.tm_wday = 0;
        timeStruct.tm_mon = convertMonthToInt(month) - 1;
        timeStruct.tm_mday = stoi(dayOfMonth);
        timeStruct.tm_year = stoi(year) - 1900;
        timeStruct.tm_hour = timeHours;
        timeStruct.tm_min = timeMinutes;
        timeStruct.tm_sec = timeSeconds;
        timeStruct.tm_isdst = -1;

        return timeStruct;
    }


    time_t createDateFromString(string timeValue)
    {
        const char * val = timeValue.c_str();

        time_t timeT;

        struct tm timeStruct = convertDateStrToTmStruct(timeValue);

        timeT = mktime(&timeStruct);
        // cout << ctime(&timeT);

        return timeT;
    }


    time_t createDateFromStringTimeIrrelevant(string timeValue)
    {
        const char * val = timeValue.c_str();

        time_t timeT;
        struct tm timeStruct;
        string weekDay, month, dayOfMonth, time, year;

        stringstream tokens(val);

        tokens >> weekDay >> month >> dayOfMonth >> time >> year;

        timeStruct.tm_mon = convertMonthToInt(month) - 1;
        timeStruct.tm_mday = stoi(dayOfMonth);
        timeStruct.tm_year = stoi(year) - 1900;
        timeStruct.tm_hour = 0;
        timeStruct.tm_min = 0;
        timeStruct.tm_sec = 0;
        timeStruct.tm_isdst = -1;


        // cout << asctime(&timeStruct);

        timeT = mktime(&timeStruct);
        // cout << ctime(&timeT);

        return timeT;
    }

}