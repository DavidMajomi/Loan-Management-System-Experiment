#pragma once

#include <mutex>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Loan.h"
#include "time.h"
#include "sqlite3.h"
#include "constants.h"


using namespace std;

std::mutex DATABASELOCKMUTEX;

int convert_to_int(string valueToConvert)
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
    int count = 0, creditScoreInteger, durationInMonthsInteger;
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
        inputFile.open(CSV_FILE_FOR_TEMP_GENERATED_DATA_FOR_DB);    // Data from here would be stored in database (data analysis on new generated data)
    }

    if (inputFile.fail())
    {
        cout << " File opening failure. " << endl;
        fileOpeningError = true;
        // exit(1);
    }
    else
    {
        // This while loop runs until end of stream or end of line.
        while (getline(inputFile, userName, ','))
        {

            getline(inputFile, creditScore, ',');
            getline(inputFile, monthlyIncome, ',');
            getline(inputFile, financialReserves, ',');
            getline(inputFile, debtToIncomeRatio, ',');
            getline(inputFile, durationInMonths, ',');
            getline(inputFile, loanAmountRequested, '\n');


            if (count > 0)
            {
                creditScoreInteger = convert_to_int(creditScore);
                monthlyIncomeDecimal = convert_to_double(monthlyIncome);
                financialReservesDecimal = convert_to_double(financialReserves);
                debtToIncomeRatioDecimal = convert_to_double(debtToIncomeRatio);
                durationInMonthsInteger = convert_to_int(durationInMonths);
                loanAmonutRequestedDeciaml = convert_to_double(loanAmountRequested);

                Loan userAccount(userName, creditScoreInteger, monthlyIncomeDecimal, financialReservesDecimal, debtToIncomeRatioDecimal, durationInMonthsInteger, loanAmonutRequestedDeciaml);

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

            if(count >= 0 && count < 10)
            {
                cout << " ALVS = " << loanAccounts[count].getFinalAdjustedLoanViabilityScore() << " Matrix based ALVS = " << loanAccounts[count].getMatrixBasedAdjustedLoanViabilityScore() << endl;

            }

        }


        outputCsvFile.close();
    }

    return fileOpeningError;
}


