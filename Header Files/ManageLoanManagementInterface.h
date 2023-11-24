#include <iostream>
#include "EconomicMetrics.h"
#include "Loan.h"

// #ifndef LOANMANAGEMENTSYSTEMFORSERVER_H_INCLUDED
// #define LOANMANAGEMENTSYSTEMFORSERVER_H_INCLUDED
#pragma once

#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "sqlite3.h"
// #include "constants.h"

#include <filesystem>// cpp 17 reference https://en.cppreference.com/w/cpp/filesystem/current_paths


namespace fs = std::filesystem;
// Next Task: Modify the weights to represent the removed interest rate weight
using namespace std;

// FILE NAMES
const string CURRENT_FULL_PATH = fs::current_path().string();
const string DATABASE_NAME_WITH_PATH = CURRENT_FULL_PATH + "\\Database files\\bam_bam.db";       // Has to be a constant char to be compatibe with sqlite
const char* DATABASE_NAME = DATABASE_NAME_WITH_PATH.c_str();
const string CSV_FILE_FOR_ALL_GENERATED_LOAN_DATA = CURRENT_FULL_PATH + "\\Folder with Generated Data\\allGeneratedLoanData.csv";     // Based only on historical generated data, no new generated data here
const string OUTPUT_CSV_FILE_FOR_PROCESSED_DATA = CURRENT_FULL_PATH + "\\Csv Files For Analysis\\processedLoanData.csv";
const string CSV_FILE_FOR_STORING_ANALAYZED_DB_VALUES = CURRENT_FULL_PATH + "\\Csv Files For Analysis\\analyzedDataFromDb.csv";
const string CSV_FILE_FOR_TEMP_GENERATED_DATA_FOR_DB = CURRENT_FULL_PATH + "\\Folder with Generated Data\\tempGeneratedLoanDataForDbStorage.csv";


const unsigned short int MAX_CREDIT_SCORE = 850;
const unsigned short int MIN_CREDIT_SCORE = 300;

const unsigned short int MAX_MONTHLY_INCOME = 12000;
const unsigned short int MIN_MONTHLY_INCOME = 800;

const double CREDIT_SCORE_WEIGHT = 0.20;          // Most important metric, it shows credit worthiness, while minimizing risk
const double LOSS_GIVEN_DEFAULT_WEIGHT = -0.15;   // Potential Losses when considering Financial Reserves
const double DEBT_TO_INCOME_RATIO_WEIGHT = -0.15;   // Works as a measure of the customer's ability to shoulder debt weight
const double LOAN_AMOUNT_WEIGHT = 0.12;          // Works as a measure of possible profitability to some extent, but needs to be reduced
const double DEFAULT_RISK_SCORE_WEIGHT = -0.10;   // Risk accrued for higher returns, foregoing more secure investment options.
// const double INTEREST_RATE_WEIGHT = 0.08;        // Measure of profitability to the bank, POSSIBLE FORMULA INVOLVING THIS, LOAN AMOUNT AND DURATION TO BE MORE PRECISE.
const double FINANCIAL_RESERVES_WEIGHT = 0.08;   // All liquidable financial assets weight
const double LOAN_DURATION_WEIGHT = 0.06;        // Duration of the loan, NEED TO ADJUST THIS WEIGHT DRASTICALLY
const double MONTHLY_INCOME_WEIGHT = 0.06;        // Not as important, because DTI covers this, however, valuable to weigh customer value, POSSIBLE FORMULA IN THE FUTURE

const unsigned short int MAX_LOAN_DURATION = 60;
const double MIN_LOAN_DURATION = 1;
// const double MAX_INTEREST_RATE = 2.08;
// const double MIN_INTEREST_RATE = 0.58;
const double MAX_FINANCIAL_RESERVES = 50000;
const double MIN_FINANCIAL_RESERVES = 10000;
const double MAX_LOAN_AMOUNT = 50000;
const double MIN_LOAN_AMOUNT = 500;

const double BEST_DEFAULT_RISK_SCORE = 0; 
const double BEST_LOSS_GIVEN_DEFAULT = 0;
const double BEST_DEBT_TO_INCOME_RATIO = 0;
// const double BEST_FINAL_MONTHLY_INTEREST_RATE = 0.58;

const double WORST_DEFAULT_RISK_SCORE = 1;   // add this to loan viability formula
const double WORST_LOSS_GIVEN_DEFAULT = 0.8;   // possible value includes 0.2, 0.1, 1 = too high
const double WORST_DEBT_TO_INCOME_RATIO = 0.9; //
// const double WORST_FINAL_MONTHLY_INTEREST_RATE = 2;   // Check the logic behind this



