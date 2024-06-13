#pragma once

#include <mutex>
#include <fstream>
#include "Loan.h"
// #include "processor.h"
#include "constants.h"
#include "databaseAbstraction.h"

namespace databaseManager
{
    using namespace std;
    mutex DATABASELOCKMUTEX;
    
    const unsigned short int LOAN_ID_POSITION = 0;
    const unsigned short int NAME_POSITION = 1;
    const unsigned short int TIME_OF_APPLICATION_POSITION = 2;
    const unsigned short int CREDIT_SCORE_POSITION = 3;
    const unsigned short int MONTHLY_INCOME_POSITION = 4;
    const unsigned short int FINANCIAL_RESERVES_POSITION = 5;
    const unsigned short int DEBT_TO_INCOME_RATIO_POSITION = 6;
    const unsigned short int LOAN_DURATION_POSITION = 7;
    const unsigned short int DURATION_TO_NEXT_INSTALLMENT_DAYS_POSITION = 8;
    const unsigned short int DURATION_TO_LOAN_SETTLEMENT_MONTHS_POSITION = 9;
    const unsigned short int REQUESTED_LOAN_AMOUNT_POSITION = 10;
    const unsigned short int MONTHLY_INTEREST_RATE_POSITION = 11;
    const unsigned short int YEARLY_INTEREST_RATE_POSITION = 12;
    const unsigned short int LOSS_GIVEN_DEFAULT_POSITION = 13;
    const unsigned short int RECOVERY_RATE_POSITION = 14;
    const unsigned short int OUTSTANDING_MONTHLY_DEBT_PAYMENTD_FROM_LOAN_POSITION = 15;
    const unsigned short int OUTSTANDING_MONTHLY_DEBT_PAYMENTS_PRIOR_TO_LOAN_POSITION = 16;
    const unsigned short int AMOUNT_TO_PAY_AT_NEXT_INSTALLMENT_POSITION = 17;
    const unsigned short int DEFAULT_RISK_SCORE_POSITION = 18;
    const unsigned short int LOAN_VIABILITY_SCORE_POSITION = 19;
    const unsigned short int ADJUSTED_LOAN_VIABILITY_SCORE_POSITION = 20;
    const unsigned short int MATRIX_BASED_ADJUSTED_LOAN_VIABILITY_SCORE_POSITION = 21;
    const unsigned short int INTEREST_RATE_BY_GROUP_POSITION = 22;
    const unsigned short int BEST_POSSIBLE_YEARLY_RATE_POSITION = 23;
    const unsigned short int WORST_POSSIBLE_YEARLY_RATE_POSITION = 24;
    const unsigned short int FINAL_LOAN_GRADE_POSITION = 25;
    const unsigned short int POTENTIAL_PROFIT_FROM_LOAN_POSITION = 26;
    const unsigned short int CALCULATED_BEST_POSSIBLE_LOAN_VIABILITY_SCORE_POSITION = 27;
    const unsigned short int CALCULATED_WORST_POSSIBLE_LOAN_VIABILITY_SCORE_POSITION = 28;
    const unsigned short int AMOUNT_OF_CURRENT_LOAN_AND_INTERESTS_LEFT_POSITION = 29;
    const unsigned short int LOAN_DECISION_POSITION = 30;
    const unsigned short int LOAN_STATUS_POSITION = 31;
    const unsigned short int APPLIED_TODAY_OR_NOT_POSITION = 32;
    const unsigned short int ACCOUNT_NUMBER_POSITION = 33;
    const unsigned short int END_OF_TERM_COPYING_DONE_POSITION = 34;
    
    
    // Table Names
    const string REPORTS_TABLE_NAME = "reports";
    const string TABLE_OF_INITIAL_USER_APPLICATION = "users";
    const string REJECTED_USERS_TABLE_NAME = "rejected_users";
    const string ACCEPTED_USERS_TABLE_NAME = "accepted_users";
    const string DEFAULTING_USERS_TABLE_NAME = "defaulting_users";


    class userDataFromDb
    {
    private:
        int loanId;
        string userName;
        string timeOfApplication;
        int creditScore;
        double monthlyIncome;
        double financialReserves;
        double debtToIncomeRatio;
        double loanDuration;

