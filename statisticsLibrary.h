#ifndef STATISTICSLIBRARY_H_INCLUDED
#define STATISTICSLIBRARY_H_INCLUDED

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

double getMedian(vector<double> dataSet);

double getMean(vector<double> dataSet);

vector<double> getMode(vector<double> dataSet);

double getStandardDeviation(vector<double> dataSet);


#endif // STATISTICSLIBRARY_H_INCLUDED