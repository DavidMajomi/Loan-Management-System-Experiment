// #ifndef LOANMANAGEMENTSYSTEMFORSERVER_H_INCLUDED
// #define LOANMANAGEMENTSYSTEMFORSERVER_H_INCLUDED
#pragma once


// #include "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\sqlite3.h"
#include "sqlite3.h"
#include "constants.h"
#include "Loan.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


// class Loan
// {
// private:
//     unsigned short int creditScore, duration;
//     string userName;
//     double loanAmount, finalMonthlyInterestRate, monthlyIncome, financialReserves, debtToIncomeRatio, recoveryRate, monthlyDebtPaymentsFromLoan, outstandingMonthlyDebtPaymentsPriorToLoan,
//            totalMonthlyDebtPaymentsAfterLoan, lossGivenDefault, defaultRiskScore, loanViabilityScore, finalAdjustedViabilityScore, normalizedCreditScore, normalizedmonthlyIncome, normalizedLoanAmount,
//            normalizedInterest, normalizedDuration, normalizedFinancialReserves;


//     double normalizeScore(double rawScore, double maxScore, double minScore);

//     double calculateDefaultRisk ();  // function not needed now since calc interest rate is not complete
    
//     void simple_set_credit_metrics();

//     void set_monthly_debt_payments ()
//     {
//         monthlyDebtPaymentsFromLoan = loanAmount / duration;
//         outstandingMonthlyDebtPaymentsPriorToLoan = monthlyIncome * debtToIncomeRatio;
//         totalMonthlyDebtPaymentsAfterLoan = outstandingMonthlyDebtPaymentsPriorToLoan + monthlyDebtPaymentsFromLoan;
//     }

// public:
//     static double normalizeScoreOutsideClass(double rawScore, double maxScore, double minScore);
//     double adjustLoanViabiltyScore (double rawLoanViabilityScore);
//     Loan(int values)
//     {

//     }
//     void setCreditScore (int creditScoreValue)
//     {
//         creditScore = creditScoreValue;
//     }
//     void setUserName (string name)
//     {
//         userName = name;
//     }
//     void setLoanAmount (double amount)
//     {
//         loanAmount = amount;
//     }
//     void setFinalMonthlyInterestRate ()
//     {
//         double baseRate;

//         set_monthly_debt_payments();
//         baseRate = BASE_YEARLY_INTEREST_RATE_FOR_CALCULATION;

//         if (creditScore >= 800)
//         {
//             baseRate = baseRate + 2;

//         }
//         else if (creditScore >= 740 && creditScore < 800)
//         {
//             baseRate = baseRate + 6;
//         }
//         else if (creditScore >= 670 && creditScore <= 739)
//         {
//             baseRate = baseRate + 9;
//         }
//         else if (creditScore >=580 && creditScore <= 669)
//         {
//            baseRate = baseRate + 12;
//         }
//         else if (creditScore >= 300 && creditScore <= 579)
//         {
//             baseRate = baseRate + 20;
//         }


//         // if (creditScore >= 800)
//         // {
//         //     baseRate = baseRate + 2;

//         // }
//         // else if (creditScore >= 740 && creditScore < 800)
//         // {
//         //     baseRate = baseRate + 6;
//         // }
//         // else if (creditScore >= 670 && creditScore <= 739)
//         // {
//         //     baseRate = baseRate + 9;
//         // }
//         // else if (creditScore >=580 && creditScore <= 669)
//         // {
//         //    baseRate = baseRate + 12;
//         // }
//         // else if (creditScore >= 300 && creditScore <= 579)
//         // {
//         //     baseRate = baseRate + 20;
//         // }

//         finalMonthlyInterestRate = baseRate / 12;

//     }
//     double calculateInterestForDefaultRisk (double baseRate)
//     {
//         if (creditScore >= 800)
//         {
//             baseRate = baseRate + 2;

//         }
//         else if (creditScore >= 740 && creditScore < 800)
//         {
//             baseRate = baseRate + 6;
//         }
//         else if (creditScore >= 670 && creditScore <= 739)
//         {
//             baseRate = baseRate + 9;
//         }
//         else if (creditScore >=580 && creditScore <= 669)
//         {
//            baseRate = baseRate + 12;
//         }
//         else if (creditScore >= 300 && creditScore <= 579)
//         {
//             baseRate = baseRate + 20;
//         }

//         return baseRate / 12;

