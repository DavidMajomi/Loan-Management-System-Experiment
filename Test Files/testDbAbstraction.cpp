#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <filesystem>// cpp 17 reference https://en.cppreference.com/w/cpp/filesystem/current_paths
#include "../header Files/databaseAbstraction.h"


namespace fs = std::filesystem;
using namespace std;

// FILE NAMES
const string CURRENT_FULL_PATH = fs::current_path().string();
const string DATABASE_NAME_WITH_PATH = CURRENT_FULL_PATH + "\\Test Files\\Executables\\bam_bam.db";       // Has to be a constant char to be compatibe with sqlite

const char* DATABASE_NAME = DATABASE_NAME_WITH_PATH.c_str();

template <typename T>
void printMatrixValues(vector<vector <T>> dBDataMatrix)
{
    int matrixSize = dBDataMatrix.size();
    for(int count = 0; count < matrixSize; count++)
    {
        for(int j = 0; j < dBDataMatrix[count].size(); j++)
        {
            cout << dBDataMatrix[count][j] << endl;
        }

        cout << endl << endl;
        
    }
}


void getData()
{
    vector <vector<string>> dBDataMatrix;
    try
    {
        dBDataMatrix = databaseAbstraction::retrieveAllUserDataFromDatabaseForMatrix(DATABASE_NAME, "users");
        printMatrixValues(dBDataMatrix);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(string exception)
    {
        cout << " Error exception caught: " << endl;
        cout << " Exception value: " << exception << endl;
    }
    catch(const char * exception)
    {
        cout << " Error exception caught: " << endl;
        cout << " Exception value: " << exception << endl;
    }
}


template <typename T>
void addData()
{
    double timeInMilliSeconds;
    bool addedSucessfully = false;
    int creditScore = 850;
    vector <vector <pair <T, string>>> dataToAdd;
    vector <pair <T, string>> temp (21);
    dataToAdd.push_back(temp);
    dataToAdd.push_back(temp);
    string name = "test db", timeOfApplication = "Sat Feb 10 17:27:06 2024";
    string monthlyIncome = "4000", financialReserves = "12000", debtToIncomeRatio = "0.2", loanDurationInMonths = "40", loanAmount = "5000",
           monthlyInteresRate = "0.2", yearlyInterestRate = "14", recoveryRate = "1", outstandingMonthlyDebtPaymentsFromLoan = "2",
           defaultRiskScore = "1.2", loanViabilityScore = "380", adjustedLoanViabilityScore = "300", lossGivenDefault = "2", 
           interestRateByGroup = "30", bestPossibleRate = "8.33", worstPossibleRate = "30";
    string dataType = typeid(double).name();

    cout << " In add data" << endl;

    // Populate vector with data
    dataToAdd[0][0].first = name;
    dataToAdd[0][1].first = timeOfApplication;
    dataToAdd[0][2].first = to_string(creditScore);
    dataToAdd[0][3].first = monthlyIncome;
    dataToAdd[0][4].first = financialReserves;
    dataToAdd[0][5].first = debtToIncomeRatio;
    dataToAdd[0][6].first = loanDurationInMonths;
    dataToAdd[0][7].first = loanAmount;
    dataToAdd[0][8].first = monthlyInteresRate;
    dataToAdd[0][9].first = yearlyInterestRate;
    dataToAdd[0][10].first = lossGivenDefault;
    dataToAdd[0][11].first = recoveryRate;
    dataToAdd[0][12].first = outstandingMonthlyDebtPaymentsFromLoan;
    dataToAdd[0][13].first = defaultRiskScore;
    dataToAdd[0][14].first = loanViabilityScore;
    dataToAdd[0][15].first = adjustedLoanViabilityScore;
    dataToAdd[0][16].first = adjustedLoanViabilityScore;
    dataToAdd[0][17].first = interestRateByGroup;
    dataToAdd[0][18].first = bestPossibleRate;
    dataToAdd[0][19].first = worstPossibleRate;
    dataToAdd[0][20].first = "";
    
    // Populate vector with data type
    dataToAdd[1][0].second = typeid(string).name();
    dataToAdd[1][1].second = typeid(string).name();
    dataToAdd[1][2].second = dataType;
    dataToAdd[1][3].second = dataType;
    dataToAdd[1][4].second = dataType;
    dataToAdd[1][5].second = dataType;
    dataToAdd[1][6].second = dataType;
    dataToAdd[1][7].second = dataType;
    dataToAdd[1][8].second = dataType;
    dataToAdd[1][9].second = dataType;
    dataToAdd[1][10].second = dataType;
    dataToAdd[1][11].second = dataType;
    dataToAdd[1][12].second = dataType;
    dataToAdd[1][13].second = dataType;
    dataToAdd[1][14].second = dataType;
    dataToAdd[1][15].second = dataType;
    dataToAdd[1][16].second = dataType;
    dataToAdd[1][17].second = dataType;
    dataToAdd[1][18].second = dataType;
    dataToAdd[1][19].second = dataType;
    dataToAdd[1][20].second = typeid(string).name();
     // Populate vector with data
    dataToAdd[1][0].first = name;
    dataToAdd[1][1].first = timeOfApplication;
    dataToAdd[1][2].first = to_string(creditScore);
    dataToAdd[1][3].first = monthlyIncome;
    dataToAdd[1][4].first = financialReserves;
    dataToAdd[1][5].first = debtToIncomeRatio;
    dataToAdd[1][6].first = loanDurationInMonths;
    dataToAdd[1][7].first = loanAmount;
    dataToAdd[1][8].first = monthlyInteresRate;
    dataToAdd[1][9].first = yearlyInterestRate;
    dataToAdd[1][10].first = lossGivenDefault;
    dataToAdd[1][11].first = recoveryRate;
    dataToAdd[1][12].first = outstandingMonthlyDebtPaymentsFromLoan;
    dataToAdd[1][13].first = defaultRiskScore;
    dataToAdd[1][14].first = loanViabilityScore;
    dataToAdd[1][15].first = adjustedLoanViabilityScore;
    dataToAdd[1][16].first = adjustedLoanViabilityScore;
    dataToAdd[1][17].first = interestRateByGroup;
    dataToAdd[1][18].first = bestPossibleRate;
    dataToAdd[1][19].first = worstPossibleRate;
    dataToAdd[1][20].first = "";
    
    // Populate vector with data type
    dataToAdd[0][0].second = typeid(string).name();
    dataToAdd[0][1].second = typeid(string).name();
    dataToAdd[0][2].second = dataType;
    dataToAdd[0][3].second = dataType;
    dataToAdd[0][4].second = dataType;
    dataToAdd[0][5].second = dataType;
    dataToAdd[0][6].second = dataType;
    dataToAdd[0][7].second = dataType;
    dataToAdd[0][8].second = dataType;
    dataToAdd[0][9].second = dataType;
    dataToAdd[0][10].second = dataType;
    dataToAdd[0][11].second = dataType;
    dataToAdd[0][12].second = dataType;
    dataToAdd[0][13].second = dataType;
    dataToAdd[0][14].second = dataType;
    dataToAdd[0][15].second = dataType;
    dataToAdd[0][16].second = dataType;
    dataToAdd[0][17].second = dataType;
    dataToAdd[0][18].second = dataType;
    dataToAdd[0][19].second = dataType;
    dataToAdd[0][20].second = typeid(string).name();
    
    cout << "DOne populating" << endl;
    
    try
    {
        timeInMilliSeconds = databaseAbstraction::storeDataInDbUsingSingleTransaction(DATABASE_NAME, 
        "CREATE TABLE IF NOT EXISTS users (Loan_id INTEGER PRIMARY KEY, name TEXT, time_of_application TEXT, credit_score INTEGER, monthly_income REAL, financial_reserves REAL, debt_to_income_ratio REAL,"
        " loan_duration REAL, requested_loan_amount REAL, monthly_interest_rate REAL, yearly_interest_rate REAL, loss_given_default REAL, recovery_rate REAL,"
        " outstanding_monthly_debt_paymentd_from_loan REAL, default_risk_score REAL, loan_viability_score REAL, adjusted_loan_viability_score REAL, matrix_based_adjusted_loan_viability_score REAL, interest_rate_by_group REAL,"
        " best_possible_rate REAL, worst_possible_rate REAL, final_loan_grade TEXT)",
        " INSERT INTO users (name , time_of_application, credit_score , monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rate,"
        " yearly_interest_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_paymentd_from_loan, default_risk_score, loan_viability_score,"
        " adjusted_loan_viability_score, matrix_based_adjusted_loan_viability_score, interest_rate_by_group, best_possible_rate, worst_possible_rate, final_loan_grade)",
        dataToAdd);

        cout << "Done with: " << 1  << " time: " << timeInMilliSeconds << endl; 
        databaseAbstraction::storeDataInDbUsingSingleTransaction(DATABASE_NAME, 
        "CREATE TABLE IF NOT EXISTS shabo (Loan_id INTEGER PRIMARY KEY, name TEXT, time_of_application TEXT, credit_score INTEGER, monthly_income REAL, financial_reserves REAL, debt_to_income_ratio REAL,"
        " loan_duration REAL, requested_loan_amount REAL, monthly_interest_rate REAL, yearly_interest_rate REAL, loss_given_default REAL, recovery_rate REAL,"
        " outstanding_monthly_debt_paymentd_from_loan REAL, default_risk_score REAL, loan_viability_score REAL, adjusted_loan_viability_score REAL, matrix_based_adjusted_loan_viability_score REAL, interest_rate_by_group REAL,"
        " best_possible_rate REAL, worst_possible_rate REAL, final_loan_grade TEXT)",
        " INSERT INTO shabo (name , time_of_application, credit_score , monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rate,"
        " yearly_interest_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_paymentd_from_loan, default_risk_score, loan_viability_score,"
        " adjusted_loan_viability_score, matrix_based_adjusted_loan_viability_score, interest_rate_by_group, best_possible_rate, worst_possible_rate, final_loan_grade)",
        dataToAdd);

        cout << " Done with: " << 3 << " time: " << timeInMilliSeconds << endl; 
        databaseAbstraction::storeDataInDbUsingSingleTransaction(DATABASE_NAME, 
        "CREATE TABLE IF NOT EXISTS shabo (Loan_id INTEGER PRIMARY KEY, name TEXT, time_of_application TEXT, credit_score INTEGER, monthly_income REAL, financial_reserves REAL, debt_to_income_ratio REAL,"
        " loan_duration REAL, requested_loan_amount REAL, monthly_interest_rate REAL, yearly_interest_rate REAL, loss_given_default REAL, recovery_rate REAL,"
        " outstanding_monthly_debt_paymentd_from_loan REAL, default_risk_score REAL, loan_viability_score REAL, adjusted_loan_viability_score REAL, matrix_based_adjusted_loan_viability_score REAL, interest_rate_by_group REAL,"
        " best_possible_rate REAL, worst_possible_rate REAL, final_loan_grade TEXT)",
        " INSERT INTO shabo (name , time_of_application, credit_score , monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rate,"
        " yearly_interest_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_paymentd_from_loan, default_risk_score, loan_viability_score,"
        " adjusted_loan_viability_score, matrix_based_adjusted_loan_viability_score, interest_rate_by_group, best_possible_rate, worst_possible_rate, final_loan_grade)",
        dataToAdd);

        cout << " Done with: " << 3 << " time: " << timeInMilliSeconds << endl; 
    
    }
    catch(const char * error)
    {
        cout << error << endl;
    }

    cout << "hello in add data" << endl;
    
}


void update()
{
    cout << " in update " << endl;
    try
    {
        double value = databaseAbstraction::update(DATABASE_NAME, "users", "financial_reserves", "200000000", "Loan_id", 22);
        // cout << " Timetaken to insert: " << value << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(const char * error)
    {
        cout << "ERROR: "; 
        cout << error << endl;
    }

    
    cout << "done update " << endl;
}


void deleteValue()
{
    try
    {
        double value = databaseAbstraction::deleteRow(DATABASE_NAME, "users", "name", "Loan_id", 20);
    }
    catch(const char * error)
    {
        cout << error << endl;
    }

}


void addColumn()
{
    try
    {
        double value = databaseAbstraction::addNewColumn(DATABASE_NAME, "users", "baggage", "'TEXT'");
    }
    catch(const char * error)
    {
        cout << error << endl;
        cout << " Error adding column " << endl;
    }

}


void deleteColumn()
{
    try
    {
        double value = databaseAbstraction::deleteColumn(DATABASE_NAME, "users", "baggage");
    }
    catch(const char * exception)
    {
        cout << exception << endl;
    }
}


void retreiveData()
{
    vector <vector<string>> dBDataMatrix;
    try
    {
        dBDataMatrix = databaseAbstraction::retreiveDataWithMatchingValue(DATABASE_NAME, "users", "Loan_id", "12");
        printMatrixValues(dBDataMatrix);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(string exception)
    {
        cout << " Error exception caught: " << endl;
        cout << " Exception value: " << exception << endl;
    }
    catch(const char * exception)
    {
        cout << " Error exception caught: " << endl;
        cout << " Exception value: " << exception << endl;
        cout << " Error retreiving Data" << endl;
    }
}


void addSingleData()
{
    try
    {
        string values = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21";
        string insert = "INSERT INTO users (name , time_of_application, credit_score , monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rate,"
                      " yearly_interest_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_paymentd_from_loan, default_risk_score, loan_viability_score,"
                      " adjusted_loan_viability_score, matrix_based_adjusted_loan_viability_score, interest_rate_by_group, best_possible_rate, worst_possible_rate, final_loan_grade) VALUES (" + values + ");";
        string format = "CREATE TABLE IF NOT EXISTS users (Loan_id INTEGER PRIMARY KEY, name TEXT, time_of_application TEXT, credit_score INTEGER, monthly_income REAL, financial_reserves REAL, debt_to_income_ratio REAL,"
                      " loan_duration REAL, requested_loan_amount REAL, monthly_interest_rate REAL, yearly_interest_rate REAL, loss_given_default REAL, recovery_rate REAL,"
                      " outstanding_monthly_debt_paymentd_from_loan REAL, default_risk_score REAL, loan_viability_score REAL, adjusted_loan_viability_score REAL, matrix_based_adjusted_loan_viability_score REAL, interest_rate_by_group REAL,"
                      " best_possible_rate REAL, worst_possible_rate REAL, final_loan_grade TEXT)";
        double timeTaken = databaseAbstraction::storeSingleRowInDbUsingSingleInsert(DATABASE_NAME, format, "users", insert);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(const char * exception)
    {
        cout << exception << endl;
        cout << " Error storing single data. " << endl;
    }
}


int main()
{
    cout << DATABASE_NAME_WITH_PATH << endl;
    // getData();
    // addData<string>();
    // update();
    // deleteValue();
    addSingleData();
    retreiveData();
    
    addColumn();
    cout << "Validate new column exists then press enter" << endl;
    system("pause");
    deleteColumn();
    cout << " Validate new column deleted then press enter" << endl;
    system("pause");

    cout << "Done with all tests. " << endl;
    
    return 0;
}
// cout << "time taken for transaction = " <<  timeInt << " millisecond(s), which is equal to " << timeInSeconds << " seconds" << endl;

