#include <iostream>
#include<string>
#include <utility>
#include <vector>
#include <algorithm>


using namespace std;

int main()
{
    pair <string, string> valOne;
    pair <string, string> temp;

    vector<pair <string, string>> vec;

    valOne = make_pair("Hello", "world of pairs");


    for (int count = 0; count < 10; count++)
    {
        temp = make_pair("Test one", "test two");
        vec.push_back(temp);
    }
    for (int count = 0; count < 10; count++)
    {
        cout << vec[count].first << endl;
        cout << vec[count].second << endl;
        cout << endl;
    }
    
    cout << valOne.first + " " + valOne.second;


    

    return 0;
}