//     }
//     void setLoanDuration(int loanDuration)
//     {
//         duration = loanDuration;
//     }
//     void setMonthlyIncome (double income)
//     {
//         monthlyIncome = income;
//     }
//     void setFinancialReserves(double financialReserveValues)
//     {
//         financialReserves = financialReserveValues;
//     }
//     void setDebtToIncomeRatio (double debtToIncomeRatioValue)
//     {
//         debtToIncomeRatio = debtToIncomeRatioValue; // outstanding dti prior to loan
//     }
//     void computeCreditData ()
//     {
//         simple_set_credit_metrics();
//     }
//     string getUserName() const
//     {
//         return userName;
//     }
//     int getCreditScore () const
//     {
//         return creditScore;
//     }
//     double getMonthlyIncome () const
//     {
//         return monthlyIncome;
//     }
//     double getFinancialReserves () const
//     {
//         return financialReserves;
//     }
//     double getDebtToIncomeRatio() const
//     {
//         return debtToIncomeRatio;
//     }
//     int getDurationInMonths() const
//     {
//         return duration;
//     }
//     double getLoanAmount() const
//     {
//         return loanAmount;
//     }
//     double getMonthlyInterestRate() const
//     {
//         return finalMonthlyInterestRate;
//     }
//     double getYearlyInterestRate () const
//     {
//         return finalMonthlyInterestRate * 12;
//     }
//     double getLossGivenDefault() const
//     {
//         return lossGivenDefault;
//     }
//     double getRecoveryRate () const
//     {
//         return recoveryRate;
//     }
//     double getTotalOutstandingMonthlyDebtPaymentsAfterLoan () const
//     {
//         return totalMonthlyDebtPaymentsAfterLoan;
//     }
//     double getDefaultRiskScore () const
//     {
//         return defaultRiskScore;
//     }
//     double getLoanViabilityScore () const
//     {
//         return loanViabilityScore;
//     }
//     double getFinalAdjustedLoanViabilityScore() const
//     {
//         return finalAdjustedViabilityScore;
//     }
// };


// double Loan::normalizeScore(double rawScore, double maxScore, double minScore)
// {
//     unsigned short int maxScaleValue = 1, minScaleValue = 0;
//     double normalizedScore;

//     normalizedScore = ((rawScore - minScore) / (maxScore - minScore)) * (maxScaleValue - minScaleValue) + (minScaleValue);

//     return normalizedScore;
// }


// double Loan::normalizeScoreOutsideClass(double rawScore, double maxScore, double minScore)
// {
//     double normalizedScore, maxScaleValue = 1, minScaleValue = 0;

//     normalizedScore = ((rawScore - minScore) / (maxScore - minScore)) * (maxScaleValue - minScaleValue) + (minScaleValue);

//     return normalizedScore;
// }


// double calculateBestCreditMetrics()
// {
//     double loanViabilityScore, normalizedCreditScore, normalizedmonthlyIncome, normalizedLoanAmount, normalizedInterest, normalizedDuration, normalizedFinancialReserves;

//     normalizedCreditScore =  Loan::normalizeScoreOutsideClass(MAX_CREDIT_SCORE, MAX_CREDIT_SCORE, MIN_CREDIT_SCORE);
//     normalizedDuration = Loan::normalizeScoreOutsideClass(MAX_LOAN_DURATION, MAX_LOAN_DURATION, MIN_LOAN_DURATION);
//     normalizedFinancialReserves = Loan::normalizeScoreOutsideClass(MAX_FINANCIAL_RESERVES, MAX_FINANCIAL_RESERVES, MIN_FINANCIAL_RESERVES);
//     normalizedInterest = Loan::normalizeScoreOutsideClass(BEST_FINAL_MONTHLY_INTEREST_RATE, MAX_INTEREST_RATE, MIN_INTEREST_RATE);
//     normalizedmonthlyIncome = Loan::normalizeScoreOutsideClass(MAX_MONTHLY_INCOME, MAX_MONTHLY_INCOME, MIN_MONTHLY_INCOME);
//     normalizedLoanAmount = Loan::normalizeScoreOutsideClass(MIN_LOAN_AMOUNT, MAX_LOAN_AMOUNT, MIN_LOAN_AMOUNT);

