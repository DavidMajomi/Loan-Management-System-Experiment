#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Header Files/loanManagementSystemForServer.h"

// Use g++ -fPIC -shared -o loanManagementLibraryForServer.dll loanManagementLibraryForServer.cpp sqlite3.o
// Upcoming Task: Add functionality for year on year inflation rate.
using namespace std;

struct UserData
{
    char* userName;
    int creditScore;
    double monthlyIncomeDecimal;
    double financialReservesDecimal;
    double debtToIncomeRatioDecimal;
    double loanAmonutRequestedDeciaml;
    int duration;
};


// double getCurrentFFR()
// {
//     return CURRENT_METRICS.getFederalFundsRate();
// }

void setCurrentMetrics(double primeRate)
{
    CURRENT_METRICS.unlockClassForModification();
    CURRENT_METRICS.setFederalFundsRatePercent(primeRate);
    CURRENT_METRICS.lockModificationOfClass();
}


void addIndividualizedLoanDataFromPythonServer(UserData tempUserData,  vector <Loan>& loanAccountsToAdd)
{
    Loan userAccount(1);

    userAccount.setUserName(tempUserData.userName);
    userAccount.setCreditScore(tempUserData.creditScore);
    userAccount.setMonthlyIncome(tempUserData.monthlyIncomeDecimal);
    userAccount.setFinancialReserves(tempUserData.financialReservesDecimal);
    userAccount.setDebtToIncomeRatio(tempUserData.debtToIncomeRatioDecimal);
    userAccount.setLoanDuration(tempUserData.duration);
    userAccount.setLoanAmount(tempUserData.loanAmonutRequestedDeciaml);
    userAccount.computeCreditData();
    userAccount.setFinalMonthlyInterestRate();

    loanAccountsToAdd.push_back(userAccount);

}


extern "C" {
    void changeBaseRate(double primeRate)
    {
        cout << " This is entered prime rate: " << primeRate << endl;
        setCurrentMetrics(primeRate);

        // cout << " Prime Rate has been Changed to " << getCurrentFFR() << endl;
    }


    bool addIndividualizedDataToDb(UserData tempUserDataFromPython)
    {

        bool fileOpeningError = false;
        vector<Loan> loanAccountsToAdd;

        addIndividualizedLoanDataFromPythonServer (tempUserDataFromPython, loanAccountsToAdd);
        fileOpeningError = createDatabaseToAddUserLoanData (loanAccountsToAdd);

        // cout << " This is federalFundsRate from todays metrics: " << TODAYS_METRICS.getFederalFundsRate() << endl;
        // cout << " This is federalFundsRate from current metrics: " << CURRENT_METRICS.getFederalFundsRate() << endl;
        return fileOpeningError;
    }
    

    bool readAndStoreGeneratedDataInDb(unsigned short int devMenuResponse)
    {
        bool fileOpeningError = false;
        ifstream inputFile;
        vector<Loan> loanAccounts;

        fileOpeningError = readGeneratedData(inputFile, loanAccounts, devMenuResponse);
        fileOpeningError = storeGeneratedDataInDatabase(loanAccounts);

        return fileOpeningError;
    }


    bool readAndStoreGeneratedDataForAnalysis(unsigned short int devMenuResponse)
    {
        ifstream inputFile;
        ofstream outputCsvFile;
        vector<Loan> loanAccounts;
        bool openInputFileError = false, openOutputFileError = true,  fileOpeningError = false;

        openInputFileError = readGeneratedData(inputFile, loanAccounts, devMenuResponse);
        openOutputFileError = outputToFile (outputCsvFile, loanAccounts);

        if ((openInputFileError == true) || (openOutputFileError == true))
        {
            fileOpeningError = true;
        }

        return fileOpeningError;
    }


    bool readAllDatabaseDataForAnalysis()
    {
        bool errorRetrievingData = false;
        ofstream outputCsvFile;

        errorRetrievingData = retrieveAllUserDataFromDatabase(outputCsvFile);

        return errorRetrievingData;
    }


    double getSpread()
    {
        // cout << " This is spread from cpp end: " << getSpreadForCurrentMetrics() << endl;
        return CURRENT_METRICS.getSpreadForInterestRate();
    }

    double getThisMonthsPrimeRate()
    {
        // cout << " This is prime rate from cpp end: " << CURRENT_METRICS.getSuperPrimeRate() << endl;
        return CURRENT_METRICS.getSuperPrimeRate();
    }

    // double 

}