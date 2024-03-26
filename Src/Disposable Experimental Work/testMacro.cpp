#include <iostream>

using namespace std;

int main()
{

    string function = __FUNCTION__;
    cout << " This is test func: " << function << endl;
    cout << " This is test Line: " << __LINE__ << endl;

    // cout << " This is func return type: " << decltype(function) << endl;

}