#pragma once

#include <string>
#include "Logger.h"
#include <filesystem>// cpp 17 reference https://en.cppreference.com/w/cpp/filesystem/current_paths


Logger DISPLAY;
const char ENDLINE = '\n';


namespace fs = std::filesystem;
// Next Task: Modify the weights to represent the removed interest rate weight
using namespace std;

// FILE NAMES
const string CURRENT_FULL_PATH = fs::current_path().string();
const string DATABASE_NAME_WITH_PATH = CURRENT_FULL_PATH + "\\Database files\\loans.db";       // Has to be a constant char to be compatibe with sqlite
const char* DATABASE_NAME = DATABASE_NAME_WITH_PATH.c_str();
const string CSV_FILE_FOR_ALL_GENERATED_LOAN_DATA = CURRENT_FULL_PATH + "\\Folder with Generated Data\\allGeneratedLoanData.csv";     // Based only on historical generated data, no new generated data here
const string OUTPUT_CSV_FILE_FOR_PROCESSED_DATA = CURRENT_FULL_PATH + "\\..\\Csv Files For Analysis\\processedLoanData.csv";
const string CSV_FILE_FOR_STORING_ANALAYZED_DB_VALUES = CURRENT_FULL_PATH + "\\..\\Csv Files For Analysis\\analyzedDataFromDb.csv";
const string CSV_FILE_FOR_TEMP_GENERATED_DATA_FOR_DB = CURRENT_FULL_PATH + "\\Folder with Generated Data\\tempGeneratedLoanDataForDbStorage.csv";
const string DATABASE_TABLE_WITH_INITIAL_APPLICATION = "users";

// Best Values for Different Factors
const double BEST_DEFAULT_RISK_SCORE = 0; 
const double WORST_DEFAULT_RISK_SCORE = 1;   // add this to loan viability formula

const double BEST_LOSS_GIVEN_DEFAULT = 0;
const double WORST_LOSS_GIVEN_DEFAULT = 0.8;   // possible value includes 0.2, 0.1, 1 = too high

// Worst Values for Different Factors
const double BEST_DEBT_TO_INCOME_RATIO = 0;
const double WORST_DEBT_TO_INCOME_RATIO = 0.9; //

// Maximum and minimum Factor Values
const double MIN_LOAN_AMOUNT = 500;
const double MAX_LOAN_AMOUNT = 50000;

const double MAX_FINANCIAL_RESERVES = 50000;
const double MIN_FINANCIAL_RESERVES = 10000;

const double MIN_LOAN_DURATION = 1;
const unsigned short int MAX_LOAN_DURATION = 60;

const unsigned short int MAX_CREDIT_SCORE = 850;
const unsigned short int MIN_CREDIT_SCORE = 300;

const unsigned short int MIN_MONTHLY_INCOME = 800;
const unsigned short int MAX_MONTHLY_INCOME = 12000;


// Weights of Different Factors
const double LOAN_AMOUNT_WEIGHT = 0.12;          // Works as a measure of possible profitability to some extent, but needs to be reduced
const double CREDIT_SCORE_WEIGHT = 0.30;          // Most important metric, it shows credit worthiness, while minimizing risk
const double LOAN_DURATION_WEIGHT = 0.06;        // Duration of the loan, NEED TO ADJUST THIS WEIGHT DRASTICALLY
const double MONTHLY_INCOME_WEIGHT = 0.06;        // Not as important, because DTI covers this, however, valuable to weigh customer value, POSSIBLE FORMULA IN THE FUTURE
const double FINANCIAL_RESERVES_WEIGHT = 0.08;   // All liquidable financial assets weight
const double LOSS_GIVEN_DEFAULT_WEIGHT = -0.15;   // Potential Losses when considering Financial Reserves
const double DEFAULT_RISK_SCORE_WEIGHT = -0.08;   // Risk accrued for higher returns, foregoing more secure investment options.
const double DEBT_TO_INCOME_RATIO_WEIGHT = -0.15;   // Works as a measure of the customer's ability to shoulder debt weight


const unsigned short int NUM_MONTHS_IN_YEAR = 12;

const string USERS_TABLE_COLUMN_FORMAT = " (Loan_id INTEGER PRIMARY KEY,"
                      "name TEXT,"
                      "time_of_application TEXT,"
                      "credit_score INTEGER,"
                      "monthly_income REAL,"
                      "financial_reserves REAL,"
                      "debt_to_income_ratio REAL,"
                      "loan_duration REAL,"
                      "duration_to_installment_days STRING,"
                      "duration_to_settlement_months STRING,"
                      "requested_loan_amount REAL,"
                      "monthly_interest_rate REAL,"
                      "yearly_interest_rate REAL,"
                      "loss_given_default REAL,"
                      "recovery_rate REAL,"
                      "outstanding_monthly_debt_paymentd_from_loan REAL,"
                      "outstanding_monthly_debt_payments_prior_to_loan REAL,"
                      "amount_to_pay_at_next_installment REAL,"
                      "default_risk_score REAL,"
                      "loan_viability_score REAL,"
                      "adjusted_loan_viability_score REAL,"
                      "matrix_based_adjusted_loan_viability_score REAL,"
                      "interest_rate_by_group REAL,"
                      "best_possible_yearly_rate REAL,"
                      "worst_possible_yearly_rate REAL,"
                      "final_loan_grade TEXT,"
                      "potential_profit_from_loan REAL,"
                      "calculated_best_possible_loan_viabbility_score REAL,"
                      "calculated_worst_possible_loan_viabbility_score REAL,"
                      "amount_of_current_loan_and_interests_left REAL,"
                      "loan_decision INTEGER,"
                      "loan_status TEXT,"
                      "applied_today_or_not INTEGER,"
                      "account_number INTEGER,"
                      "end_of_term_copying_done INTEGER"
                      ");";


const string USERS_TABLE_INSERT_FORMT = " (name, "
                            "time_of_application, "
                            "credit_score , "
                            "monthly_income, "
                            "financial_reserves, "
                            "debt_to_income_ratio, "
                            "loan_duration, "
                            "duration_to_installment_days, "
                            "duration_to_settlement_months, "
                            "requested_loan_amount, "
                            "monthly_interest_rate,"
                            "yearly_interest_rate, "
                            "loss_given_default, "
                            "recovery_rate, "
                            "outstanding_monthly_debt_paymentd_from_loan, "
                            "outstanding_monthly_debt_payments_prior_to_loan, "
                            "amount_to_pay_at_next_installment," 
                            "default_risk_score, "
                            "loan_viability_score,"
                            "adjusted_loan_viability_score, "
                            "matrix_based_adjusted_loan_viability_score, "
                            "interest_rate_by_group, "
                            "best_possible_yearly_rate, "
                            "worst_possible_yearly_rate, "
                            "final_loan_grade, "
                            "potential_profit_from_loan, "
                            "calculated_best_possible_loan_viabbility_score, "
                            "calculated_worst_possible_loan_viabbility_score, "
                            "amount_of_current_loan_and_interests_left, "
                            "loan_decision, "
                            "loan_status, "
                            "applied_today_or_not, "
                            "account_number, "
                            "end_of_term_copying_done"
                            ") VALUES (";

