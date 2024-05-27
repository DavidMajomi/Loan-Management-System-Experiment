#pragma once

#include <fstream>
#include "Loan.h"
#include "processor.h"
#include "databaseAbstraction.h"

namespace databaseManager
{
    using namespace std;

    // Matrix positions of db values
    const unsigned short int LOAN_ID_POSITION = 0;
    const unsigned short int NAME_POSITION = 1;
    const unsigned short int TIME_OF_APPLICATION_POSITION = 2;
    const unsigned short int CREDIT_SCORE_POSITION = 3;
    const unsigned short int MONTHLY_INCOME_POSITION = 4;
    const unsigned short int FINANCIAL_RESERVES_POSITION = 5;
    const unsigned short int DEBT_TO_INCOME_RATIO_POSITION = 6;
    const unsigned short int LOAN_DURATION_POSITION = 7;
    const unsigned short int REQUESTED_LOAN_AMOUNT_POSITION = 8;
    const unsigned short int MONTHLY_INTEREST_RATE_POSITION = 9;
    const unsigned short int YEARLY_INTEREST_RATE_POSITION = 10;
    const unsigned short int LOSS_GIVEN_DEFAULT_POSITION = 11;
    const unsigned short int RECOVERY_RATE_POSITION = 12;
    const unsigned short int OUTSTANDING_MONTHLY_DEBT_PAYMENTS_POSITION = 13;
    const unsigned short int DEFAULT_RISK_SCORE_POSITION = 14;
    const unsigned short int LOAN_VIABILITY_SCORE_POSITION = 15;
    const unsigned short int ADJUSTED_LOAN_VIABILITY_SCORE_POSITION = 16;
    const unsigned short int MATRIX_BASED_ADJUSTED_LOAN_VIABILITY_SCORE_POSITION = 17;
    const unsigned short int INTERETS_RATE_BY_GROUP_POSITION = 18;
    const unsigned short int BEST_POSSIBLE_RATE_POSITION = 19;
    const unsigned short int WORST_POSSIBLE_RATE_POSITION = 20;
    const unsigned short int FINAL_LOAN_GRADE_POSITION = 21;
    
    
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
            loanId = stoi(data[0]);
            userName = (data[1]);
            timeOfApplication = (data[2]);
            creditScore = stoi(data[3]);
            monthlyIncome = stod(data[4]);
            financialReserves = stod(data[5]);
            debtToIncomeRatio = stod(data[6]);
            loanDuration = stod(data[7]);
            durationToNextInstallmentDays = stod(data[8]);
            durationToLoanSettlementMonths = stod(data[9]);
            requestedLoanAmount = stod(data[9 + 1]);
            monthlyInterestRate = stod(data[10 + 1]);
            yearlyInterestRate = stod(data[11 + 1]);
            lossGivenDefault = stod(data[12 + 1]);
            recoveryRate = stod(data[13 + 1]);
            outstandingMonthlyDebtsPaymentsFromLoan = stod(data[14 + 1]);
            outsytandingMonthlyDebtPaymentsPriorToLoan = stod(data[15 + 1]);
            amounttoPayAtNextInsstallment = stod(data[16 + 1]);
            defaultRiskScore = stod(data[17 + 1]);
            loanViabilityScore = stod(data[18 + 1]);
            adjustedLoanViabilityScore = stod(data[19 + 1]);
            matrixBasedAdjustedLoanViabilityScore = stod(data[20 + 1]);
            interestRateByGroup = stod(data[21 + 1]);
            bestPossibleYearlyRate = stod(data[22 + 1]);
            worstPossibleYearlyRate = stod(data[23 + 1]);
            finalLoanGrade = (data[24  + 1][0]);
            potentialProfitFromLoan = stod(data[25 + 1]);
            calculatedBestPossibleLoanViabilityScore = stod(data[26 + 1]);
            calculatedWorstPossibleLoanViabilityScore = stod(data[27 + 1]);
            amountOfCurrentLoanAndInteerestsLeft = stod(data[28 + 1]);
            loanDecision = stoi(data[29 + 1]);
            loanStatus = data[30 + 1];
            appliedToday = stoi(data[31 + 1]);
            accountNumber = stoi(data[32 + 1]);
            endOfTermCopyingDone = stoi(data[33 + 1]);

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
        vector<vector<string>> dataMatrix = databaseAbstraction::retrieveAllUserDataFromDatabaseForMatrix(DATABASE_NAME, TABLE_OF_INITIAL_USER_APPLICATION);

        return dataMatrix;
    }


    int retrieveAllUserDataFromDatabaseAndOutputToCsv(ofstream& outputCsvFile)
    {
        int matrixSize;
        
        string outputDBDataToCsvHeader = "Name,credit_score,monthly_income,financial_reserves,debt_to_income_ratio,Duration_in_months,loan_amount_requested,Monthly_interest_rate,Interest_rate_over_a_year,"
        "loss_Given_Default,Recovery_Rate,outstanding_Monthly_Debt_Payments,"
        "default_risk_score,Loan_Viability_Score,Adjusted_Loan_viability_Score,matrix_based_adjusted_loan_viability_score,interest_rate_by_group,best_possible_rate,worst_possible_rate";
        
        
        vector<vector<string>> dataMatrix = getAllDbDATA();

        outputCsvFile.open("dbtest.csv");
        
        if (outputCsvFile.fail())
        {
            throw " Error opening File to output database values.";
        }
        else
        {
            matrixSize = dataMatrix.size();

            outputCsvFile << outputDBDataToCsvHeader << endl;

            for(int count = 0; count < matrixSize; count++)
            {
                for(int j = 0; j < dataMatrix[count].size(); j++)
                {
                    if(j != 2)          // Do not print the time of application into the csv file
                    {

                        outputCsvFile << dataMatrix[count][j];

                        if(j <= (dataMatrix[count].size() - 2))
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
            
        return 0;
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


    bool changeDateToNextInstallment(int loanId, int changeTo)
    {

        return true;
    }


    bool copyUserDataToCompletedTable(Processor::userDataFromDb userData)
    {
        string insertFormat = userData.getSqlInsertformat();
        string statementWithData = userData.getSqlInsertValues();

        double timeTaken = databaseAbstraction::storeSingleRowInDbUsingSingleInsert(DATABASE_NAME, insertFormat, TABLE_OF_INITIAL_USER_APPLICATION, statementWithData);
       
        return true;
    }


    bool copyUserDataToDefaultedTable(Processor::userDataFromDb userData)
    {
        string insertFormat = userData.getSqlInsertformat();
        string statementWithData = userData.getSqlInsertValues();

        // cout << insertFormat << endl;
        // cout << statementWithData << endl;

        double timeTaken = databaseAbstraction::storeSingleRowInDbUsingSingleInsert(DATABASE_NAME, insertFormat, DEFAULTING_USERS_TABLE_NAME, statementWithData);
       
        return true;
    }
    
    
}