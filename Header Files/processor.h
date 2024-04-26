#pragma once

#include <time.h>
#include <string>
#include "constants.h"
#include "stats.h"

namespace Processor
{
    using namespace std;

    class loanUpdates
    {
    private:
        int loanId;
        int durationToNextInstallmentDays;
        int durationToLoanSettlementMonths;
        char finalLoanGrade;
        // double amountOfCurrentLoanAndInterestsLeft;
        int loanDecision;
        string loanStatus;
        int appliedToday;
        bool endOfTermCopyingDone;
        
    public:
        // double amountOfCurrentLoanAndInterestsLeft;
        int getDurationToNextInstallmentDays()
        { 
            return durationToNextInstallmentDays;
        }
        int getDurationToLoanSettlementMonths()
        {
            return durationToLoanSettlementMonths;
        }
        int getLoanId()
        {
            return loanId;
        }
        int getLoanDecision()
        {
            return loanDecision;
        }
        int getAppliedToday()
        {
            return appliedToday;
        }
        char getFinalLoanGrade()
        {
            return finalLoanGrade;
        }
        string getLoanStatus()
        {
            return loanStatus;
        }
        int getEndOfTermCopyingDone()
        {
            return endOfTermCopyingDone;
        }

        void setLoanId(int id)
        {
            this -> loanId = id;
        }
        void setDurationToNextInstallmentDays(int duration)
        { 
            this -> durationToNextInstallmentDays = duration;
        }
        void setDurationToLoanSettlementMonths(int duration)
        {
            this -> durationToLoanSettlementMonths = duration;
        }
        void setLoanDecision(int decision)
        {
            this -> loanDecision = decision;
        }
        void setAppliedToday(int appliedToday)
        {
            this -> appliedToday = appliedToday;
        }
        void setFinalLoanGrade(char grade)
        {
            this -> finalLoanGrade = grade;
        }
        void setLoanStatus(string status)
        {
            this -> loanStatus = status;
        }
        void setEndOfTermCopyingDone(bool done)
        {
            this -> endOfTermCopyingDone = (int)(done);
        }
        

    };


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
        bool endOfTermCopyingDone = false;

        string sqlInsertFormat;
        string stringSqlInsertData;


        int processDurationToNextInstallment()
        {

            if(durationToNextInstallmentDays == 0 && durationToLoanSettlementMonths > 0)
            {
                return 31;
            }
            else if(durationToNextInstallmentDays > 0)
            {
                return durationToNextInstallmentDays - 1;
                
            }
        }


        int processDurationToLoanSettlementMonths()
        {
            int duration;

            if(previousDurationToNextInstallmentDays == 0)
            {
                if(durationToLoanSettlementMonths > 0)
                {
                    duration = durationToLoanSettlementMonths - 1;
                }
                else
                {
                    duration = 0;
                }
            }
            else
            {
                duration = durationToLoanSettlementMonths;

            }

            return duration;
        }


        int processLoanDecision()
        {
            bool accept = false;
            if(finalLoanGrade == 'A')
            {
                accept = true;
            }
            if(finalLoanGrade == 'B')
            {
                accept = true;
            }
            if(finalLoanGrade == 'C')
            {
               accept = true; 
            }
            if(finalLoanGrade == 'D')
            {
               accept = true; 
            }
            if(finalLoanGrade == 'E')
            {
                accept = false;
            }
            if(finalLoanGrade == 'F')
            {
                accept = false;
            }


            return (int)(accept);
        }


        char processFinalLoanGrade()
        {
            char grade;

            if(adjustedLoanViabilityScore >= 80)
            {
                grade = 'A';
            }
            else if(adjustedLoanViabilityScore >= 60 && adjustedLoanViabilityScore < 80)
            {
                grade = 'B';
            }
            else if(adjustedLoanViabilityScore >= 40 && adjustedLoanViabilityScore < 60)
            {
                grade = 'C';
            }
            else if(adjustedLoanViabilityScore >= 20 && adjustedLoanViabilityScore < 40)
            {
                grade = 'D';
            }
            else if(adjustedLoanViabilityScore < 20)
            {
                grade = 'F';
            }

            return grade;
        }
        

