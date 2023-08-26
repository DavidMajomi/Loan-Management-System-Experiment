#include "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\sqlite3.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "loanManagementSystemForServer.h"

// Use g++ -fPIC -shared -o loanManagementLibrary.dll loanManagementLibrary.cpp sqlite3.o

using namespace std;


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
    void addIndividualizedDataToDb(UserData tempUserDataFromPython)
    {
        vector<Loan> loanAccountsToAdd;

        // cout << " Got data. " << endl;
        cout << tempUserDataFromPython.monthlyIncomeDecimal;
        cout << endl;

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
        bool openInputFileError = false, openOutputFileError = true,  fileOpeningError = false;
        ifstream inputFile;
        ofstream outputCsvFile;
        vector<Loan> loanAccounts;

        openInputFileError = readGeneratedData(inputFile, loanAccounts, devMenuResponse);
        openOutputFileError = outputToFile (outputCsvFile, loanAccounts);

        if ((openInputFileError == true) || (openOutputFileError == true))
        {
            fileOpeningError = true;
        }

        return fileOpeningError;
    }


}

