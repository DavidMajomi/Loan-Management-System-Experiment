#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "loan.h"


// Use g++ -fPIC -shared -o loanManagementLibraryForServer.dll loanManagementLibraryForServer.cpp sqlite3.o
// Upcoming Task: Add functionality for year on year inflation rate.
using namespace std;


struct UserData
{
    const char* userName;
    int creditScore;
    double monthlyIncomeDecimal;
    double financialReservesDecimal;
    double debtToIncomeRatioDecimal;
    double loanAmonutRequestedDeciaml;
    int durationInMonthsInteger;
};


void addIndividualizedLoanDataFromPythonServer(UserData tempUserData,  vector <Loan>& loanAccountsToAdd);


/*
    * All functions within this extern are potentially non thread safe, but since they are mostly used from the dev menu, they wont run 
    *        into thread related issues for now, however, potential fixes using mutex would be coming soon
    * 
    */
extern "C" {
    void changeBaseRate(double primeRate);

    bool addIndividualizedDataToDb(UserData tempUserDataFromPython);
    

    bool readAndStoreGeneratedDataInDb(unsigned short int devMenuResponse);


    bool readAndStoreGeneratedDataForAnalysis(unsigned short int devMenuResponse);


    bool readAllDatabaseDataForAnalysis();


    double getSpread();


    double getThisMonthsPrimeRate();


    bool testAccess();

}