using namespace std;

bool storeDataInDb(vector<Loan> loanData)
{
    sqlite3* db;
    int numberOfAddedLoanValues, creditScore, numMetricsToAdd;
    int rc = sqlite3_open(DATABASE_NAME, &db);
    bool errorStoringData = false;
    char charFinalSqlInsertStatement;
    const char* sqlInsertLine;
    const char* sql = "CREATE TABLE IF NOT EXISTS users (Loan_id INTEGER PRIMARY KEY, name TEXT, credit_score INTEGER, monthly_income REAL, financial_reserves REAL, debt_to_income_ratio REAL,"
                      " loan_duration REAL, requested_loan_amount REAL, monthly_interest_rate REAL, yearly_interest_rate REAL, loss_given_default REAL, recovery_rate REAL,"
                      " outstanding_monthly_debt_paymentd_from_loan REAL, default_risk_score REAL, loan_viability_score REAL, adjusted_loan_viability_score REAL, interest_rate_by_group REAL,"
                      " best_possible_rate REAL, worst_possible_rate REAL)";
    vector <string> valsToInsert;
    string insertToSql, userName, stringFinalSqlInsertStatement, stringCreditScore, stringMonthlyIncome, stringFinancialReserves, stringDebtToIncomeRatio, stringLoanDurationInMonths, stringLoanAmount, stringMonthlyInteresRate, 
           stringyearlyInterestRate, stringrecoveryRate, stringOutstandingMonthlyDebtPaymentsFromLoan, stringDefaultRiskScore, stringLoanViabilityScore,
           stringAdjustedLoanViabilityScore, stringLossGivenDefault, stringInterestRateByGroup, stringBestPossibleRate, stringWorstPossibleRate;
    double monthlyIncome, financialReserves, debtToIncomeRatio, loanDurationInMonths, loanAmount, monthlyInteresRate, 
           yearlyInterestRate, recoveryRate, outstandingMonthlyDebtPaymentsFromLoan, defaultRiskScore, loanViabilityScore,
           adjustedLoanViabilityScore, lossGivenDefault, interestRateByGroup, bestPossibleRate, worstPossibleRate;


    numberOfAddedLoanValues = loanData.size();

    if (rc != SQLITE_OK) {
        // Handle error
        //cout << "Step 1 error. 2" << endl;
        errorStoringData = true;
    }


    sqlite3_stmt* stmt;
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        // Handle error preparing the statement
        //cout << "Step 2 error. 2" << endl;
        sqlite3_close(db);
        errorStoringData = true;
    }
    rc = sqlite3_exec(db, sql, 0, 0, 0);

    if (rc != SQLITE_OK) {
        // Handle error
        //cout << " Step 3 error. 2" << endl;
        sqlite3_close(db);
        errorStoringData = true;
    }

    for (int count = 0; count < numberOfAddedLoanValues; count++)
    {
        creditScore = loanData[count].getCreditScore();
        monthlyIncome = loanData[count].getMonthlyIncome() ;
        financialReserves = loanData[count].getFinancialReserves() ;
        debtToIncomeRatio = loanData[count].getDebtToIncomeRatio() ;
        loanDurationInMonths = loanData[count].getDurationInMonths() ;
        loanAmount = loanData[count].getLoanAmount();
        monthlyInteresRate = loanData[count].getMonthlyInterestRate();
        yearlyInterestRate = loanData[count].getYearlyInterestRate();
        userName =  loanData[count].getUserName();
        lossGivenDefault = loanData[count].getLossGivenDefault();
        recoveryRate = loanData[count].getRecoveryRate();
        outstandingMonthlyDebtPaymentsFromLoan = loanData[count].getTotalOutstandingMonthlyDebtPaymentsAfterLoan();
        defaultRiskScore = loanData[count].getDefaultRiskScore();
        loanViabilityScore = loanData[count].getLoanViabilityScore();
        adjustedLoanViabilityScore = loanData[count].getFinalAdjustedLoanViabilityScore();
        interestRateByGroup = loanData[count].getInterestRateByGroup();
        bestPossibleRate = loanData[count].getBestPossibleRate();
        worstPossibleRate = loanData[count].getWorstPossibleRate();

        stringCreditScore = to_string(creditScore);
        stringMonthlyIncome = to_string(monthlyIncome);
        stringFinancialReserves = to_string(financialReserves);
        stringDebtToIncomeRatio = to_string(debtToIncomeRatio);
        stringLoanDurationInMonths = to_string(loanDurationInMonths);
        stringLoanAmount = to_string(loanAmount);
        stringMonthlyInteresRate = to_string(monthlyInteresRate);
        stringyearlyInterestRate = to_string(yearlyInterestRate);
        stringLossGivenDefault = to_string(lossGivenDefault);
        stringrecoveryRate = to_string(recoveryRate);
        stringOutstandingMonthlyDebtPaymentsFromLoan = to_string(outstandingMonthlyDebtPaymentsFromLoan);
        stringDefaultRiskScore = to_string(defaultRiskScore);
        stringLoanViabilityScore = to_string(loanViabilityScore);
        stringAdjustedLoanViabilityScore = to_string(adjustedLoanViabilityScore);
        stringInterestRateByGroup = to_string(interestRateByGroup);
        stringBestPossibleRate = to_string(bestPossibleRate);
        stringWorstPossibleRate = to_string(worstPossibleRate);

        // //cout << outstandingMonthlyDebtPaymentsFromLoan << endl;

        valsToInsert.push_back(stringCreditScore);
        valsToInsert.push_back(stringMonthlyIncome);
        valsToInsert.push_back(stringFinancialReserves);
        valsToInsert.push_back(stringDebtToIncomeRatio);
        valsToInsert.push_back(stringLoanDurationInMonths);
        valsToInsert.push_back(stringLoanAmount);
        valsToInsert.push_back(stringMonthlyInteresRate);
        valsToInsert.push_back(stringyearlyInterestRate);
        valsToInsert.push_back(stringLossGivenDefault);
        valsToInsert.push_back(stringrecoveryRate);
        valsToInsert.push_back(stringOutstandingMonthlyDebtPaymentsFromLoan);
        valsToInsert.push_back(stringDefaultRiskScore);
        valsToInsert.push_back(stringLoanViabilityScore);
        valsToInsert.push_back(stringAdjustedLoanViabilityScore);
        valsToInsert.push_back(stringInterestRateByGroup);
        valsToInsert.push_back(stringBestPossibleRate);
        valsToInsert.push_back(stringWorstPossibleRate);

        numMetricsToAdd = valsToInsert.size();

        // //cout << " after pushback" << endl;

        stringFinalSqlInsertStatement = "'" + userName + "',";

        // //cout << " This is userNmae after string addition: " << stringFinalSqlInsertStatement << endl;

        for (int count = 0; count < numMetricsToAdd; count++)
        {

            if (count <= (numMetricsToAdd - 2))
            {

                stringFinalSqlInsertStatement = stringFinalSqlInsertStatement + valsToInsert[count] + ",";
            }
            else
            {
                stringFinalSqlInsertStatement = stringFinalSqlInsertStatement + valsToInsert[count];
            }
        }
        
        //cout << endl;
        // //cout << stringFinalSqlInsertStatement << endl;

        insertToSql = "INSERT INTO users (name , credit_score , monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rate,"
                      " yearly_interest_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_paymentd_from_loan, default_risk_score, loan_viability_score,"
                      " adjusted_loan_viability_score, interest_rate_by_group, best_possible_rate, worst_possible_rate) VALUES (" + stringFinalSqlInsertStatement + ")"; 

        // //cout << insertToSql;

        sqlInsertLine = insertToSql.c_str();
        sql = sqlInsertLine;

        rc = sqlite3_exec(db, sql, 0, 0, 0);

        if (rc != SQLITE_OK) {
            // Handle error
            cout << " Step 4 error.  Sql statement error in store generated data function." << endl;
            sqlite3_close(db);
            errorStoringData = true;
        }

        valsToInsert.clear();
    }


    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return errorStoringData;

    
}