//     loanViabilityScore = (normalizedCreditScore * CREDIT_SCORE_WEIGHT) + (normalizedmonthlyIncome * MONTHLY_INCOME_WEIGHT) + (BEST_DEBT_TO_INCOME_RATIO * DEBT_TO_INCOME_RATIO_WEIGHT)  
//                             + (normalizedLoanAmount * LOAN_AMOUNT_WEIGHT) + (normalizedDuration * LOAN_DURATION_WEIGHT)+ (normalizedInterest * INTEREST_RATE_WEIGHT) 
//                             + (BEST_LOSS_GIVEN_DEFAULT * LOSS_GIVEN_DEFAULT_WEIGHT) + (normalizedFinancialReserves * FINANCIAL_RESERVES_WEIGHT) + (BEST_DEFAULT_RISK_SCORE * DEFAULT_RISK_SCORE_WEIGHT);

//     // //cout << " Best loan viability score = " << loanViabilityScore << endl;

//     return loanViabilityScore;
// }


// // Need to review the logic here as well as finding a way to put it in the class we will see how it goes
// double calculateWorstCreditMetrics()
// {
//     double loanViabilityScore, normalizedCreditScore, normalizedmonthlyIncome, normalizedLoanAmount, normalizedInterest, normalizedDuration, normalizedFinancialReserves;

//     normalizedCreditScore =  Loan::normalizeScoreOutsideClass(MIN_CREDIT_SCORE, MAX_CREDIT_SCORE, MIN_CREDIT_SCORE);
//     normalizedDuration = Loan::normalizeScoreOutsideClass(MIN_LOAN_DURATION, MAX_LOAN_DURATION, MIN_LOAN_DURATION);
//     normalizedFinancialReserves = Loan::normalizeScoreOutsideClass(MIN_FINANCIAL_RESERVES, MAX_FINANCIAL_RESERVES, MIN_FINANCIAL_RESERVES);
//     normalizedInterest = Loan::normalizeScoreOutsideClass(WORST_FINAL_MONTHLY_INTEREST_RATE, MAX_INTEREST_RATE, MIN_INTEREST_RATE);
//     normalizedmonthlyIncome = Loan::normalizeScoreOutsideClass(MIN_MONTHLY_INCOME, MAX_MONTHLY_INCOME, MIN_MONTHLY_INCOME);
//     normalizedLoanAmount = Loan::normalizeScoreOutsideClass(MAX_LOAN_AMOUNT, MAX_LOAN_AMOUNT, MIN_LOAN_AMOUNT);

//     loanViabilityScore = (normalizedCreditScore * CREDIT_SCORE_WEIGHT) + (normalizedmonthlyIncome * MONTHLY_INCOME_WEIGHT) + (WORST_DEBT_TO_INCOME_RATIO * DEBT_TO_INCOME_RATIO_WEIGHT)  + (normalizedLoanAmount * LOAN_AMOUNT_WEIGHT) + (normalizedDuration * LOAN_DURATION_WEIGHT)
//                             + (normalizedInterest * INTEREST_RATE_WEIGHT) + (WORST_LOSS_GIVEN_DEFAULT * LOSS_GIVEN_DEFAULT_WEIGHT) + (normalizedFinancialReserves * FINANCIAL_RESERVES_WEIGHT) + (WORST_DEFAULT_RISK_SCORE * DEFAULT_RISK_SCORE_WEIGHT);

//     // //cout << " Worst loan viability score = " << loanViabilityScore << endl;

//     return loanViabilityScore;
// }


// double Loan::adjustLoanViabiltyScore (double rawLoanViabilityScore)
// {
//     unsigned short int maxScaleValue = 100, minScaleValue = 0;
//     double adjustedViabilityScore, bestLoanViabilityScore, worstLoanViabilityScore;

//     bestLoanViabilityScore = calculateBestCreditMetrics();
//     worstLoanViabilityScore = calculateWorstCreditMetrics();
//     adjustedViabilityScore = (((rawLoanViabilityScore - worstLoanViabilityScore) / (bestLoanViabilityScore - worstLoanViabilityScore)) * (maxScaleValue - minScaleValue)) + (minScaleValue);

//     return adjustedViabilityScore;
// }


// double Loan::calculateDefaultRisk ()  // function not needed now since calc interest rate is not complete
// {
//     //int  creditScore = 850;
//     //double lossGivenDefault = 0, duration = 19, loanAmount = 200000, bestRecoveryRate = 1, calculatedDefaultRisk;
//     double bestRate, finalInterestRate, calculatedDefaultRisk, bestMonthlyRate;

//     // bestMonthlyRate = BASE_INTEREST_RATE_FOR_CALCULATION / 12;
//     finalInterestRate = calculateInterestForDefaultRisk(BEST_MONTHLY_INTEREST_RATE_FOR_CALCULATION);      // since at best credit rate, base rate is the automatic rate
//     calculatedDefaultRisk = finalInterestRate - BEST_MONTHLY_INTEREST_RATE_FOR_CALCULATION;

