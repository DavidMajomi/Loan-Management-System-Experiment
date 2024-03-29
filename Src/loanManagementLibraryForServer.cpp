#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "../Header Files/Logger.h"
#include "../Header Files/loanManagementSystemForServer.h"


// Use g++ -fPIC -shared -o loanManagementLibraryForServer.dll loanManagementLibraryForServer.cpp sqlite3.o
// Upcoming Task: Add functionality for year on year inflation rate.
using namespace std;


struct UserData
{
    char* userName;
    int creditScoreInteger;
    double monthlyIncomeDecimal;
    double financialReservesDecimal;
    double debtToIncomeRatioDecimal;
    double loanAmonutRequestedDeciaml;
    int durationInMonthsInteger;
};


void addIndividualizedLoanDataFromPythonServer(UserData tempUserData,  vector <Loan>& loanAccountsToAdd)
{
    Loan userAccount(tempUserData.userName, tempUserData.creditScoreInteger, tempUserData.monthlyIncomeDecimal, tempUserData.financialReservesDecimal, tempUserData.debtToIncomeRatioDecimal, tempUserData.durationInMonthsInteger, tempUserData.loanAmonutRequestedDeciaml);

    loanAccountsToAdd.push_back(userAccount);

}


#if _WIN64
    
    /*
     * All functions within this extern are potentially non thread safe, but since they are mostly used from the dev menu, they wont run 
     *        into thread related issues for now, however, potential fixes using mutex would be coming soon
     * 
     */
    extern "C" {
        void changeBaseRate(double primeRate)
        {
            cout << " This is entered prime rate: " << primeRate << endl;

            if (CURRENT_METRICS.getClassModificationState() == false)
            {
                CURRENT_METRICS.setFederalFundsRatePercent(primeRate);
                CURRENT_METRICS.lockModificationOfClass();
            }
            else
            {
                cout << " This class has already being locked with todays metrics, no modification allowed." << endl;
            }

                // cout << " Prime Rate has been Changed to " << getCurrentFFR() << endl;
        }


        bool addIndividualizedDataToDb(UserData tempUserDataFromPython)
        {

            bool fileOpeningError = false;
            vector<Loan> loanAccountsToAdd;

            addIndividualizedLoanDataFromPythonServer (tempUserDataFromPython, loanAccountsToAdd);
            fileOpeningError = createDatabaseToAddUserLoanData (loanAccountsToAdd);

            // DISPLAY.display(" This is federalFundsRate from todays metrics: ",  TODAYS_METRICS.getFederalFundsRate());
            // DISPLAY.display(" This is federalFundsRate from current metrics: ", CURRENT_METRICS.getFederalFundsRate());

            return fileOpeningError;
        }
        

        bool readAndStoreGeneratedDataInDb(unsigned short int devMenuResponse)
        {
            bool fileOpeningError = false, errorReadingData = false, errorStoringData = false;
            ifstream inputFile;
            vector<Loan> loanAccounts;

            errorReadingData = readGeneratedData(inputFile, loanAccounts, devMenuResponse);
            errorStoringData = storeGeneratedDataInDatabase(loanAccounts);

            if (errorReadingData == true || errorStoringData == true)
            {
                fileOpeningError = true;
            }

            return fileOpeningError;
        }


        bool readAndStoreGeneratedDataInDbWithTransaction(unsigned short int devMenuResponse)
        {
            bool fileOpeningError = false, errorReadingData = false, errorStoringData = false;
            ifstream inputFile;
            vector<Loan> loanAccounts;

            errorReadingData = readGeneratedData(inputFile, loanAccounts, devMenuResponse);
            errorStoringData = storeDataInDbUsingSingleTransaction(loanAccounts);

            if (errorReadingData == true || errorStoringData == true)
            {
                fileOpeningError = true;
            }

            return fileOpeningError;
        }


        bool readAndStoreGeneratedDataForAnalysis(unsigned short int devMenuResponse)
        {
            ifstream inputFile;
            ofstream outputCsvFile;
            vector<Loan> loanAccounts;
            bool openInputFileError = false, openOutputFileError = false,  fileOpeningError = false;

            openInputFileError = readGeneratedData(inputFile, loanAccounts, devMenuResponse);
            openOutputFileError = outputToFile (outputCsvFile, loanAccounts);

            if ((openInputFileError == true) || (openOutputFileError == true))
            {
                fileOpeningError = true;
                // cout << " Error opening file = true. " << endl;
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


        bool testAccess()
        {
            cout << " The test. " << endl;
            return true;
        }


        void switchLogger()
        {
            DISPLAY.switchScreenDisplay();
        }

    }


#endif