        int durationToNextInstallmentDays;
        int previousDurationToNextInstallmentDays;

        int durationToLoanSettlementMonths;
        double requestedLoanAmount;
        double monthlyInterestRate;
        double yearlyInterestRate;
        double lossGivenDefault;
        double recoveryRate;

        double outstandingMonthlyDebtsPaymentsFromLoan;
        double outsytandingMonthlyDebtPaymentsPriorToLoan;
        double amounttoPayAtNextInsstallment;
        double defaultRiskScore;
        double loanViabilityScore;

        double adjustedLoanViabilityScore;
        double matrixBasedAdjustedLoanViabilityScore;
        double interestRateByGroup;
        double bestPossibleYearlyRate;

        double worstPossibleYearlyRate;
        char finalLoanGrade;
        double potentialProfitFromLoan;
        double calculatedBestPossibleLoanViabilityScore;
        double calculatedWorstPossibleLoanViabilityScore;
        double calculatedBestPossibleAdjustedLoanViabilityScore;
        double calculatedWorstpossibleAdjustedLoanViabilityScore;
        
        double amountOfCurrentLoanAndInteerestsLeft;
        int loanDecision;
        string loanStatus;
        int appliedToday;
        int accountNumber;
        bool endOfTermCopyingDone;

        string sqlInsertFormat;
        string stringSqlInsertData;



        string createSqlFormat(string tableName)
        {
            string format = "CREATE TABLE IF NOT EXISTS " + tableName + " (Loan_id INTEGER,"
                        "name TEXT,"
                        "time_of_application TEXT,"
                        "credit_score INTEGER,"
                        "monthly_income REAL,"
                        "financial_reserves REAL,"
                        "debt_to_income_ratio REAL,"
                        "loan_duration REAL,"
                        "duration_to_next_installment_days INTEGER,"
                        "duration_to_loan_settlement_months INTEGER,"
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

                        // cout << tableName << endl;

            return format;
        }


        string createSqlInsertValues(string tableName)
        {
            string stringFinalLoangrade;
            string stringFinalSqlInsertStatement;
            string insertData;
            
            stringFinalLoangrade = finalLoanGrade;

            stringFinalSqlInsertStatement = to_string(loanId) + ",";
            stringFinalSqlInsertStatement = stringFinalSqlInsertStatement + "'" + userName + "'," + "'" + timeOfApplication + "',";
            stringFinalSqlInsertStatement = stringFinalSqlInsertStatement 
            + to_string(creditScore) + "," 
            + to_string(monthlyIncome) + "," 
            + to_string(financialReserves) + "," 
            + to_string(debtToIncomeRatio) + "," 
            + to_string(loanDuration) + "," 
            + to_string(durationToNextInstallmentDays) + "," 
            + to_string(durationToLoanSettlementMonths) + ","
            + to_string(requestedLoanAmount) + "," 
            + to_string(monthlyInterestRate) + "," 
            + to_string(getYearlyInterestRate()) + ","
            + to_string(lossGivenDefault) + "," 
            + to_string(recoveryRate) + ","
            + to_string(outstandingMonthlyDebtsPaymentsFromLoan) + "," 
            + to_string(outsytandingMonthlyDebtPaymentsPriorToLoan) + "," 
            + to_string(amounttoPayAtNextInsstallment) + "," 
            + to_string(defaultRiskScore) + "," 
            + to_string(loanViabilityScore) + "," 
            + to_string(adjustedLoanViabilityScore) + "," 
            + to_string(matrixBasedAdjustedLoanViabilityScore) + "," 
            + to_string(interestRateByGroup) + "," 
            + to_string(bestPossibleYearlyRate) + ","
            + to_string(worstPossibleYearlyRate) + "," 
            + "'" + stringFinalLoangrade + "'," 
            + to_string(potentialProfitFromLoan) + "," 
            + to_string(calculatedBestPossibleLoanViabilityScore)+ "," 
            + to_string(calculatedWorstPossibleLoanViabilityScore)+ "," 
            + to_string(amountOfCurrentLoanAndInteerestsLeft) + "," 
            + to_string(loanDecision) + "," 
            + "'" + loanStatus + "'," 
            + to_string(appliedToday) + "," 
            + to_string(accountNumber) + ","
            + to_string((int)(endOfTermCopyingDone));
            

            insertData = "INSERT INTO " + tableName +  " (Loan_id, " 
                                "name, "
                                "time_of_application, "
                                "credit_score, "
                                "monthly_income, "
                                "financial_reserves, "
                                "debt_to_income_ratio, "
                                "loan_duration, "
                                "duration_to_next_installment_days, "
                                "duration_to_loan_settlement_months, "
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
                                ") VALUES (" + stringFinalSqlInsertStatement + ");"; 

            // cout << sqlInsertFormat << endl;
            // cout << stringSqlInsertData << endl;
            return insertData;
        }


