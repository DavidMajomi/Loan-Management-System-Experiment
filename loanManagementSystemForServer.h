// #ifndef LOANMANAGEMENTSYSTEMFORSERVER_H_INCLUDED
// #define LOANMANAGEMENTSYSTEMFORSERVER_H_INCLUDED
#pragma once


#include "sqlite3.h"
#include "constants.h"
#include "Loan.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


int convert_to_int (string valueToConvert)
{
    int convertedValue = stoi(valueToConvert);

    return convertedValue;
}


double convert_to_double (string valueToConvert)
{
    double convertedValue;
    convertedValue = stod(valueToConvert);

    return convertedValue;
}


bool readGeneratedData (ifstream& inputFile, vector <Loan>& loanAccounts, unsigned short int devMenuResponse)
{
    int count = 0, values, creditScoreInteger, durationInMonthsInteger;
    bool fileOpeningError = false;
    double monthlyIncomeDecimal, financialReservesDecimal, debtToIncomeRatioDecimal, loanAmonutRequestedDeciaml;
    string userName, creditScore, monthlyIncome, financialReserves, debtToIncomeRatio, durationInMonths, loanAmountRequested;


    if (devMenuResponse == 2)
    {
        // //cout << " 2" << endl;
        inputFile.open(CSV_FILE_FOR_ALL_GENERATED_LOAN_DATA); // Based only on historical generated data, no new generated data here
    }
    else if (devMenuResponse == 1)
    {
        // This contains freshly generated data from python
        inputFile.open(CSV_FILE_FOR_TEMP_GENERTED_DATA_FOR_BD);    // Data from here would be stored in database (data analysis on new generated data)
    }

    if (inputFile.fail())
    {
        //cout << " File opening failure. " << endl;
        fileOpeningError = true;
    }
    else
    {

        while (getline(inputFile, userName, ','))
        {
            values = count;

            getline(inputFile, creditScore, ',');
            getline(inputFile, monthlyIncome, ',');
            getline(inputFile, financialReserves, ',');
            getline(inputFile, debtToIncomeRatio, ',');
            getline(inputFile, durationInMonths, ',');
            getline(inputFile, loanAmountRequested, '\n');


            if (count > 0)
            {
                values = count - 1;
                Loan userAccount(values);

                creditScoreInteger = convert_to_int(creditScore);
                monthlyIncomeDecimal = convert_to_double(monthlyIncome);
                financialReservesDecimal = convert_to_double(financialReserves);
                debtToIncomeRatioDecimal = convert_to_double(debtToIncomeRatio);
                durationInMonthsInteger = convert_to_int(durationInMonths);
                loanAmonutRequestedDeciaml = convert_to_double(loanAmountRequested);

                userAccount.setUserName(userName);
                userAccount.setCreditScore(creditScoreInteger);
                userAccount.setMonthlyIncome(monthlyIncomeDecimal);
                userAccount.setFinancialReserves(financialReservesDecimal);
                userAccount.setDebtToIncomeRatio(debtToIncomeRatioDecimal);
                userAccount.setLoanDuration(durationInMonthsInteger);
                userAccount.setLoanAmount(loanAmonutRequestedDeciaml);
                // userAccount.set_monthly_debt_payments();
                userAccount.computeCreditData();
                userAccount.setFinalMonthlyInterestRate();

                loanAccounts.push_back(userAccount);

            }

            count++;
        }

        inputFile.close();
    }

    
    return fileOpeningError;
}


bool outputToFile (ofstream& outputCsvFile, vector <Loan>& loanAccounts)
{
    int numLoanAccounts;
    bool fileOpeningError = false;

    outputCsvFile.open(OUTPUT_CSV_FILE_FOR_PROCESSED_DATA);


    if (outputCsvFile.fail())
    {
        //cout << " Output File Opening Error. " << endl;
        fileOpeningError = true;
    }
    else
    {
        numLoanAccounts = loanAccounts.size();
        //cout << " This is num processed values. outputFile function: " << numLoanAccounts << endl;

        outputCsvFile << "Name,credit_score,monthly_income,financial_reserves,debt_to_income_ratio,Duration_in_months,loan_amount_requested,Monthly_interest_rate,Interest_rate_over_a_year,"
                    "loss_Given_Default,Recovery_Rate,outstanding_Monthly_Debt_Payments,";
        outputCsvFile << "default_risk_score,Loan_Viability_Score,Adjusted_Loan_viability_Score" << endl;

        for (int count = 0; count < numLoanAccounts; count++)
        {
            outputCsvFile << loanAccounts[count].getUserName() << ",";
            outputCsvFile << loanAccounts[count].getCreditScore() << ",";
            outputCsvFile << loanAccounts[count].getMonthlyIncome() << ",";
            outputCsvFile << loanAccounts[count].getFinancialReserves() << ",";
            outputCsvFile << loanAccounts[count].getDebtToIncomeRatio() << ",";
            outputCsvFile << loanAccounts[count].getDurationInMonths() << ",";
            outputCsvFile << loanAccounts[count].getLoanAmount() << ",";
            outputCsvFile << loanAccounts[count].getMonthlyInterestRate() << ",";
            outputCsvFile << loanAccounts[count].getYearlyInterestRate() << ",";
            outputCsvFile << loanAccounts[count].getLossGivenDefault() << ",";
            outputCsvFile << loanAccounts[count].getRecoveryRate() << ",";
            outputCsvFile << loanAccounts[count].getTotalOutstandingMonthlyDebtPaymentsAfterLoan() << ",";
            outputCsvFile << loanAccounts[count].getDefaultRiskScore() << ",";
            outputCsvFile << loanAccounts[count].getLoanViabilityScore() << ",";
            outputCsvFile << loanAccounts[count].getFinalAdjustedLoanViabilityScore() << "\n";
        }


        outputCsvFile.close();
    }


    return fileOpeningError;

}

// Need to review the logic here as well as finding a way to put it in the class we will see how it goes


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

        if (outputCsvFile.fail())
        {
            //cout << " Output File Opening Error. " << endl;
            errorRetrievingData = true;
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

// #endif // LOANMANAGEMENTSYSTEMFORSERVER_H_INCLUDED
