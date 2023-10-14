// #ifndef CONSTANTS_H_INCLUDED
// #define CONSTANTS_H_INCLUDED
#pragma once

#include <string>
// Next Task: Modify the weights to represent the removed interest rate weight
using namespace std;

// FILE NAMES
const char* DATABASE_NAME = "bam_bam.db";       // Has to be a constant char to be compatibe with sqlite
const string CSV_FILE_FOR_ALL_GENERATED_LOAN_DATA = "allGeneratedLoanData.csv";     // Based only on historical generated data, no new generated data here
const string OUTPUT_CSV_FILE_FOR_PROCESSED_DATA = "processedLoanData.csv";
const string CSV_FILE_FOR_STORING_ANALAYZED_DB_VALUES = "analyzedDataFromDb.csv";
const string CSV_FILE_FOR_TEMP_GENERTED_DATA_FOR_BD = "tempGeneratedLoanDataForDbStorage.csv";

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
const double MAX_INTEREST_RATE = 2.08;
const double MIN_INTEREST_RATE = 0.58;
const double MAX_FINANCIAL_RESERVES = 50000;
const double MIN_FINANCIAL_RESERVES = 10000;
const double MAX_LOAN_AMOUNT = 50000;
const double MIN_LOAN_AMOUNT = 500;

const double BEST_DEFAULT_RISK_SCORE = 0; 
const double BEST_LOSS_GIVEN_DEFAULT = 0;
const double BEST_DEBT_TO_INCOME_RATIO = 0;
const double BEST_FINAL_MONTHLY_INTEREST_RATE = 0.58;

const double WORST_DEFAULT_RISK_SCORE = 1;   // add this to loan viability formula
const double WORST_LOSS_GIVEN_DEFAULT = 0.8;   // possible value includes 0.2, 0.1, 1 = too high
const double WORST_DEBT_TO_INCOME_RATIO = 0.9; //
const double WORST_FINAL_MONTHLY_INTEREST_RATE = 2;   // Check the logic behind this

// #endif // CONSTANTS_H_INCLUDED