//     return calculatedDefaultRisk;
// }


// // When minimizing inefficiencies in this programme, initialize the credit metrics instead of assignning them values after decleration
// void Loan::simple_set_credit_metrics ()
// {
//     normalizedCreditScore =  normalizeScore(creditScore, MAX_CREDIT_SCORE, MIN_CREDIT_SCORE);
//     normalizedDuration = normalizeScore(duration, MAX_LOAN_DURATION, MIN_LOAN_DURATION);
//     normalizedFinancialReserves = normalizeScore(financialReserves, MAX_FINANCIAL_RESERVES, MIN_FINANCIAL_RESERVES);
//     normalizedInterest = normalizeScore(finalMonthlyInterestRate, MAX_INTEREST_RATE, MIN_INTEREST_RATE);
//     normalizedmonthlyIncome = normalizeScore(monthlyIncome, MAX_MONTHLY_INCOME, MIN_MONTHLY_INCOME);
//     normalizedLoanAmount = normalizeScore(loanAmount, MAX_LOAN_AMOUNT, MIN_LOAN_AMOUNT);

//     lossGivenDefault = (loanAmount - financialReserves) / loanAmount; // SOURCE = WIKIPEDIA
//     recoveryRate = 1 - lossGivenDefault;
//     defaultRiskScore = calculateDefaultRisk();

//     loanViabilityScore = (normalizedCreditScore * CREDIT_SCORE_WEIGHT) + (normalizedmonthlyIncome * MONTHLY_INCOME_WEIGHT) + (debtToIncomeRatio * DEBT_TO_INCOME_RATIO_WEIGHT)  + (normalizedLoanAmount * LOAN_AMOUNT_WEIGHT) + (normalizedDuration * LOAN_DURATION_WEIGHT)
//                         + (normalizedInterest * INTEREST_RATE_WEIGHT) + (lossGivenDefault * LOSS_GIVEN_DEFAULT_WEIGHT) + (normalizedFinancialReserves * FINANCIAL_RESERVES_WEIGHT) + (defaultRiskScore * DEFAULT_RISK_SCORE_WEIGHT);

//     finalAdjustedViabilityScore = adjustLoanViabiltyScore(loanViabilityScore);

