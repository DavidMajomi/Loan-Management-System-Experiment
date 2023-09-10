// #include "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\sqlite3.h"
#include "sqlite3.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "loanManagementSystemForServer.h"

// Use g++ -fPIC -shared -o loanManagementLibraryForServer.dll loanManagementLibraryForServer.cpp sqlite3.o

using namespace std;


// double PLACEHOLDER_BASE_YEARLY_INTEREST_RATE_FOR_CALCULATION = 250;

struct UserData
{
    char *userName;
    int creditScore;
    double monthlyIncomeDecimal;
    double financialReservesDecimal;
    double debtToIncomeRatioDecimal;
    double loanAmonutRequestedDeciaml;
    int duration;
};


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
    userAccount.calculateInterestForDefaultRisk();
    userAccount.computeCreditData();


    loanAccountsToAdd.push_back(userAccount);
}


extern "C" {
    void changeBaseRate(double primeRate)
    {
        BASE_YEARLY_INTEREST_RATE_FOR_CALCULATION = primeRate;
        BEST_MONTHLY_INTEREST_RATE_FOR_CALCULATION = BASE_YEARLY_INTEREST_RATE_FOR_CALCULATION / 12;
    }

    void addIndividualizedDataToDb(UserData tempUserDataFromPython)
    {
        vector<Loan> loanAccountsToAdd;

        addIndividualizedLoanDataFromPythonServer (tempUserDataFromPython, loanAccountsToAdd);
        createDatabaseToAddUserLoanData (loanAccountsToAdd);
    }
    

    bool readAndStoreGeneratedDataInDb(unsigned short int devMenuResponse)
    {
        bool fileOpeningError = false;
        ifstream inputFile;
        vector<Loan> loanAccounts;

        fileOpeningError = readGeneratedData(inputFile, loanAccounts, devMenuResponse);
        storeGeneratedDataInDatabase(loanAccounts);

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


}

