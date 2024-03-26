
// #define BUILD_DLL

// #ifdef BUILD_DLL
// #define EXPORT __declspec(dllexport)
// #else
// #define EXPORT __declspec(dllimport)
// #endif

#include <iostream>
#include <windows.h>
// #include <


using namespace std;

    
extern "C" bool __declspec(dllexport) __stdcall testAccess()
{
   cout << " Accessed from dll successful. " << endl;
   return true;
}


// void WINAPI DllMain( HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
// {
//    cout << " In the dll" << endl;
// }



// extern "C" int __declspec(dllexport) __stdcall funci() {
// extern "C" __declspec(dllexport) __stdcall int bro(int forget) {
//    // ...

//    cout << " Accessed From outside. " << endl;
//    return 256789;
// }



// extern "C" int __declspec(dllexport) __stdcall funci() {
// extern int __declspec(dllexport) __stdcall bro(int forget) {
extern "C" int  __declspec(dllexport) __stdcall bro(int forget) {
   // ...

   cout << " Accessed From outside. " << endl;
   return 256789;
}