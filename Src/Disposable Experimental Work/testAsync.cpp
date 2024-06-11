#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

using namespace std;


int sumVectorValues(vector <int> values)
{   
    int sumValues = 0;

    for (int count = 0; count < values.size(); count++)
    {
        sumValues += values[count];

    }

    cout << " Thi is sum values in function: " << sumValues << endl;

    return sumValues;
}


int main()
{
    vector <int> values;

    for(int count; count < 100; count++)
    {
        values.push_back(1);


    }

    int halfSize = values.size();

    vector <int> firstHalf = values;

    auto sum1 = async(launch::async, &sumVectorValues, firstHalf);

    cout << " This is a test. " << endl;

    cout << typeid(sum1).name() << endl;


    int sum1Result = sum1.get();

    cout << " This is sum result: " << sum1Result << endl;


}