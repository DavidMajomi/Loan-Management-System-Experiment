#include <iostream>
#include <vector>
#include "../../Header Files/loanDatabaseManager.h"
#include "../../Header Files/loanManagementLibraryForServer.h"


using namespace std;

int main()
{
    changeBaseRate(5.33);
    cout << CURRENT_METRICS.getFederalFundsRate() << endl;
    cout << " Prime Rate has been Changed to " << CURRENT_METRICS.getPrimeRate() << endl;
    cout << " Feds fund rate " << CURRENT_METRICS.getFederalFundsRate() << endl;
    cout << CURRENT_METRICS.getBaseYearlyInterestRatePercentForLoans() << endl;
    Loan test("Test Db", 780, 12000, 200000, 0.2, 20, 20000);
    ofstream outputsCsvFile;
    cout << "Hello this is loan database manager tester " << endl;
    cout << CURRENT_METRICS.getBaseYearlyInterestRatePercentForLoans() << endl;

    cout << "Interest rate = " << test.getYearlyInterestRate() << endl;
    cout << endl;
    
    
    try
    {
        int value = databaseManager::retrieveAllUserDataFromDatabaseAndOutputToCsv(outputsCsvFile);
        vector<vector<string>> dataValues = databaseManager::getAllDbDATA();
        cout << "Loan id: " << dataValues[0][0] << endl << "Name: " << dataValues[0][1] << endl;
        cout << "Loan id: " << dataValues[1][0] << endl << "Date: " << dataValues[1][2] << endl;
        cout << "Name with loan id = 1 is " << databaseManager::retreiveUserNameMatchingLoanId(1) << endl;
        
        bool boolValue = databaseManager::addLoanUser(test);
        
        cout << endl;
    }
    catch(const char * exception)
    {
        cout << exception << endl;
    }
    catch(...)
    {
        cout << endl;
        cout << "UNKNOWN EXCEPTION" << endl;
    }


    cout << "Done getting db files" << endl;


    return 0;
}