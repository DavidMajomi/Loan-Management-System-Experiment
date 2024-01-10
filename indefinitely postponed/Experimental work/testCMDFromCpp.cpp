#include <iostream>
#include <string>
using namespace std;

int main() {
    int test;
    test = system("netsh wlan show profile");
    cout << " CHeck it out " << endl;
    cout << test << endl;
    cout << " Another one " << endl;
    
    return 0;
}