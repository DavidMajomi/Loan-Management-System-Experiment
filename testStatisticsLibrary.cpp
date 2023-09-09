#include <vector>
#include <iostream>
#include <algorithm>
#include "statisticsLibrary.h"

using namespace std;

int main()
{
    double median, mean, standardDeviation;
    vector<double> values;
    vector<double> mode;

    values.push_back(10);
    values.push_back(20);
    values.push_back(20);
    values.push_back(30);


    cout << " THis is main" << endl;

    mean = getMean(values);
    mode = getMode(values);
    median = getMedian(values);
    standardDeviation = getStandardDeviation(values);
    cout << " This is mean: " << mean << endl;
    // cout << " This is mode: " << mode << endl;
    for (int count = 0; count < mode.size(); count++)
    {
        cout << " Mode " << (count + 1) << ": " << mode[count] << endl;
    }
    cout << " This is median: " << median << endl;
    cout << " This is standardDeviation: " << standardDeviation << endl;

    return 0;
}