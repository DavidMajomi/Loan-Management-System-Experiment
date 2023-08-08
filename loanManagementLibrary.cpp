#include "C:\\Users\\David\\Documents\\loanManagementSystem\\sqlite3.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "loanManagementSystem.h"

// g++ -fPIC -shared -o loanManagementLibrary.dll loanManagementLibrary.cpp sqlite3.o

using namespace std;


void  fakeMain(unsigned short int initialResponse, unsigned short int devMenuResponse)
{
    int menuResponse,  devMenuResponse;
    ifstream inputfile;
    ofstream outputCsvFile;
    vector<Loan> loanAccounts, loanAccountsToAdd;

    // initialResponse = initialResponseForMenu ();

    if (initialResponse == 0)
    {
        menuResponse = menu();

        if (menuResponse == 1)
        {
            cout << endl;
            cin.ignore();
            addIndividualizedLoanDataFromPython (loanAccountsToAdd);
            createDatabaseToAddUserLoanData (loanAccountsToAdd);
        }
        else if (menuResponse == 2)
        {
            cout << " This is the line for menu response 2. " << endl;
            cout << " What is the loanId: " << endl;
        }
    }
    else if (initialResponse == 1)   // This is dev option
    {
        // devMenuResponse = devMenu ();

        if (devMenuResponse == 1) // Generate data, must be noted this can only be done using python.
        {
            cout << " This is where generate new data would be. " << endl;
            readGeneratedData(inputfile, loanAccounts, devMenuResponse);
            storeGeneratedDataInDatabase(loanAccounts);
        }
        else if (devMenuResponse == 2) // read and output data for analysis in csv format
        {
            cout << " This is perform data analysis from csv file. " << endl;
            readGeneratedData(inputfile, loanAccounts, devMenuResponse);
            outputFile (outputCsvFile, loanAccounts);
        }
        else if (devMenuResponse == 3) // Retrieve data from sqlite database for analysis
        {
            cout << " This is retrieve and analyze database values. " << endl;
        }

    }

    inputfile.close();
    outputCsvFile.close();

}


extern "C"{

    int setInitialMenuResponse()
    {
        unsigned short int initialResponse;

        initialResponse = initialResponseForMenu();

        return initialResponse;
    }


    unsigned short int showDevMenuFromCpp()
    {
        unsigned short int devMenuResponse;

        devMenuResponse = devMenu();

        return devMenuResponse;
    }


    void getValuesFromPython(unsigned short int initialResponse, unsigned short int devMenuResponse)
    {
        fakeMain(initialResponse, devMenuResponse);
    }

}

