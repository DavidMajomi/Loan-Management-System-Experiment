#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>

using namespace std;

template <typename T>
void test(T shaking)
{
    string value;
    int dt = 66;
    value = shaking;

    cout << shaking << endl;
    // cout << value + dt;
}

int main()
{
    string valueString = " teyeu";
    string typeValue = (typeid(valueString).name());

    const char * addedValue = " added";
    char * charPointer = " added char pointer";
    string completedValue = valueString + addedValue + charPointer;

    // string convert = to_string(value);
    if (typeid(valueString).name() == typeid(string).name())
    {
        cout << " Hello";
    }

    cout <<  completedValue;
    cout << endl << endl;

    cout << (valueString);
    test("bamij");
    cout << typeid(typeid(string).name()).name();

    if(typeValue == typeid(string).name())
    {
        cout << " Value Match" << endl;
    }
    
    return 0;
}