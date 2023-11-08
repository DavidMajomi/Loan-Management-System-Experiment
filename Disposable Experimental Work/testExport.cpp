#include <iostream>



using namespace std;

extern "C" int bro(int);

int main()
{
    cout << " Bro returns " << bro(5) << endl;

    return 0;

}