    public:
        userDataFromDb(vector<string> data)
        {
            loanId = stoi(data[LOAN_ID_POSITION]);
            userName = data[NAME_POSITION];
            timeOfApplication = data[TIME_OF_APPLICATION_POSITION];
            creditScore = stoi(data[CREDIT_SCORE_POSITION]);
            monthlyIncome = stod(data[MONTHLY_INCOME_POSITION]);
            financialReserves = stod(data[FINANCIAL_RESERVES_POSITION]);
            debtToIncomeRatio = stod(data[DEBT_TO_INCOME_RATIO_POSITION]);
            loanDuration = stod(data[LOAN_DURATION_POSITION]);
            durationToNextInstallmentDays = stod(data[DURATION_TO_NEXT_INSTALLMENT_DAYS_POSITION]);
            durationToLoanSettlementMonths = stod(data[DURATION_TO_LOAN_SETTLEMENT_MONTHS_POSITION]);
            requestedLoanAmount = stod(data[REQUESTED_LOAN_AMOUNT_POSITION]);
            monthlyInterestRate = stod(data[MONTHLY_INTEREST_RATE_POSITION]);
            yearlyInterestRate = stod(data[YEARLY_INTEREST_RATE_POSITION]);
            lossGivenDefault = stod(data[LOSS_GIVEN_DEFAULT_POSITION]);
            recoveryRate = stod(data[RECOVERY_RATE_POSITION]);
            outstandingMonthlyDebtsPaymentsFromLoan = stod(data[OUTSTANDING_MONTHLY_DEBT_PAYMENTD_FROM_LOAN_POSITION]);
            outsytandingMonthlyDebtPaymentsPriorToLoan = stod(data[OUTSTANDING_MONTHLY_DEBT_PAYMENTS_PRIOR_TO_LOAN_POSITION]);
            amounttoPayAtNextInsstallment = stod(data[AMOUNT_TO_PAY_AT_NEXT_INSTALLMENT_POSITION]);
            defaultRiskScore = stod(data[DEFAULT_RISK_SCORE_POSITION]);
            loanViabilityScore = stod(data[LOAN_VIABILITY_SCORE_POSITION]);
            adjustedLoanViabilityScore = stod(data[ADJUSTED_LOAN_VIABILITY_SCORE_POSITION]);
            matrixBasedAdjustedLoanViabilityScore = stod(data[MATRIX_BASED_ADJUSTED_LOAN_VIABILITY_SCORE_POSITION]);
            interestRateByGroup = stod(data[INTEREST_RATE_BY_GROUP_POSITION]);
            bestPossibleYearlyRate = stod(data[BEST_POSSIBLE_YEARLY_RATE_POSITION]);
            worstPossibleYearlyRate = stod(data[WORST_POSSIBLE_YEARLY_RATE_POSITION]);
            finalLoanGrade = data[FINAL_LOAN_GRADE_POSITION][0];
            potentialProfitFromLoan = stod(data[POTENTIAL_PROFIT_FROM_LOAN_POSITION]);
            calculatedBestPossibleLoanViabilityScore = stod(data[CALCULATED_BEST_POSSIBLE_LOAN_VIABILITY_SCORE_POSITION]);
            calculatedWorstPossibleLoanViabilityScore = stod(data[CALCULATED_WORST_POSSIBLE_LOAN_VIABILITY_SCORE_POSITION]);
            amountOfCurrentLoanAndInteerestsLeft = stod(data[AMOUNT_OF_CURRENT_LOAN_AND_INTERESTS_LEFT_POSITION]);
            loanDecision = stoi(data[LOAN_DECISION_POSITION]);
            loanStatus = data[LOAN_STATUS_POSITION];
            appliedToday = stoi(data[APPLIED_TODAY_OR_NOT_POSITION]);
            accountNumber = stoi(data[ACCOUNT_NUMBER_POSITION]);
            endOfTermCopyingDone = stoi(data[END_OF_TERM_COPYING_DONE_POSITION]);

            previousDurationToNextInstallmentDays = durationToNextInstallmentDays;
        }
        int getLoanId() const { 
            return loanId; 
        }
        string getUserName() const {
            return userName;
        }
        string getTimeOfApplication() const { 
            return timeOfApplication; 
        }
        int getCreditScore() const { 
            return creditScore;
        }
        double getMonthlyIncome() const { 
            return monthlyIncome; 
        }
        double getFinancialReserves() const { 
            return financialReserves; 
        }
        double getDebtToIncomeRatio() const { 
            return debtToIncomeRatio; 
        }
        double getLoanDuration() const { 
            return loanDuration; 
        }
        int getDurationToNextInstallmentDays() const { 
            return durationToNextInstallmentDays; 
        }
        int getDurationToLoanSettlementMonths() const {
            return durationToLoanSettlementMonths;
        }
        double getRequestedLoanAmount() const { 
            return requestedLoanAmount; 
        }
        double getMonthlyInterestRate() const { 
            return monthlyInterestRate; 
        }
        double getYearlyInterestRate() const { 
            return yearlyInterestRate; 
        }
        double getLossGivenDefault() const { 
            return lossGivenDefault; 
        }
        double getRecoveryRate() const { 
            return recoveryRate; 
        }
        double getOutstandingMonthlyDebtsPaymentsFromLoan() const{
            return outstandingMonthlyDebtsPaymentsFromLoan;
        }
        double getOutsytandingMonthlyDebtPaymentsPriorToLoan() const { 
            return outsytandingMonthlyDebtPaymentsPriorToLoan; 
        }
        double getAmounttoPayAtNextInsstallment() const { 
            return amounttoPayAtNextInsstallment; 
        }
        double getDefaultRiskScore() const { 
            return defaultRiskScore; 
        }
        double getLoanViabilityScore() const { 
            return loanViabilityScore; 
        }
        double getAdjustedLoanViabilityScore() const { 
            return adjustedLoanViabilityScore; 
        }
        double getMatrixBasedAdjustedLoanViabilityScore() const { 
            return matrixBasedAdjustedLoanViabilityScore; 
        }
        double getInterestRateByGroup() const { 
            return interestRateByGroup; 
        }
        double getBestPossibleYearlyRate() const { 
            return bestPossibleYearlyRate; 
        }
        double getWorstPossibleYearlyRate() const { 
            return worstPossibleYearlyRate; 
        }
        char getFinalLoanGrade() const { 
            return finalLoanGrade; 
        }
        double getPotentialProfitFromLoan() const { 
            return potentialProfitFromLoan; 
        }
        double getCalculatedBestPossibleAdjustedLoanViabilityScore() const { 
            return calculatedBestPossibleAdjustedLoanViabilityScore; 
        }
        double getCalculatedWorstpossibleAdjustedLoanViabilityScore() const { 
            return calculatedWorstpossibleAdjustedLoanViabilityScore; 
        }
        double getAmountOfCurrentLoanAndInteerestsLeft() const { 
            return amountOfCurrentLoanAndInteerestsLeft; 
        }
        int getLoanDecision() const { 
            return loanDecision; 
        }
        string getLoanStatus() const { 
            return loanStatus; 
        }
        int getAppliedToday() const { 
            return appliedToday; 
        }
        int getAccountNumber() const { 
            return accountNumber; 
        }
        int getEndOfTermCopyingDone() const{
            return endOfTermCopyingDone;
        }
    };



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


