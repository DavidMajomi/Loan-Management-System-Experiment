#include <mutex>
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "../../Header Files/loanManagementLibraryForServer.h"

using namespace std;


bool testAddingSingleLoanData()
{
    bool successfullTest, testAccess;
    // string timeOfApplication;
    UserData test; // {"test cpp", 500, 20000, 200000, 0, 8000, 25};

    cout << " Test Access " << testAccess << endl;
    // string name = "test cpp";
    // char * nameChar = "test cpp";

    test.userName = "test cpp";
    test.creditScore = 500;
    test.monthlyIncomeDecimal = 20000;
    test.financialReservesDecimal = 200000;
    test.debtToIncomeRatioDecimal = 0;
    test.loanAmonutRequestedDeciaml = 8000;
    test.durationInMonthsInteger = 25;

    changeBaseRate(5.33);
    testAccess = addIndividualizedDataToDb(test);
    cout << " Test Access " << testAccess << endl;

    return successfullTest;
}

int main()
{
    bool successfullSingleLoanAddition;

    successfullSingleLoanAddition = testAddingSingleLoanData();


    return 0;
}