bool storeDataInDb(vector<Loan> loanData)
{
    char * error = 0;
    const std::lock_guard<std::mutex> lock(DATABASELOCKMUTEX);
    clock_t time;

    time = clock();

    sqlite3* db;
    int numberOfAddedLoanValues, creditScore, numMetricsToAdd, numberOFInsertions;
    int rc = sqlite3_open(DATABASE_NAME, &db);
    bool errorStoringData = false;
    char charFinalSqlInsertStatement;
    const char* sqlInsertLine;
    string stringSql = loanData[0].getSqlInsertFormat();
    const char* sql = stringSql.c_str();
    vector <string> allInsertStatements;
    string insertToSql, userName, timeOfApplication, stringFinalSqlInsertStatement, completedSqlStatement;
    double monthlyIncome, financialReserves, debtToIncomeRatio, loanDurationInMonths, loanAmount, monthlyInteresRate, 
           yearlyInterestRate, recoveryRate, outstandingMonthlyDebtPaymentsFromLoan, defaultRiskScore, loanViabilityScore,
           adjustedLoanViabilityScore, matrixBasedAdjustedLoanViabilityScore, lossGivenDefault, interestRateByGroup, bestPossibleRate, worstPossibleRate;


    numberOfAddedLoanValues = loanData.size();

    if (rc != SQLITE_OK) {
        // Handle error
        cout << "Step 1 error. 2" << endl;
        errorStoringData = true;
    }


    sqlite3_stmt* stmt;
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        // Handle error preparing the statement
        cout << "Step 2 error. 2" << endl;
        sqlite3_close(db);
        errorStoringData = true;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &error);

    if (rc != SQLITE_OK) {
        // Handle error
        cout << " Step 3 error. 2" << endl;
        cout << error << endl;
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
        // cout << loanData[count].getUserName();
        lossGivenDefault = loanData[count].getLossGivenDefault();
        recoveryRate = loanData[count].getRecoveryRate();
        outstandingMonthlyDebtPaymentsFromLoan = loanData[count].getTotalOutstandingMonthlyDebtPaymentsAfterLoan();
        defaultRiskScore = loanData[count].getDefaultRiskScore();
        loanViabilityScore = loanData[count].getLoanViabilityScore();
        adjustedLoanViabilityScore = loanData[count].getFinalAdjustedLoanViabilityScore();
        matrixBasedAdjustedLoanViabilityScore = loanData[count].getMatrixBasedAdjustedLoanViabilityScore();
        interestRateByGroup = loanData[count].getInterestRateByGroup();
        bestPossibleRate = loanData[count].getBestPossibleRate();
        worstPossibleRate = loanData[count].getWorstPossibleRate();
        timeOfApplication = loanData[count].getTimeOfApplication(); 
        // cout << loanData[count].getTimeOfApplication() << endl;

        if(count >= 1)
        {
            if(count < 10)
            {
                cout << " ALVS = " << loanData[count].getFinalAdjustedLoanViabilityScore() << " Matrix based ALVS = " << loanData[count].getMatrixBasedAdjustedLoanViabilityScore();
                cout << endl;
  
            }

        }

        insertToSql = loanData[count].getInsertStatementWithData();
        // cout << insertToSql;

        allInsertStatements.push_back(insertToSql);

    }

    numberOFInsertions = allInsertStatements.size();

    for(int count = 0; count < numberOFInsertions; count++)
    {
        completedSqlStatement = completedSqlStatement + allInsertStatements[count];
    }


    // cout << " This is completed statement: " << endl << completedSqlStatement << endl;

    sqlInsertLine = completedSqlStatement.c_str();
    sql = sqlInsertLine;

    rc = sqlite3_exec(db, sql, 0, 0, &error);

    if (rc != SQLITE_OK) {
        // Handle error
        cout << " Step 4 error.  Sql statement error in store generated data function." << endl;
        cout << error << endl;
        sqlite3_close(db);
        errorStoringData = true;
    }


    sqlite3_finalize(stmt);
    sqlite3_close(db);

    time = clock() - time;

    int timeInt = int(time);

    double timeInSeconds = double(time) / 1000;

    cout << "time taken = " <<  timeInt << " millisecond(s), which is equal to " << timeInSeconds << " seconds" << endl;

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
           adjustedLoanViabilityScore, matrixBasedAdjustedLoanViabilityScore, lossGivenDefault, interestRateByGroup, bestPossibleRate, worstPossibleRate;
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
            outputCsvFile << "default_risk_score,Loan_Viability_Score,Adjusted_Loan_viability_Score,matrix_based_adjusted_loan_viability_score,interest_rate_by_group,best_possible_rate,worst_possible_rate" << endl;

            while (sqlite3_step(stmt) == SQLITE_ROW) {
                // loanId = sqlite3_column_int(stmt, 0);
                const unsigned char* userName = sqlite3_column_text(stmt, 1);
                creditScore = sqlite3_column_int(stmt, 3);
                monthlyIncome = sqlite3_column_double(stmt, 4);
                financialReserves = sqlite3_column_double(stmt, 5);
                debtToIncomeRatio = sqlite3_column_double(stmt, 6);
                loanDurationInMonths = sqlite3_column_double(stmt, 7);
                loanAmount = sqlite3_column_double(stmt, 8);
                monthlyInteresRate = sqlite3_column_double(stmt, 9);
                yearlyInterestRate = sqlite3_column_double(stmt, 10);
                lossGivenDefault = sqlite3_column_double(stmt, 11);
                recoveryRate = sqlite3_column_double(stmt, 12);
                outstandingMonthlyDebtPaymentsFromLoan = sqlite3_column_double(stmt, 13);
                defaultRiskScore = sqlite3_column_double(stmt, 14);
                loanViabilityScore = sqlite3_column_double(stmt, 15);
                adjustedLoanViabilityScore = sqlite3_column_double(stmt, 16);
                matrixBasedAdjustedLoanViabilityScore = sqlite3_column_double(stmt, 17);
                interestRateByGroup = sqlite3_column_double(stmt, 18);
                bestPossibleRate = sqlite3_column_double(stmt, 19);
                worstPossibleRate = sqlite3_column_double(stmt, 20);


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
                outputCsvFile << matrixBasedAdjustedLoanViabilityScore << ",";
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


// Use time.h here to track insertion speeds to track which method of insertion is better between this and sqlite3 transactions
bool storeDataInDbUsingSingleTransaction(vector<Loan> loanData)
{
    const std::lock_guard<std::mutex> lock(DATABASELOCKMUTEX);
    clock_t time;

    time = clock();

    sqlite3* db;
    int numberOfAddedLoanValues, creditScore, numMetricsToAdd, numberOFInsertions;
    int rc = sqlite3_open(DATABASE_NAME, &db);
    bool errorStoringData = false;
    char charFinalSqlInsertStatement;
    const char* sqlInsertLine;
    string stringSql = "BEGIN TRANSACTION; " + loanData[0].getSqlInsertFormat();
    const char* sql = stringSql.c_str();
    vector <string> allInsertStatements;
    string insertToSql, userName, stringFinalSqlInsertStatement, completedSqlStatement;
    double monthlyIncome, financialReserves, debtToIncomeRatio, loanDurationInMonths, loanAmount, monthlyInteresRate, 
           yearlyInterestRate, recoveryRate, outstandingMonthlyDebtPaymentsFromLoan, defaultRiskScore, loanViabilityScore,
           adjustedLoanViabilityScore, lossGivenDefault, interestRateByGroup, bestPossibleRate, worstPossibleRate;
    sqlite3_stmt* stmt;


    numberOfAddedLoanValues = loanData.size();

    if(rc != SQLITE_OK) {
        // Handle error
        //cout << "Step 1 error. 2" << endl;
        errorStoringData = true;
    }


    
    
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
        // DISPLAY << loanData[count].getUserName();
        lossGivenDefault = loanData[count].getLossGivenDefault();
        recoveryRate = loanData[count].getRecoveryRate();
        outstandingMonthlyDebtPaymentsFromLoan = loanData[count].getTotalOutstandingMonthlyDebtPaymentsAfterLoan();
        defaultRiskScore = loanData[count].getDefaultRiskScore();
        loanViabilityScore = loanData[count].getLoanViabilityScore();
        adjustedLoanViabilityScore = loanData[count].getFinalAdjustedLoanViabilityScore();
        interestRateByGroup = loanData[count].getInterestRateByGroup();
        bestPossibleRate = loanData[count].getBestPossibleRate();
        worstPossibleRate = loanData[count].getWorstPossibleRate();


        // stringFinalSqlInsertStatement = "'" + userName + "',";
        // stringFinalSqlInsertStatement = stringFinalSqlInsertStatement + to_string(creditScore) + "," + to_string(monthlyIncome) + "," + to_string(financialReserves) + "," + to_string(debtToIncomeRatio) + "," 
        //                                 + to_string(loanDurationInMonths) + "," +  to_string(loanAmount) + "," + to_string(monthlyInteresRate) + "," + to_string(yearlyInterestRate) + "," + to_string(lossGivenDefault) + "," 
        //                                 + to_string(recoveryRate) + "," + to_string(outstandingMonthlyDebtPaymentsFromLoan) + "," +  to_string(defaultRiskScore) + "," + to_string(loanViabilityScore) + "," 
        //                                 + to_string(adjustedLoanViabilityScore) + "," + to_string(interestRateByGroup) + "," + to_string(bestPossibleRate) + ","
        //                                 + to_string(worstPossibleRate);

        // cout << stringFinalSqlInsertStatement << endl;

        insertToSql = loanData[count].getInsertStatementWithData();
        // cout << insertToSql;

        allInsertStatements.push_back(insertToSql);
    }

    numberOFInsertions = allInsertStatements.size();

    for(int count = 0; count < numberOFInsertions; count++)
    {
        completedSqlStatement = completedSqlStatement + allInsertStatements[count];
    }


    completedSqlStatement = completedSqlStatement + "COMMIT;";
    // cout << " This is completed statement: " << endl << completedSqlStatement << endl;

    sqlInsertLine = completedSqlStatement.c_str();
    sql = sqlInsertLine;

    rc = sqlite3_exec(db, sql, 0, 0, 0);

    if (rc != SQLITE_OK) {
        // Handle error
        cout << " Step 4 error.  Sql statement error in store generated data function." << endl;
        sqlite3_close(db);
        errorStoringData = true;
    }


    sqlite3_finalize(stmt);
    sqlite3_close(db);

    time = clock() - time;

    int timeInt = int(time);

    double timeInSeconds = double(time) / 1000;

    cout << "time taken for transaction = " <<  timeInt << " millisecond(s), which is equal to " << timeInSeconds << " seconds" << endl;

    return errorStoringData;
}