//     // //cout << " This is adjusted Loan viability score: " << finalAdjustedViabilityScore << endl;

    
// }


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
        inputFile.open("allGeneratedLoanData.csv"); // Based only on historical generated data, no new generated data here
    }
    else if (devMenuResponse == 1)
    {
        // This contains freshly generated data from python
        inputFile.open("tempGeneratedLoanDataForDbStorage.csv");    // Data from here would be stored in database (data analysis on new generated data)
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
                userAccount.setFinalMonthlyInterestRate();
                userAccount.computeCreditData();

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

    outputCsvFile.open("processedLoanData.csv");


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

void createDatabaseToAddUserLoanData(vector<Loan>& loanAccountsToAdd) 
{
    int numberOfAddedLoanValues, creditScore, numMetricsToAdd;
    char charFinalSqlInsertStatement;
    const char* sqlInsertLine;
    const char* sql = "CREATE TABLE IF NOT EXISTS users (Loan_id INTEGER PRIMARY KEY, name TEXT, credit_score INTEGER, monthly_income REAL, financial_reserves REAL, debt_to_income_ratio REAL,"
                      " loan_duration REAL, requested_loan_amount REAL, monthly_interest_rate REAL, yearly_interest_rate REAL, loss_given_default REAL, recovery_rate REAL,"
                      " outstanding_monthly_debt_paymentd_from_loan REAL, default_risk_score REAL, loan_viability_score REAL, adjusted_loan_viability_score REAL)";
    vector <string> valsToInsert;
    string insertToSql, userName, stringFinalSqlInsertStatement, stringCreditScore, stringMonthlyIncome, stringFinancialReserves, stringDebtToIncomeRatio, stringLoanDurationInMonths, 
           stringLoanAmount, stringMonthlyInteresRate, stringyearlyInterestRate, stringrecoveryRate, stringOutstandingMonthlyDebtPaymentsFromLoan, stringDefaultRiskScore, stringLoanViabilityScore,
           stringAdjustedLoanViabilityScore, stringLossGivenDefault;
    double monthlyIncome, financialReserves, debtToIncomeRatio, loanDurationInMonths, loanAmount, monthlyInteresRate, 
           yearlyInterestRate, recoveryRate, outstandingMonthlyDebtPaymentsFromLoan, defaultRiskScore, loanViabilityScore,
           adjustedLoanViabilityScore, lossGivenDefault;
    sqlite3* db;
    int rc = sqlite3_open(DATABASE_NAME, &db);

    numberOfAddedLoanValues = loanAccountsToAdd.size();



    if (rc != SQLITE_OK) {
        // Handle error
        //cout << "Step 1 error." << endl;
        exit(1);
    }


    sqlite3_stmt* stmt;
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        // Handle error preparing the statement
        //cout << "Step 2 error." << endl;
        sqlite3_close(db);
        exit(1);
    }
    rc = sqlite3_exec(db, sql, 0, 0, 0);

    if (rc != SQLITE_OK) {
        // Handle error
        //cout << " Step 3 error. " << endl;
        sqlite3_close(db);
        exit (1);
    }


    for (int count = 0; count < numberOfAddedLoanValues; count++)
    {
        creditScore = loanAccountsToAdd[count].getCreditScore();
        monthlyIncome = loanAccountsToAdd[count].getMonthlyIncome() ;
        financialReserves = loanAccountsToAdd[count].getFinancialReserves() ;
        debtToIncomeRatio = loanAccountsToAdd[count].getDebtToIncomeRatio() ;
        loanDurationInMonths = loanAccountsToAdd[count].getDurationInMonths() ;
        loanAmount = loanAccountsToAdd[count].getLoanAmount();
        monthlyInteresRate = loanAccountsToAdd[count].getMonthlyInterestRate();
        yearlyInterestRate = loanAccountsToAdd[count].getYearlyInterestRate();
        userName =  loanAccountsToAdd[count].getUserName();
        lossGivenDefault = loanAccountsToAdd[count].getLossGivenDefault();
        recoveryRate = loanAccountsToAdd[count].getRecoveryRate();
        outstandingMonthlyDebtPaymentsFromLoan = loanAccountsToAdd[count].getTotalOutstandingMonthlyDebtPaymentsAfterLoan();
        defaultRiskScore = loanAccountsToAdd[count].getDefaultRiskScore();
        loanViabilityScore = loanAccountsToAdd[count].getLoanViabilityScore();
        adjustedLoanViabilityScore = loanAccountsToAdd[count].getFinalAdjustedLoanViabilityScore();
        
        // //cout << outstandingMonthlyDebtPaymentsFromLoan << endl;

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


        insertToSql = "INSERT INTO users (name , credit_score , monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rate, yearly_interest_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_paymentd_from_loan, default_risk_score, loan_viability_score, adjusted_loan_viability_score) VALUES (" + stringFinalSqlInsertStatement + ")"; 


        // //cout << insertToSql;

        sqlInsertLine = insertToSql.c_str();
        sql = sqlInsertLine;

        rc = sqlite3_exec(db, sql, 0, 0, 0);

        if (rc != SQLITE_OK) {
            // Handle error
            //cout << " Step 4 error. " << endl;
            sqlite3_close(db);
            exit (1);
        }

        valsToInsert.clear();

    }


    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // //cout << "The base" << endl;
    // //cout << " New values for testing python execution." << endl;

}