    vector<vector<string>> getAllDbDATA()
    {
        return databaseAbstraction::retrieveAllUserDataFromDatabaseForMatrix(DATABASE_NAME, TABLE_OF_INITIAL_USER_APPLICATION);
    }


    bool isColumnValNeccessaryForCSV(const int & position)
    {
       if (position == NAME_POSITION || position == CREDIT_SCORE_POSITION ||
        position == MONTHLY_INCOME_POSITION || position == FINANCIAL_RESERVES_POSITION ||
        position == DEBT_TO_INCOME_RATIO_POSITION || position == LOAN_DURATION_POSITION ||
        position == REQUESTED_LOAN_AMOUNT_POSITION || position == MONTHLY_INTEREST_RATE_POSITION ||
        position == YEARLY_INTEREST_RATE_POSITION || position == LOSS_GIVEN_DEFAULT_POSITION ||
        position == RECOVERY_RATE_POSITION || position == OUTSTANDING_MONTHLY_DEBT_PAYMENTD_FROM_LOAN_POSITION ||
        position == DEFAULT_RISK_SCORE_POSITION || position == LOAN_VIABILITY_SCORE_POSITION ||
        position == ADJUSTED_LOAN_VIABILITY_SCORE_POSITION || position == MATRIX_BASED_ADJUSTED_LOAN_VIABILITY_SCORE_POSITION ||
        position == INTEREST_RATE_BY_GROUP_POSITION || position == BEST_POSSIBLE_YEARLY_RATE_POSITION ||
        position == WORST_POSSIBLE_YEARLY_RATE_POSITION || position == FINAL_LOAN_GRADE_POSITION ||
        position == POTENTIAL_PROFIT_FROM_LOAN_POSITION || position == CALCULATED_BEST_POSSIBLE_LOAN_VIABILITY_SCORE_POSITION ||
        position == CALCULATED_WORST_POSSIBLE_LOAN_VIABILITY_SCORE_POSITION || position == AMOUNT_OF_CURRENT_LOAN_AND_INTERESTS_LEFT_POSITION ||
        position == LOAN_DECISION_POSITION) 
        {
            return true;
        }

        return false;
    }


