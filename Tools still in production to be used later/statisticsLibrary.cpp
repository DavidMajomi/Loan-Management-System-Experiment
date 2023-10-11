#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include "statisticsLibrary.h"

using namespace std;


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
    int sumElements = 0;
    int numElementsInDataSet = dataSet.size();
    double mean;

    for (int count = 0; count < numElementsInDataSet; count++)
    {
        sumElements += dataSet[count];
    }

    mean = sumElements / numElementsInDataSet;

    return mean;
}


vector<double> getMode(vector<double> dataSet)
{
    int numElementsInDataSet = dataSet.size(), maxNumberOfReoccurencesInDataSet = 1, defaultMode = 0, numCurrentValueOccurences = 1;
    vector<double> coNodes;

    sort(dataSet.begin(), dataSet.end());

    for(int count = 0; count < numElementsInDataSet; count++)
    {
        if (dataSet[count] == dataSet[count - 1])
        {
            numCurrentValueOccurences++;

            if (numCurrentValueOccurences > maxNumberOfReoccurencesInDataSet)
            {
                maxNumberOfReoccurencesInDataSet = numCurrentValueOccurences;
                defaultMode = dataSet[count];
                coNodes.clear();
            }
            
            if (numCurrentValueOccurences == maxNumberOfReoccurencesInDataSet)
            {

                coNodes.push_back(dataSet[count]);
            }
            

        }
        else
        {
            numCurrentValueOccurences = 1;
        }
    }

    // cout << " This is default node: " << defaultMode << endl;
    // cout << " This is coNodes size: " << coNodes.size() << endl;

    if (coNodes.size() == 0)
    {
        coNodes.push_back(defaultMode);
    }

    if (maxNumberOfReoccurencesInDataSet == 1)
    {
        coNodes.push_back(0);
    }


    return coNodes;
}


double getStandardDeviation(vector<double> dataSet)
{
    int numElementsInDataSet = dataSet.size();
    double standardDeviation = 0, mean = 0, summationResult = 0;

    mean = getMean(dataSet);

    for(int count = 0; count < numElementsInDataSet; count++)
    {
        summationResult += pow((dataSet[count] - mean), 2);
    }

    standardDeviation = sqrt((summationResult / (numElementsInDataSet - 1)));

    return standardDeviation;
}


// template <typename T>  vector<T> duplicate(vector<T> vectorToDuplicate)
// {
//     vector<T> newVector;

//     for (int count = 0; count < vectorToDuplicate.size(); count++)
//     {
//         newVector.push_back(vectorToDuplicate[count]);
//     }

//     return newVector;

// }