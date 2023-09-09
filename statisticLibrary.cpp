#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

double getMedian(vector<double> dataSet);
double getMean(vector<double> dataSet);


int main()
{
    double median, mean;
    vector<double> values;

    values.push_back(10);
    values.push_back(20);
    values.push_back(30);

    cout << " THis is main" << endl;

    median = getMedian(values);
    mean = getMean(values);
    cout << mean;


    return 0;
}


double getMedian(vector<double> dataSet)
{
    int numElementsInDataSet = dataSet.size();
    double median;

    sort(dataSet.begin(), dataSet.end());


    if (numElementsInDataSet % 2 == 0)
    {
        median = (dataSet[(numElementsInDataSet / 2) - 1] + dataSet[((numElementsInDataSet / 2))]) / 2;
    }
    else
    {
        median = dataSet[((numElementsInDataSet + 1) / 2) - 1];
    }


    return median;
}


double getMean(vector<double> dataSet)
{
    // sum of elements / num of elements
    int sumElements;
    int numElementsInDataSet = dataSet.size();
    double mean;

    sort(dataSet.begin(), dataSet.end());

    for (int count = 0; count < numElementsInDataSet; count++)
    {
        sumElements += dataSet[count];
    }

    mean = sumElements / numElementsInDataSet;

    return mean;
}