bool createDatabaseToAddUserLoanData(vector<Loan>& loanAccountsToAdd) 
{
    bool errorStoringData = false;

    errorStoringData = storeDataInDb(loanAccountsToAdd);

    return errorStoringData;
}


bool storeGeneratedDataInDatabase(vector<Loan>& loanAccounts) 
{
    bool errorStoringData = false;

    errorStoringData = storeDataInDb(loanAccounts);

    return errorStoringData;

}


bool retrieveAllUserDataFromDatabase(ofstream& outputCsvFile) 
{
    int creditScore, loanId;
    bool errorRetrievingData = false;
    const char* sql = "SELECT * FROM users";
    double monthlyIncome, financialReserves, debtToIncomeRatio, loanDurationInMonths, loanAmount, monthlyInteresRate, 
           yearlyInterestRate, recoveryRate, outstandingMonthlyDebtPaymentsFromLoan, defaultRiskScore, loanViabilityScore,
           adjustedLoanViabilityScore, lossGivenDefault, interestRateByGroup, bestPossibleRate, worstPossibleRate;
    sqlite3* db;
    int rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc != SQLITE_OK)
    {
        // Handle error
        //cout << "Step 1 error." << endl;
        errorRetrievingData = true;
    }
    else
    {

        outputCsvFile.open(CSV_FILE_FOR_STORING_ANALAYZED_DB_VALUES);

        cout << " This is File path for analyzed data: " << CSV_FILE_FOR_STORING_ANALAYZED_DB_VALUES << endl;

        if (outputCsvFile.fail())
        {
            //cout << " Output File Opening Error. " << endl;
            errorRetrievingData = true;
            cout << " Error opening File" << endl;
        }
        else
        {
            sqlite3_stmt* stmt;
            
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

            if (rc != SQLITE_OK) {
                // Handle error
                //cout << " Step 5 error. " << endl;
                sqlite3_close(db);
                errorRetrievingData = true;
            }

            outputCsvFile << "Name,credit_score,monthly_income,financial_reserves,debt_to_income_ratio,Duration_in_months,loan_amount_requested,Monthly_interest_rate,Interest_rate_over_a_year,"
                             "loss_Given_Default,Recovery_Rate,outstanding_Monthly_Debt_Payments,";
            outputCsvFile << "default_risk_score,Loan_Viability_Score,Adjusted_Loan_viability_Score,interest_rate_by_group,best_possible_rate,worst_possible_rate" << endl;

            while (sqlite3_step(stmt) == SQLITE_ROW) {
                // loanId = sqlite3_column_int(stmt, 0);
                const unsigned char* userName = sqlite3_column_text(stmt, 1);
                creditScore = sqlite3_column_int(stmt, 2);
                monthlyIncome = sqlite3_column_double(stmt, 3);
                financialReserves = sqlite3_column_double(stmt, 4);
                debtToIncomeRatio = sqlite3_column_double(stmt, 5);
                loanDurationInMonths = sqlite3_column_double(stmt, 6);
                loanAmount = sqlite3_column_double(stmt, 7);
                monthlyInteresRate = sqlite3_column_double(stmt, 8);
                yearlyInterestRate = sqlite3_column_double(stmt, 9);
                lossGivenDefault = sqlite3_column_double(stmt, 10);
                recoveryRate = sqlite3_column_double(stmt, 11);
                outstandingMonthlyDebtPaymentsFromLoan = sqlite3_column_double(stmt, 12);
                defaultRiskScore = sqlite3_column_double(stmt, 13);
                loanViabilityScore = sqlite3_column_double(stmt, 14);
                adjustedLoanViabilityScore = sqlite3_column_double(stmt, 15);
                interestRateByGroup = sqlite3_column_double(stmt, 16);
                bestPossibleRate = sqlite3_column_double(stmt, 17);
                worstPossibleRate = sqlite3_column_double(stmt, 18);


                outputCsvFile << userName << ",";
                outputCsvFile << creditScore << ",";
                outputCsvFile << monthlyIncome << ",";
                outputCsvFile << financialReserves << ",";
                outputCsvFile << debtToIncomeRatio << ",";
                outputCsvFile << loanDurationInMonths << ",";
                outputCsvFile << loanAmount << ",";
                outputCsvFile << monthlyInteresRate << ",";
                outputCsvFile << yearlyInterestRate << ",";
                outputCsvFile << lossGivenDefault << ",";
                outputCsvFile << recoveryRate << ",";
                outputCsvFile << outstandingMonthlyDebtPaymentsFromLoan << ",";
                outputCsvFile << defaultRiskScore << ",";
                outputCsvFile << loanViabilityScore << ",";
                outputCsvFile << adjustedLoanViabilityScore << ",";
                outputCsvFile << interestRateByGroup << ",";
                outputCsvFile << bestPossibleRate << ",";
                outputCsvFile << worstPossibleRate << "\n";

            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }


        outputCsvFile.close();

    }


    return errorRetrievingData;

}


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


class ManageLoanManagementInterface
{
private:
    static inline bool hasInstace = false;

public:
    ManageLoanManagementInterface()
    {
        hasInstace = true;
    }
    const bool hasInstace(){
        return hasInstace;
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

    void internalAutomatedTesting(){

    }

    void cPlusPlusBasedAnalysisTools(){

    }





};