void storeGeneratedDataInDatabase(vector<Loan>& loanAccounts) 
{
    sqlite3* db;
    int numberOfAddedLoanValues, creditScore, numMetricsToAdd;
    int rc = sqlite3_open(DATABASE_NAME, &db);
    char charFinalSqlInsertStatement;
    const char* sqlInsertLine;
    const char* sql = "CREATE TABLE IF NOT EXISTS users (Loan_id INTEGER PRIMARY KEY, name TEXT, credit_score INTEGER, monthly_income REAL, financial_reserves REAL, debt_to_income_ratio REAL,"
                      " loan_duration REAL, requested_loan_amount REAL, monthly_interest_rate REAL, yearly_interest_rate REAL, loss_given_default REAL, recovery_rate REAL,"
                      " outstanding_monthly_debt_paymentd_from_loan REAL, default_risk_score REAL, loan_viability_score REAL, adjusted_loan_viability_score REAL)";
    vector <string> valsToInsert;
    string insertToSql, userName, stringFinalSqlInsertStatement, stringCreditScore, stringMonthlyIncome, stringFinancialReserves, stringDebtToIncomeRatio, stringLoanDurationInMonths, stringLoanAmount, stringMonthlyInteresRate, 
           stringyearlyInterestRate, stringrecoveryRate, stringOutstandingMonthlyDebtPaymentsFromLoan, stringDefaultRiskScore, stringLoanViabilityScore,
           stringAdjustedLoanViabilityScore, stringLossGivenDefault;
    double monthlyIncome, financialReserves, debtToIncomeRatio, loanDurationInMonths, loanAmount, monthlyInteresRate, 
           yearlyInterestRate, recoveryRate, outstandingMonthlyDebtPaymentsFromLoan, defaultRiskScore, loanViabilityScore,
           adjustedLoanViabilityScore, lossGivenDefault;


    numberOfAddedLoanValues = loanAccounts.size();

    if (rc != SQLITE_OK) {
        // Handle error
        //cout << "Step 1 error. 2" << endl;
        exit(1);
    }


    sqlite3_stmt* stmt;
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        // Handle error preparing the statement
        //cout << "Step 2 error. 2" << endl;
        sqlite3_close(db);
        exit(1);
    }
    rc = sqlite3_exec(db, sql, 0, 0, 0);

    if (rc != SQLITE_OK) {
        // Handle error
        //cout << " Step 3 error. 2" << endl;
        sqlite3_close(db);
        exit (1);
    }

    for (int count = 0; count < numberOfAddedLoanValues; count++)
    {
        creditScore = loanAccounts[count].getCreditScore();
        monthlyIncome = loanAccounts[count].getMonthlyIncome() ;
        financialReserves = loanAccounts[count].getFinancialReserves() ;
        debtToIncomeRatio = loanAccounts[count].getDebtToIncomeRatio() ;
        loanDurationInMonths = loanAccounts[count].getDurationInMonths() ;
        loanAmount = loanAccounts[count].getLoanAmount();
        monthlyInteresRate = loanAccounts[count].getMonthlyInterestRate();
        yearlyInterestRate = loanAccounts[count].getYearlyInterestRate();
        userName =  loanAccounts[count].getUserName();
        lossGivenDefault = loanAccounts[count].getLossGivenDefault();
        recoveryRate = loanAccounts[count].getRecoveryRate();
        outstandingMonthlyDebtPaymentsFromLoan = loanAccounts[count].getTotalOutstandingMonthlyDebtPaymentsAfterLoan();
        defaultRiskScore = loanAccounts[count].getDefaultRiskScore();
        loanViabilityScore = loanAccounts[count].getLoanViabilityScore();
        adjustedLoanViabilityScore = loanAccounts[count].getFinalAdjustedLoanViabilityScore();

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
                      " adjusted_loan_viability_score) VALUES (" + stringFinalSqlInsertStatement + ")"; 

        // //cout << insertToSql;

        sqlInsertLine = insertToSql.c_str();
        sql = sqlInsertLine;

        rc = sqlite3_exec(db, sql, 0, 0, 0);

        if (rc != SQLITE_OK) {
            // Handle error
            //cout << " Step 4 error. 2" << endl;
            sqlite3_close(db);
            exit (1);
        }

        valsToInsert.clear();
    }


    sqlite3_finalize(stmt);
    sqlite3_close(db);

}


bool retrieveAllUserDataFromDatabase(ofstream& outputCsvFile) 
{
    int creditScore, loanId;
    bool errorRetrievingData = false;
    const char* sql = "SELECT * FROM users";
    double monthlyIncome, financialReserves, debtToIncomeRatio, loanDurationInMonths, loanAmount, monthlyInteresRate, 
           yearlyInterestRate, recoveryRate, outstandingMonthlyDebtPaymentsFromLoan, defaultRiskScore, loanViabilityScore,
           adjustedLoanViabilityScore, lossGivenDefault;
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

        outputCsvFile.open("analyzedDataFromDb.csv");

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
            outputCsvFile << "default_risk_score,Loan_Viability_Score,Adjusted_Loan_viability_Score" << endl;

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
                outputCsvFile << adjustedLoanViabilityScore << "\n";
                // outputCsvFile << loanDurationInMonths << ",";
                // outputCsvFile << loanDurationInMonths << "\n";

                

                // //cout << " This is id " << loanId << endl;
                // //cout << " This is name " << userName << endl;
                // //cout << " This is credit score" << creditScore << endl;

            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }


        outputCsvFile.close();

    }


    return errorRetrievingData;

}

// #endif // LOANMANAGEMENTSYSTEMFORSERVER_H_INCLUDED