    bool retrieveAllUserDataFromDatabaseAndOutputToCsv(ofstream& outputCsvFile)
    {
        int matrixSize = 0;
        bool fileOpeningError = false;

        string outputDBDataToCsvHeader = "Name,"
                                 "credit_score,"
                                 "monthly_income,"
                                 "financial_reserves,"
                                 "debt_to_income_ratio,"
                                 "Duration_in_months,"
                                 "loan_amount_requested,"
                                 "Monthly_interest_rate,"
                                 "Interest_rate_over_a_year,"
                                 "loss_Given_Default,"
                                 "Recovery_Rate,"
                                 "outstanding_Monthly_Debt_Payments,"
                                 "default_risk_score,"
                                 "Loan_Viability_Score,"
                                 "Adjusted_Loan_viability_Score,"
                                 "matrix_based_adjusted_loan_viability_score,"
                                 "interest_rate_by_group,"
                                 "best_possible_rate,"
                                 "worst_possible_rate,"
                                 "final_loan_grade,"
                                 "potential_profit_from_loan,"
                                 "calculated_best_possible_loan_viability_score,"
                                 "calculated_worst_possible_loan_viability_score,"
                                 "amount_of_current_loan_and_interests_left,"
                                 "loan_decision";
        
        
        vector<vector<string>> dataMatrix = getAllDbDATA();
        

        outputCsvFile.open(CSV_FILE_FOR_STORING_ANALAYZED_DB_VALUES);
        
        if (outputCsvFile.fail())
        {
            fileOpeningError = true;
            
            // throw " Error opening File to output database values.";
        }
        else
        {
            matrixSize = dataMatrix.size();


            outputCsvFile << outputDBDataToCsvHeader << endl;

            for(int count = 0; count < matrixSize; count++)
            {
                // userDataFromDb dataFromDb(dataMatrix[count]);
                for(int j = 0; j < dataMatrix[count].size(); j++)
                {
                    if(isColumnValNeccessaryForCSV(j))          // Do not print the time of application and index into the csv file
                    {
                        outputCsvFile << dataMatrix[count][j];

                        if(j < (LOAN_DECISION_POSITION))
                        {
                            outputCsvFile << ",";
                        }
                        else
                        {
                            outputCsvFile << "\n";
                        }
                    }
                }

            }
            
            outputCsvFile.close();
        }
            
        return fileOpeningError;
    }