        string updateLoanStatus()
        {
            string status;

            if(durationToNextInstallmentDays == 0)
            {
                if(amountOfCurrentLoanAndInteerestsLeft == 0)
                {
                    status = "Completed";
                }
                else
                {
                    if(durationToLoanSettlementMonths == 0)
                    {
                        status = "Defaulted";
                    }
                    else
                    {
                        status  = "In Good Standing";
                    }
                }
            }
            else if(loanDecision == int(true))
            {
                status = "In Good Standing";
            }
            else if(loanDecision == int(false))
            {
                status = "Rejected";
            }

            return status;
        }


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



            if(appliedToday == true)
            {
                // amountOfCurrentLoanAndInteerestsLeft = 
                finalLoanGrade = processFinalLoanGrade();
                loanDecision = processLoanDecision();
            }
            else
            {
                // if((loanStatus != "Completed"))
                // {
                durationToNextInstallmentDays = processDurationToNextInstallment();
                durationToLoanSettlementMonths = processDurationToLoanSettlementMonths();
                // }
            }

            loanStatus = updateLoanStatus();
            appliedToday = int(false);


            sqlInsertFormat = createSqlFormat("users");
            stringSqlInsertData = createSqlInsertValues("users");


            if(loanStatus == "Completed")
            {
                sqlInsertFormat = createSqlFormat("completed_users");
                stringSqlInsertData = createSqlInsertValues("completed_users");

            }
            else if(loanStatus == "Defaulted")
            {
                sqlInsertFormat = createSqlFormat("defaulting_users");   
                stringSqlInsertData = createSqlInsertValues("defaulting_users");
            }
            else
            {
                // sqlInsertFormat = createSqlFormat("defaulte");   
            }



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
        loanUpdates getNewUpdates()
        {
            loanUpdates data;

            data.setLoanId(loanId);
            data.setAppliedToday(appliedToday);
            data.setDurationToNextInstallmentDays(durationToNextInstallmentDays);
            data.setDurationToLoanSettlementMonths(durationToLoanSettlementMonths);
            data.setFinalLoanGrade(this -> finalLoanGrade);
            data.setLoanDecision(this -> loanDecision);
            data.setLoanStatus(this -> loanStatus);
            data.setEndOfTermCopyingDone(this -> endOfTermCopyingDone);

            return data;
        }
        string getSqlInsertformat() const{
            return this -> sqlInsertFormat;
        }
        string getSqlInsertValues() const{
            return this -> stringSqlInsertData;
        }

       

    };


    class reportData
    {
    private:
        string timeOfReportCreation;
        double meanCreditScore = 0;
        double meanDurationToNextInstallmentDays = 0;
        double meanMonthlyIncome = 0;
        double meanFinancialReserves = 0;
        double meanDebtToIncomeRatio = 0;
        double meanLoanDuration = 0;
        double meanRequestedLoanAmount = 0;
        double meanMonthlyInterestRate = 0;
        double meanYearlyInterestRate = 0;
        double meanLossGivenDefault = 0;
        double meanRecoveryRate = 0;
        double meanOutstandingMonthlyDebtsPaymentsFromLoan = 0;
        double meanOutsytandingMonthlyDebtPaymentsPriorToLoan = 0;
        double meanAmounttoPayAtNextInsstallment = 0;
        double meanDefaultRiskScore = 0;
        double meanLoanViabilityScore = 0;
        double meanAdjustedLoanViabilityScore = 0;
        double meanPotentialProfitFromLoan = 0;

        double medianCreditScore = 0;
        double medianDurationToNextInstallmentDays = 0;
        double medianMonthlyIncome = 0;
        double medianFinancialReserves = 0;
        double medianDebtToIncomeRatio = 0;
        double medianLoanDuration = 0;
        double medianRequestedLoanAmount = 0;
        double medianMonthlyInterestRate = 0;
        double medianYearlyInterestRate = 0;
        double medianLossGivenDefault = 0;
        double medianRecoveryRate = 0;
        double medianOutstandingMonthlyDebtsPaymentsFromLoan = 0;
        double medianOutsytandingMonthlyDebtPaymentsPriorToLoan = 0;
        double medianAmounttoPayAtNextInsstallment = 0;
        double medianDefaultRiskScore = 0;
        double medianLoanViabilityScore = 0;
        double medianAdjustedLoanViabilityScore = 0;
        double medianPotentialProfitFromLoan = 0;

        vector <double> modeCreditScore;
        vector <double> modeDurationToNextInstallmentDays;
        vector <double> modeMonthlyIncome;
        vector <double> modeFinancialReserves;
        vector <double> modeDebtToIncomeRatio;
        vector <double> modeLoanDuration;
        vector <double> modeRequestedLoanAmount;
        vector <double> modeMonthlyInterestRate;
        vector <double> modeYearlyInterestRate;
        vector <double> modeLossGivenDefault;
        vector <double> modeRecoveryRate;
        vector <double> modeOutstandingMonthlyDebtsPaymentsFromLoan;
        vector <double> modeOutsytandingMonthlyDebtPaymentsPriorToLoan;
        vector <double> modeAmounttoPayAtNextInsstallment;
        vector <double> modeDefaultRiskScore;
        vector <double> modeLoanViabilityScore;
        vector <double> modeAdjustedLoanViabilityScore;
        vector <double> modePotentialProfitFromLoan;

        double stdDeviationCreditScore = 0;
        double stdDeviationDurationToNextInstallmentDays = 0;
        double stdDeviationMonthlyIncome = 0;
        double stdDeviationFinancialReserves = 0;
        double stdDeviationDebtToIncomeRatio = 0;
        double stdDeviationLoanDuration = 0;
        double stdDeviationRequestedLoanAmount = 0;
        double stdDeviationMonthlyInterestRate = 0;
        double stdDeviationYearlyInterestRate = 0;
        double stdDeviationLossGivenDefault = 0;
        double stdDeviationRecoveryRate = 0;
        double stdDeviationOutstandingMonthlyDebtsPaymentsFromLoan = 0;
        double stdDeviationOutsytandingMonthlyDebtPaymentsPriorToLoan = 0;
        double stdDeviationAmounttoPayAtNextInsstallment = 0;
        double stdDeviationDefaultRiskScore = 0;
        double stdDeviationLoanViabilityScore = 0;
        double stdDeviationAdjustedLoanViabilityScore = 0;
        double stdDeviationPotentialProfitFromLoan = 0;

        // char finalLoanGrade;
        int numAgrade = 0;
        int numBgrade = 0;
        int numcgrade = 0;
        int numDgrade = 0;
        int numEgrade = 0;
        int numFgrade = 0;
        int numAppliedToday = 0;
        double sumPotentialProfitFromLoan = 0;


        vector <double> creditScoreData;
        vector <double> durationToNextInstallmentDaysData;
        vector <double> monthlyIncomeData;
        vector <double> financialReservesData;
        vector <double> debtToIncomeRatioData;
        vector <double> loanDurationData;
        vector <double> requestedLoanAmountData;
        vector <double> monthlyInterestRateData;
        vector <double> yearlyInterestRateData;
        vector <double> lossGivenDefaultData;
        vector <double> recoveryRateData;
        vector <double> outstandingMonthlyDebtsPaymentsFromLoanData;
        vector <double> outsytandingMonthlyDebtPaymentsPriorToLoanData;
        vector <double> amounttoPayAtNextInsstallmentData;
        vector <double> defaultRiskScoreData;
        vector <double> loanViabilityScoreData;
        vector <double> adjustedLoanViabilityScoreData;
        vector <double> potentialProfitFromLoan;


        string sqlInsertFormat;
        string stringSqlInsertData;

        string prepareSqlInsertStmt()
        {
            return "CREATE TABLE IF NOT EXISTS reports (report_number INTEGER PRIMARY KEY,"
                            "date_of_report TEXT,"
                            "mean_credit_score REAL,"
                            "mean_duration_to_next_installment_days REAL,"
                            "mean_monthly_income REAL,"
                            "mean_financial_reserves REAL,"
                            "mean_debt_to_income_ratio REAL,"
                            "mean_loan_duration REAL,"
                            "mean_requested_loan_amount REAL,"
                            "mean_monthly_interest_rate REAL,"
                            "mean_yearly_interest_rate REAL,"
                            "mean_loss_given_default REAL,"
                            "mean_recovery_rate REAL,"
                            "mean_outstanding_monthly_debts_payments_from_loan REAL,"
                            "mean_outsytanding_monthly_debt_payments_prior_to_loan REAL,"
                            "mean_amountto_pay_at_next_insstallment REAL,"
                            "mean_default_risk_score REAL,"
                            "mean_loan_viability_score REAL,"
                            "mean_adjusted_loan_viability_score REAL,"
                            "mean_potential_profit_from_loan REAL,"
                            "sum_potential_profit_from_loan REAL,"
                            "median_credit_score REAL,"
                            "median_duration_to_next_installment_days REAL,"
                            "median_monthly_income REAL,"
                            "median_financial_reserves REAL,"
                            "median_debt_to_income_ratio REAL,"
                            "median_loan_duration REAL,"
                            "median_requested_loan_amount REAL,"
                            "median_monthly_interest_rate REAL,"
                            "median_yearly_interest_rate REAL,"
                            "median_loss_given_default REAL,"
                            "median_recovery_rate REAL,"
                            "median_outstanding_monthly_debts_payments_from_loan REAL,"
                            "median_outsytanding_monthly_debt_payments_prior_to_loan REAL,"
                            "median_amountto_pay_at_next_insstallment REAL,"
                            "median_default_risk_score REAL,"
                            "median_loan_viability_score REAL,"
                            "median_adjusted_loan_viability_score REAL,"
                            "median_potential_profit_from_loan REAL,"
                            "mode_credit_score TEXT,"
                            "mode_duration_to_next_installment_days TEXT,"
                            "mode_monthly_income TEXT,"
                            "mode_financial_reserves TEXT,"
                            "mode_debt_to_income_ratio TEXT,"
                            "mode_loan_duration TEXT,"
                            "mode_requested_loan_amount TEXT,"
                            "mode_monthly_interest_rate TEXT,"
                            "mode_yearly_interest_rate TEXT,"
                            "mode_loss_given_default TEXT,"
                            "mode_recovery_rate TEXT,"
                            "mode_outstanding_monthly_debts_payments_from_loan TEXT,"
                            "mode_outsytanding_monthly_debt_payments_prior_to_loan TEXT,"
                            "mode_amountto_pay_at_next_insstallment TEXT,"
                            "mode_default_risk_score TEXT,"
                            "mode_loan_viability_score TEXT,"
                            "mode_adjusted_loan_viability_score TEXT,"
                            "mode_potential_profit_from_loan TEXT,"
                            "std_deviation_credit_score REAL,"
                            "std_deviation_duration_to_next_installment_days REAL,"
                            "std_deviation_monthly_income REAL,"
                            "std_deviation_financial_reserves REAL,"
                            "std_deviation_debt_to_income_ratio REAL,"
                            "std_deviation_loan_duration REAL,"
                            "std_deviation_requested_loan_amount REAL,"
                            "std_deviation_monthly_interest_rate REAL,"
                            "std_deviation_yearly_interest_rate REAL,"
                            "std_deviation_loss_given_default REAL,"
                            "std_deviation_recovery_rate REAL,"
                            "std_deviation_outstanding_monthly_debts_payments_from_loan REAL,"
                            "std_deviation_outsytanding_monthly_debt_payments_prior_to_loan REAL,"
                            "std_deviation_amountto_pay_at_next_insstallment REAL,"
                            "std_deviation_default_risk_score REAL,"
                            "std_deviation_loan_viability_score REAL,"
                            "std_deviation_adjusted_loan_viability_score REAL,"
                            "std_deviation_potential_profit_from_loan REAL,"
                            "numAgrade INTEGER,"
                            "numBgrade INTEGER,"
                            "numcgrade INTEGER,"
                            "numDgrade INTEGER,"
                            "numEgrade INTEGER,"
                            "numFgrade INTEGER,"
                            "numAppliedToday INTEGER"
                            ");";
        }


        string modeToString(const vector<double> data)
        {
            string values;

            for(int count = 0; count < data.size(); count++)
            {
                if(count == (data.size() - 1))
                {
                    values = values + to_string(data[count]);

                }
                else
                {
                    values = values + to_string(data[count]) + ("-");
                }
            }

            return "'" + values + "'";
        }


        void createSqlStmts()
        {
            string stringFinalSqlInsertStatement;


            sqlInsertFormat = prepareSqlInsertStmt();


            stringFinalSqlInsertStatement = "'" + timeOfReportCreation + "',";
            stringFinalSqlInsertStatement = stringFinalSqlInsertStatement 
            + to_string(meanCreditScore) + ","
            + to_string(meanDurationToNextInstallmentDays) + ","
            + to_string(meanMonthlyIncome) + ","
            + to_string(meanFinancialReserves) + ","
            + to_string(meanDebtToIncomeRatio) + ","
            + to_string(meanLoanDuration) + ","
            + to_string(meanRequestedLoanAmount) + ","
            + to_string(meanMonthlyInterestRate) + ","
            + to_string(meanYearlyInterestRate) + ","
            + to_string(meanLossGivenDefault) + ","
            + to_string(meanRecoveryRate) + ","
            + to_string(meanOutstandingMonthlyDebtsPaymentsFromLoan) + ","
            + to_string(meanOutsytandingMonthlyDebtPaymentsPriorToLoan) + ","
            + to_string(meanAmounttoPayAtNextInsstallment) + ","
            + to_string(meanDefaultRiskScore) + ","
            + to_string(meanLoanViabilityScore) + ","
            + to_string(meanAdjustedLoanViabilityScore) + ","
            + to_string(meanPotentialProfitFromLoan) + ","
            + to_string(sumPotentialProfitFromLoan) + ","
            + to_string(medianCreditScore) + ","
            + to_string(medianDurationToNextInstallmentDays) + ","
            + to_string(medianMonthlyIncome) + ","
            + to_string(medianFinancialReserves) + ","
            + to_string(medianDebtToIncomeRatio) + ","
            + to_string(medianLoanDuration) + ","
            + to_string(medianRequestedLoanAmount) + ","
            + to_string(medianMonthlyInterestRate) + ","
            + to_string(medianYearlyInterestRate) + ","
            + to_string(medianLossGivenDefault) + ","
            + to_string(medianRecoveryRate) + ","
            + to_string(medianOutstandingMonthlyDebtsPaymentsFromLoan) + ","
            + to_string(medianOutsytandingMonthlyDebtPaymentsPriorToLoan) + ","
            + to_string(medianAmounttoPayAtNextInsstallment) + ","
            + to_string(medianDefaultRiskScore) + ","
            + to_string(medianLoanViabilityScore) + ","
            + to_string(medianAdjustedLoanViabilityScore) + ","
            + to_string(medianPotentialProfitFromLoan) + ","
            + modeToString(modeCreditScore) + ","
            + modeToString(modeDurationToNextInstallmentDays) + ","
            + modeToString(modeMonthlyIncome) + ","
            + modeToString(modeFinancialReserves) + ","
            + modeToString(modeDebtToIncomeRatio) + ","
            + modeToString(modeLoanDuration) + ","
            + modeToString(modeRequestedLoanAmount) + ","
            + modeToString(modeMonthlyInterestRate) + ","
            + modeToString(modeYearlyInterestRate) + ","
            + modeToString(modeLossGivenDefault) + ","
            + modeToString(modeRecoveryRate) + ","
            + modeToString(modeOutstandingMonthlyDebtsPaymentsFromLoan) + ","
            + modeToString(modeOutsytandingMonthlyDebtPaymentsPriorToLoan) + ","
            + modeToString(modeAmounttoPayAtNextInsstallment) + ","
            + modeToString(modeDefaultRiskScore) + ","
            + modeToString(modeLoanViabilityScore) + ","
            + modeToString(modeAdjustedLoanViabilityScore) + ","
            + modeToString(modePotentialProfitFromLoan) + ","
            + to_string(stdDeviationCreditScore) + ","
            + to_string(stdDeviationDurationToNextInstallmentDays) + ","
            + to_string(stdDeviationMonthlyIncome) + ","
            + to_string(stdDeviationFinancialReserves) + ","
            + to_string(stdDeviationDebtToIncomeRatio) + ","
            + to_string(stdDeviationLoanDuration) + ","
            + to_string(stdDeviationRequestedLoanAmount) + ","
            + to_string(stdDeviationMonthlyInterestRate) + ","
            + to_string(stdDeviationYearlyInterestRate) + ","
            + to_string(stdDeviationLossGivenDefault) + ","
            + to_string(stdDeviationRecoveryRate) + ","
            + to_string(stdDeviationOutstandingMonthlyDebtsPaymentsFromLoan) + ","
            + to_string(stdDeviationOutsytandingMonthlyDebtPaymentsPriorToLoan) + ","
            + to_string(stdDeviationAmounttoPayAtNextInsstallment) + ","
            + to_string(stdDeviationDefaultRiskScore) + ","
            + to_string(stdDeviationLoanViabilityScore) + ","
            + to_string(stdDeviationAdjustedLoanViabilityScore) + ","
            + to_string(stdDeviationPotentialProfitFromLoan) + ","
            + to_string(numAgrade) + ","
            + to_string(numBgrade) + ","
            + to_string(numcgrade) + ","
            + to_string(numDgrade) + ","
            + to_string(numEgrade) + ","
            + to_string(numFgrade) + ","
            + to_string(numAppliedToday);

            stringSqlInsertData = "INSERT INTO reports ("
                            "date_of_report, "
                            "mean_credit_score, "
                            "mean_duration_to_next_installment_days, "
                            "mean_monthly_income, "
                            "mean_financial_reserves, "
                            "mean_debt_to_income_ratio, "
                            "mean_loan_duration, "
                            "mean_requested_loan_amount, "
                            "mean_monthly_interest_rate, "
                            "mean_yearly_interest_rate, "
                            "mean_loss_given_default, "
                            "mean_recovery_rate, "
                            "mean_outstanding_monthly_debts_payments_from_loan, "
                            "mean_outsytanding_monthly_debt_payments_prior_to_loan, "
                            "mean_amountto_pay_at_next_insstallment, "
                            "mean_default_risk_score, "
                            "mean_loan_viability_score, "
                            "mean_adjusted_loan_viability_score, "
                            "mean_potential_profit_from_loan, "
                            "sum_potential_profit_from_loan, "
                            "median_credit_score, "
                            "median_duration_to_next_installment_days, "
                            "median_monthly_income, "
                            "median_financial_reserves, "
                            "median_debt_to_income_ratio, "
                            "median_loan_duration, "
                            "median_requested_loan_amount, "
                            "median_monthly_interest_rate, "
                            "median_yearly_interest_rate, "
                            "median_loss_given_default, "
                            "median_recovery_rate, "
                            "median_outstanding_monthly_debts_payments_from_loan, "
                            "median_outsytanding_monthly_debt_payments_prior_to_loan, "
                            "median_amountto_pay_at_next_insstallment, "
                            "median_default_risk_score, "
                            "median_loan_viability_score, "
                            "median_adjusted_loan_viability_score, "
                            "median_potential_profit_from_loan, "
                            "mode_credit_score, "
                            "mode_duration_to_next_installment_days, "
                            "mode_monthly_income, "
                            "mode_financial_reserves, "
                            "mode_debt_to_income_ratio, "
                            "mode_loan_duration, "
                            "mode_requested_loan_amount, "
                            "mode_monthly_interest_rate, "
                            "mode_yearly_interest_rate, "
                            "mode_loss_given_default, "
                            "mode_recovery_rate, "
                            "mode_outstanding_monthly_debts_payments_from_loan, "
                            "mode_outsytanding_monthly_debt_payments_prior_to_loan, "
                            "mode_amountto_pay_at_next_insstallment, "
                            "mode_default_risk_score, "
                            "mode_loan_viability_score, "
                            "mode_adjusted_loan_viability_score, "
                            "mode_potential_profit_from_loan, "
                            "std_deviation_credit_score, "
                            "std_deviation_duration_to_next_installment_days, "
                            "std_deviation_monthly_income, "
                            "std_deviation_financial_reserves, "
                            "std_deviation_debt_to_income_ratio, "
                            "std_deviation_loan_duration, "
                            "std_deviation_requested_loan_amount, "
                            "std_deviation_monthly_interest_rate, "
                            "std_deviation_yearly_interest_rate, "
                            "std_deviation_loss_given_default, "
                            "std_deviation_recovery_rate, "
                            "std_deviation_outstanding_monthly_debts_payments_from_loan, "
                            "std_deviation_outsytanding_monthly_debt_payments_prior_to_loan, "
                            "std_deviation_amountto_pay_at_next_insstallment, "
                            "std_deviation_default_risk_score, "
                            "std_deviation_loan_viability_score, "
                            "std_deviation_adjusted_loan_viability_score, "
                            "std_deviation_potential_profit_from_loan, "
                            "numAgrade, "
                            "numBgrade, "
                            "numcgrade, "
                            "numDgrade, "
                            "numEgrade, "
                            "numFgrade, "
                            "numAppliedToday" 
                            ") VALUES (" + stringFinalSqlInsertStatement + ");";


        }
        

    public:
        void update(userDataFromDb data)
        {
            time_t rawTime;
            time(&rawTime);
            timeOfReportCreation = ctime(&rawTime);

            char finalLoanGrade = data.getFinalLoanGrade();
            string completedLoanStatus = data.getLoanStatus();

            creditScoreData.push_back(data.getCreditScore());
            durationToNextInstallmentDaysData.push_back(data.getDurationToNextInstallmentDays());
            monthlyIncomeData.push_back(data.getMonthlyIncome());
            financialReservesData.push_back(data.getFinancialReserves());
            debtToIncomeRatioData.push_back(data.getDebtToIncomeRatio());
            loanDurationData.push_back(data.getLoanDuration());
            requestedLoanAmountData.push_back(data.getRequestedLoanAmount());
            monthlyInterestRateData.push_back(data.getMonthlyInterestRate());
            yearlyInterestRateData.push_back(data.getYearlyInterestRate());
            lossGivenDefaultData.push_back(data.getLossGivenDefault());
            recoveryRateData.push_back(data.getRecoveryRate());
            outstandingMonthlyDebtsPaymentsFromLoanData.push_back(data.getOutstandingMonthlyDebtsPaymentsFromLoan());
            outsytandingMonthlyDebtPaymentsPriorToLoanData.push_back(data.getOutsytandingMonthlyDebtPaymentsPriorToLoan());
            amounttoPayAtNextInsstallmentData.push_back(data.getAmounttoPayAtNextInsstallment());
            defaultRiskScoreData.push_back(data.getDefaultRiskScore());
            loanViabilityScoreData.push_back(data.getLoanViabilityScore());
            adjustedLoanViabilityScoreData.push_back(data.getAdjustedLoanViabilityScore());
            sumPotentialProfitFromLoan = sumPotentialProfitFromLoan + data.getPotentialProfitFromLoan();

            // sumPotentialProfitFromLoan


            if(finalLoanGrade == 'A')
            {
                numAgrade++;
            }
            else if(finalLoanGrade == 'B')
            {
                numBgrade++;
            }
            else if(finalLoanGrade == 'C')
            {
                numcgrade++;
            }
            else if(finalLoanGrade == 'D')
            {
                numDgrade++;
            }
            else if(finalLoanGrade == 'E')
            {
                numEgrade++;
            }
            else if(finalLoanGrade == 'F')
            {
                numFgrade++;
            }

            // comple
            numAppliedToday++;
        }


        void processStats()
        {
            meanCreditScore = stats::getMean(creditScoreData);
            meanDurationToNextInstallmentDays = stats::getMean(durationToNextInstallmentDaysData);
            meanMonthlyIncome = stats::getMean(monthlyIncomeData);
            meanFinancialReserves = stats::getMean(financialReservesData);
            meanDebtToIncomeRatio = stats::getMean(debtToIncomeRatioData);
            meanLoanDuration = stats::getMean(loanDurationData);
            meanRequestedLoanAmount = stats::getMean(requestedLoanAmountData);
            meanMonthlyInterestRate = stats::getMean(monthlyInterestRateData);
            meanYearlyInterestRate = stats::getMean(yearlyInterestRateData);
            meanLossGivenDefault = stats::getMean(lossGivenDefaultData);
            meanRecoveryRate = stats::getMean(recoveryRateData);
            meanOutstandingMonthlyDebtsPaymentsFromLoan = stats::getMean(outstandingMonthlyDebtsPaymentsFromLoanData);
            meanOutsytandingMonthlyDebtPaymentsPriorToLoan = stats::getMean(outsytandingMonthlyDebtPaymentsPriorToLoanData);
            meanAmounttoPayAtNextInsstallment = stats::getMean(amounttoPayAtNextInsstallmentData);
            meanDefaultRiskScore = stats::getMean(defaultRiskScoreData);
            meanLoanViabilityScore = stats::getMean(loanViabilityScoreData);
            meanAdjustedLoanViabilityScore = stats::getMean(adjustedLoanViabilityScoreData);

            medianCreditScore = stats::getMedian(creditScoreData);
            medianDurationToNextInstallmentDays = stats::getMedian(durationToNextInstallmentDaysData);
            medianMonthlyIncome = stats::getMedian(monthlyIncomeData);
            medianFinancialReserves = stats::getMedian(financialReservesData);
            medianDebtToIncomeRatio = stats::getMedian(debtToIncomeRatioData);
            medianLoanDuration = stats::getMedian(loanDurationData);
            medianRequestedLoanAmount = stats::getMedian(requestedLoanAmountData);
            medianMonthlyInterestRate = stats::getMedian(monthlyInterestRateData);
            medianYearlyInterestRate = stats::getMedian(yearlyInterestRateData);
            medianLossGivenDefault = stats::getMedian(lossGivenDefaultData);
            medianRecoveryRate = stats::getMedian(recoveryRateData);
            medianOutstandingMonthlyDebtsPaymentsFromLoan = stats::getMedian(outstandingMonthlyDebtsPaymentsFromLoanData);
            medianOutsytandingMonthlyDebtPaymentsPriorToLoan = stats::getMedian(outsytandingMonthlyDebtPaymentsPriorToLoanData);
            medianAmounttoPayAtNextInsstallment = stats::getMedian(amounttoPayAtNextInsstallmentData);
            medianDefaultRiskScore = stats::getMedian(defaultRiskScoreData);
            medianLoanViabilityScore = stats::getMedian(loanViabilityScoreData);
            medianAdjustedLoanViabilityScore = stats::getMedian(adjustedLoanViabilityScoreData);

            modeCreditScore = stats::getMode(creditScoreData);
            modeDurationToNextInstallmentDays = stats::getMode(durationToNextInstallmentDaysData);
            modeMonthlyIncome = stats::getMode(monthlyIncomeData);
            modeFinancialReserves = stats::getMode(financialReservesData);
            modeDebtToIncomeRatio = stats::getMode(debtToIncomeRatioData);
            modeLoanDuration = stats::getMode(loanDurationData);
            modeRequestedLoanAmount = stats::getMode(requestedLoanAmountData);
            modeMonthlyInterestRate = stats::getMode(monthlyInterestRateData);
            modeYearlyInterestRate = stats::getMode(yearlyInterestRateData);
            modeLossGivenDefault = stats::getMode(lossGivenDefaultData);
            modeRecoveryRate = stats::getMode(recoveryRateData);
            modeOutstandingMonthlyDebtsPaymentsFromLoan = stats::getMode(outstandingMonthlyDebtsPaymentsFromLoanData);
            modeOutsytandingMonthlyDebtPaymentsPriorToLoan = stats::getMode(outsytandingMonthlyDebtPaymentsPriorToLoanData);
            modeAmounttoPayAtNextInsstallment = stats::getMode(amounttoPayAtNextInsstallmentData);
            modeDefaultRiskScore = stats::getMode(defaultRiskScoreData);
            modeLoanViabilityScore = stats::getMode(loanViabilityScoreData);
            modeAdjustedLoanViabilityScore = stats::getMode(adjustedLoanViabilityScoreData);
            modePotentialProfitFromLoan = stats::getMode(potentialProfitFromLoan);


            stdDeviationCreditScore = stats::getStandardDeviation(creditScoreData);
            stdDeviationDurationToNextInstallmentDays = stats::getStandardDeviation(durationToNextInstallmentDaysData);
            stdDeviationMonthlyIncome = stats::getStandardDeviation(monthlyIncomeData);
            stdDeviationFinancialReserves = stats::getStandardDeviation(financialReservesData);
            stdDeviationDebtToIncomeRatio = stats::getStandardDeviation(debtToIncomeRatioData);
            stdDeviationLoanDuration = stats::getStandardDeviation(loanDurationData);
            stdDeviationRequestedLoanAmount = stats::getStandardDeviation(requestedLoanAmountData);
            stdDeviationMonthlyInterestRate = stats::getStandardDeviation(monthlyInterestRateData);
            stdDeviationYearlyInterestRate = stats::getStandardDeviation(yearlyInterestRateData);
            stdDeviationLossGivenDefault = stats::getStandardDeviation(lossGivenDefaultData);
            stdDeviationRecoveryRate = stats::getStandardDeviation(recoveryRateData);
            stdDeviationOutstandingMonthlyDebtsPaymentsFromLoan = stats::getStandardDeviation(outstandingMonthlyDebtsPaymentsFromLoanData);
            stdDeviationOutsytandingMonthlyDebtPaymentsPriorToLoan = stats::getStandardDeviation(outsytandingMonthlyDebtPaymentsPriorToLoanData);
            stdDeviationAmounttoPayAtNextInsstallment = stats::getStandardDeviation(amounttoPayAtNextInsstallmentData);
            stdDeviationDefaultRiskScore = stats::getStandardDeviation(defaultRiskScoreData);
            stdDeviationLoanViabilityScore = stats::getStandardDeviation(loanViabilityScoreData);
            stdDeviationAdjustedLoanViabilityScore = stats::getStandardDeviation(adjustedLoanViabilityScoreData);


            

            createSqlStmts();
            // cout << sqlInsertFormat << endl;
            // cout << stringSqlInsertData << endl;

        }


        string getSqlInsertFormat()
        {
            return sqlInsertFormat;
        }


        string getInsertStatementWithData()
        {
            return stringSqlInsertData;
        }
    };


   
}