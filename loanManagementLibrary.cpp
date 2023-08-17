#include "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\sqlite3.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "loanManagementSystem.h"

// Use g++ -fPIC -shared -o loanManagementLibrary.dll loanManagementLibrary.cpp sqlite3.o

using namespace std;


struct UserData
{
    string userName;
    int duration;
    int creditScore;
    int debtToIncomeRatioDecimal;
    double monthlyIncomeDecimal;
    double financialReservesDecimal;
    double loanAmonutRequestedDeciaml;
};



void  fakeMain(unsigned short int initialResponse, unsigned short int devMenuResponse)
{
    int menuResponse;
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


void addIndividualizedLoanDataFromPythonServer(UserData tempUserData,  vector <Loan>& loanAccountsToAdd)
{
    Loan userAccount(0);

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


    unsigned short int showMenuOutsideCpp()
    {
        unsigned short int menuResponse = menu();

        return menuResponse;
    }


    void getValuesFromPython(unsigned short int initialResponse, unsigned short int devMenuResponse)
    {
        fakeMain(initialResponse, devMenuResponse);
    }


    void addIndividualizedDataToDb(UserData tempUserDataFromPython)
    {
        vector<Loan> loanAccountsToAdd;

        addIndividualizedLoanDataFromPythonServer (tempUserDataFromPython, loanAccountsToAdd);
        createDatabaseToAddUserLoanData (loanAccountsToAdd);
    }

    void readAndStoreGeneratedDataInDb(unsigned short int devMenuResponse)
    {
        ifstream inputfile;
        vector<Loan> loanAccounts;

        readGeneratedData(inputfile, loanAccounts, devMenuResponse);
        storeGeneratedDataInDatabase(loanAccounts);

        inputfile.close();
    }



    void readAndStoreGeneratedDataForAnalysis(unsigned short int devMenuResponse)
    {
        ifstream inputfile;
        ofstream outputCsvFile;
        vector<Loan> loanAccounts;

        readGeneratedData(inputfile, loanAccounts, devMenuResponse);
        outputFile (outputCsvFile, loanAccounts);


        inputfile.close();
        outputCsvFile.close();

    }




    // void getCustomerDataFromServer(UserData userDataFromPython, /*string user_name, int user_credit_score, int user_monthly_income, int user_financial_reserves, int user_debt_to_income_ratio,*/ int menu_response, int dev_menu_response, int search_menu_response)
    // {
    //     // UserData tempUser = {user_name, user_credit_score, user_monthly_income, user_financial_reserves, user_debt_to_income_ratio};



    // }

}