    string retreiveUserNameMatchingLoanId(int loanId)
    {
        vector<vector<string>> dbValues = databaseAbstraction::retreiveDataWithMatchingValue(DATABASE_NAME, TABLE_OF_INITIAL_USER_APPLICATION, "Loan_id", to_string(loanId));
        
        return (dbValues[0][NAME_POSITION]);
    }



    vector<vector<string>> getTodaysApplications()
    {
        vector<vector<string>> data;

        data = databaseAbstraction::retreiveDataWithMatchingValue(DATABASE_NAME, TABLE_OF_INITIAL_USER_APPLICATION, "applied_today_or_not", "1");

        // printMatrixValues(data);

        return data;
    }
    

    vector<vector <string>> getAllApplicationsBesideTodays()
    {
        vector<vector<string>> data;

        data = databaseAbstraction::retreiveDataWithMatchingValue(DATABASE_NAME, TABLE_OF_INITIAL_USER_APPLICATION, "applied_today_or_not", "0");

        // printMatrixValues(data);

        return data;
    }


    bool addLoanUser(Loan userData)
    {
        string insertFormat = userData.getSqlInsertFormat();
        string statementWithData = userData.getInsertStatementWithData();
        double timeTaken = databaseAbstraction::storeSingleRowInDbUsingSingleInsert(DATABASE_NAME, insertFormat, TABLE_OF_INITIAL_USER_APPLICATION, statementWithData);

        return true;
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

            // if(count >= 1)
            // {
            //     if(count < 10)
            //     {
            //         cout << " ALVS = " << loanData[count].getFinalAdjustedLoanViabilityScore() << " Matrix based ALVS = " << loanData[count].getMatrixBasedAdjustedLoanViabilityScore();
            //         cout << endl;
    
            //     }

            // }

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

        cout << "Time taken to store " << loanData.size() << " applications = " <<  timeInt << " millisecond(s), which is equal to " << timeInSeconds << " seconds" << endl;

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
        const unsigned char * finalLoanGrade;
        double monthlyIncome, financialReserves, debtToIncomeRatio, loanDurationInMonths, loanAmount, monthlyInteresRate, 
            yearlyInterestRate, recoveryRate, outstandingMonthlyDebtPaymentsFromLoan, defaultRiskScore, loanViabilityScore,
            adjustedLoanViabilityScore, matrixBasedAdjustedLoanViabilityScore, lossGivenDefault, interestRateByGroup, bestPossibleRate, worstPossibleRate, 
            potentialProfitfromLoan, calculatedBestPossibleLoanViabilityScore, calculatedWorstPossibleLoanViabilityScore, amountOfCurrentLoanAndInterestsLeft, loanDecision;
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
                //cout << " Output File Opening Error. " << endl;s
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

                outputCsvFile << "Name,credit_score,"
                                 "monthly_income,"
                                 "financial_reserves,"
                                 "debt_to_income_ratio,"
                                 "Duration_in_months,"
                                 "loan_amount_requested,"
                                 "Monthly_interest_rate,"
                                 "Interest_rate_over_a_year,"
                                 "loss_Given_Default,"
                                 "Recovery_Rate,"
                                 "outstanding_Monthly_Debt_Payments,"
                                 "default_risk_score,"
                                 "Loan_Viability_Score,"
                                 "Adjusted_Loan_viability_Score,"
                                 "matrix_based_adjusted_loan_viability_score,"
                                 "interest_rate_by_group,"
                                 "best_possible_rate,"
                                 "worst_possible_rate,"
                                 "final_loan_grade,"
                                 "potential_profit_from_loan,"
                                 "calculated_best_possible_loan_viability_score,"
                                 "calculated_worst_possible_loan_viability_score,"
                                 "amount_of_current_loan_and_interests_left,"
                                 "loan_decision" << endl;

                while (sqlite3_step(stmt) == SQLITE_ROW) {
                    // loanId = sqlite3_column_int(stmt, 0);
                    const unsigned char* userName = sqlite3_column_text(stmt, 1);
                    creditScore = sqlite3_column_int(stmt, 3);
                    monthlyIncome = sqlite3_column_double(stmt, 4);
                    financialReserves = sqlite3_column_double(stmt, 5);
                    debtToIncomeRatio = sqlite3_column_double(stmt, 6);
                    loanDurationInMonths = sqlite3_column_double(stmt, 7);
                    loanAmount = sqlite3_column_double(stmt, 9 + 1);
                    monthlyInteresRate = sqlite3_column_double(stmt, 10 + 1);
                    yearlyInterestRate = sqlite3_column_double(stmt, 11 + 1);
                    lossGivenDefault = sqlite3_column_double(stmt, 12 + 1);
                    recoveryRate = sqlite3_column_double(stmt, 13 + 1);
                    outstandingMonthlyDebtPaymentsFromLoan = sqlite3_column_double(stmt, 14 + 1);
                    defaultRiskScore = sqlite3_column_double(stmt, 17 + 1);
                    loanViabilityScore = sqlite3_column_double(stmt, 18 + 1);
                    adjustedLoanViabilityScore = sqlite3_column_double(stmt, 19 + 1);
                    matrixBasedAdjustedLoanViabilityScore = sqlite3_column_double(stmt, 20 + 1);
                    interestRateByGroup = sqlite3_column_double(stmt, 21 + 1);
                    bestPossibleRate = sqlite3_column_double(stmt, 22 + 1);
                    worstPossibleRate = sqlite3_column_double(stmt, 23 + 1);
                    finalLoanGrade = sqlite3_column_text(stmt, 24 + 1);
                    potentialProfitfromLoan = sqlite3_column_double(stmt, 25 + 1);
                    calculatedBestPossibleLoanViabilityScore = sqlite3_column_double(stmt, 26 + 1);
                    calculatedWorstPossibleLoanViabilityScore = sqlite3_column_double(stmt, 27 + 1);
                    amountOfCurrentLoanAndInterestsLeft = sqlite3_column_double(stmt, 28 + 1);
                    loanDecision = sqlite3_column_double(stmt, 29 + 1);



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
                    outputCsvFile << worstPossibleRate << ",";
                    outputCsvFile << finalLoanGrade << ",";
                    outputCsvFile << potentialProfitfromLoan << ",";
                    outputCsvFile << calculatedBestPossibleLoanViabilityScore << ",";
                    outputCsvFile << calculatedWorstPossibleLoanViabilityScore<< ",";
                    outputCsvFile << amountOfCurrentLoanAndInterestsLeft << ",";
                    outputCsvFile << loanDecision;
                    outputCsvFile << endl;

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

            insertToSql = loanData[count].getInsertStatementWithData();

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




    // bool copyUserDataToCompletedTable(Processor::userDataFromDb userData)
    // {
    //     string insertFormat = userData.getSqlInsertformat();
    //     string statementWithData = userData.getSqlInsertValues();

    //     double timeTaken = databaseAbstraction::storeSingleRowInDbUsingSingleInsert(DATABASE_NAME, insertFormat, TABLE_OF_INITIAL_USER_APPLICATION, statementWithData);
       
    //     return true;
    // }


    // bool copyUserDataToDefaultedTable(Processor::userDataFromDb userData)
    // {
    //     string insertFormat = userData.getSqlInsertformat();
    //     string statementWithData = userData.getSqlInsertValues();

    //     // cout << insertFormat << endl;
    //     // cout << statementWithData << endl;

    //     double timeTaken = databaseAbstraction::storeSingleRowInDbUsingSingleInsert(DATABASE_NAME, insertFormat, DEFAULTING_USERS_TABLE_NAME, statementWithData);
       
    //     return true;
    // }
    
    
}