#pragma once

#include <time.h>
#include <string>
#include <cmath>
#include "constants.h"
#include "loanDatabaseManager.h"
#include "stats.h"

namespace Processor
{
    using namespace std;

    class loanUpdates
    {
    private:
        int loanId;
        string durationToNextInstallmentDays;
        // string durationToLoanSettlementMonths;
        char finalLoanGrade;
        // double amountOfCurrentLoanAndInterestsLeft;
        int loanDecision;
        string loanStatus;
        int appliedToday;
        bool changeInstallmentDate;
        bool endOfTermCopyingDone;
        
    public:
        // double amountOfCurrentLoanAndInterestsLeft;
        string getDurationToNextInstallmentDays()
        { 
            return durationToNextInstallmentDays;
        }
        // string getDurationToLoanSettlementMonths()
        // {
        //     return durationToLoanSettlementMonths;
        // }
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
        bool getChangeInstallmentDate()
        {
            return changeInstallmentDate;
        }
        int getEndOfTermCopyingDone()
        {
            return endOfTermCopyingDone;
        }
        void setLoanId(int id)
        {
            this -> loanId = id;
        }
        void setDurationToNextInstallmentDays(string duration)
        { 
            this -> durationToNextInstallmentDays = duration;
        }
        // void setDurationToLoanSettlementMonths(string duration)
        // {
        //     this -> durationToLoanSettlementMonths = duration;
        // }
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
        void setChangeInstallmentDate(bool val)
        {
            this -> changeInstallmentDate = val;
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

        double durationToNextInstallmentDays;
        double previousDurationToNextInstallmentDays;

        string monthlyInstallmentDueDate;
        string nextMonthlyInstallmentDate = "";
        string loanDueDate;
        bool changeInstallmentDate = false;

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


        string encapsulateStringForDb(string value)
        {
            return "'" + value + "'";
        }


        int processDurationToNextInstallment(string date)
        {

            // cout << "Duration to next Installment days inside: " << durationToNextInstallmentDays << endl;

            if(durationToNextInstallmentDays == 0 && durationToLoanSettlementMonths > 0)
            {
            
                tm dateVal = timeManip::convertDateStrToTmStruct(date);
                nextMonthlyInstallmentDate = timeManip::getDateNMonthsFromDateStr(&dateVal, 1);
                // cout << "next Installment days: " << nextMonthlyInstallmentDate << endl;
                changeInstallmentDate = true;
                
                return 31;
            }
            else if(durationToNextInstallmentDays > 0)
            {
                return durationToNextInstallmentDays - 1;  
            }
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


    public:
        userDataFromDb(vector <string> data, string date)
        {
            time_t timeOfMonthlyInstallment, timeOfLoanDueDate;
            databaseManager::userDataFromDb convertedData(data);
            
            time_t todayTimeIrrelevant = timeManip::createDateFromStringTimeIrrelevant(date);
            
            loanId = convertedData.getLoanId();
            userName = convertedData.getUserName();
            timeOfApplication = convertedData.getTimeOfApplication();
            creditScore = convertedData.getCreditScore();
            monthlyIncome = convertedData.getMonthlyIncome();
            financialReserves = convertedData.getFinancialReserves();
            debtToIncomeRatio = convertedData.getDebtToIncomeRatio();
            loanDuration = convertedData.getLoanDuration();
            monthlyInstallmentDueDate = convertedData.getDateOfNextInstallments();
            loanDueDate = convertedData.getLoanSettlementDate();

            timeOfMonthlyInstallment = timeManip::createDateFromStringTimeIrrelevant(monthlyInstallmentDueDate);
            timeOfLoanDueDate = timeManip::createDateFromStringTimeIrrelevant(loanDueDate);

            durationToNextInstallmentDays =  (abs(timeManip::convSecsToDays(difftime(timeOfMonthlyInstallment, todayTimeIrrelevant))));
            durationToLoanSettlementMonths = ((int)(timeManip::convSecsToMonths(difftime(timeOfLoanDueDate, todayTimeIrrelevant))));

            // cout << endl;
            // cout << ctime(&todayTimeIrrelevant) << endl;
            // cout << "Entered installment due date: " << monthlyInstallmentDueDate << endl;
            // cout << "Converted installment due date: " << ctime(&timeOfMonthlyInstallment) << endl;
            // cout << "Entered loan due date: " << loanDueDate << endl;
            // cout << "Converted loan due date: " << ctime(&timeOfLoanDueDate) << endl;

            // cout << "Duration to next Installment days: " << durationToNextInstallmentDays << endl;
            // cout << "Duration to settlement months: " << durationToLoanSettlementMonths << endl;

            // cout << endl;


            requestedLoanAmount = convertedData.getRequestedLoanAmount();
            monthlyInterestRate = convertedData.getMonthlyInterestRate();
            yearlyInterestRate = convertedData.getYearlyInterestRate();
            lossGivenDefault = convertedData.getLossGivenDefault();
            recoveryRate = convertedData.getRecoveryRate();
            outstandingMonthlyDebtsPaymentsFromLoan = convertedData.getOutstandingMonthlyDebtsPaymentsFromLoan();
            outsytandingMonthlyDebtPaymentsPriorToLoan = convertedData.getOutsytandingMonthlyDebtPaymentsPriorToLoan();
            amounttoPayAtNextInsstallment = convertedData.getAmounttoPayAtNextInsstallment();
            defaultRiskScore = convertedData.getDefaultRiskScore();
            loanViabilityScore = convertedData.getLoanViabilityScore();
            adjustedLoanViabilityScore = convertedData.getAdjustedLoanViabilityScore();
            matrixBasedAdjustedLoanViabilityScore = convertedData.getMatrixBasedAdjustedLoanViabilityScore();
            interestRateByGroup = convertedData.getInterestRateByGroup();
            bestPossibleYearlyRate = convertedData.getBestPossibleYearlyRate();
            worstPossibleYearlyRate = convertedData.getWorstPossibleYearlyRate();
            finalLoanGrade = convertedData.getFinalLoanGrade();
            potentialProfitFromLoan = convertedData.getPotentialProfitFromLoan();
            calculatedBestPossibleLoanViabilityScore = convertedData.getCalculatedBestPossibleAdjustedLoanViabilityScore();
            calculatedWorstPossibleLoanViabilityScore = convertedData.getCalculatedWorstpossibleAdjustedLoanViabilityScore();
            amountOfCurrentLoanAndInteerestsLeft = convertedData.getAmountOfCurrentLoanAndInteerestsLeft();
            loanDecision = convertedData.getLoanDecision();
            loanStatus = convertedData.getLoanStatus();
            appliedToday = convertedData.getAppliedToday();
            accountNumber = convertedData.getAccountNumber();
            endOfTermCopyingDone = convertedData.getEndOfTermCopyingDone();

            previousDurationToNextInstallmentDays = durationToNextInstallmentDays;



            if(appliedToday == true)
            {
                finalLoanGrade = processFinalLoanGrade();
                loanDecision = processLoanDecision();
            }
            else
            {
                // if((loanStatus != "Completed"))
                // {
                // cout << "Duration to next Installment days: " << durationToNextInstallmentDays << endl;
                durationToNextInstallmentDays = processDurationToNextInstallment(monthlyInstallmentDueDate);
                // cout << "Duration to next Installment days: " << durationToNextInstallmentDays << endl;
                // durationToLoanSettlementMonths = processDurationToLoanSettlementMonths();
                // }
            }

            loanStatus = updateLoanStatus();
            appliedToday = int(false);


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
            data.setChangeInstallmentDate(changeInstallmentDate);
            data.setDurationToNextInstallmentDays(nextMonthlyInstallmentDate);
            // data.setDurationToLoanSettlementMonths(durationToLoanSettlementMonths);
            data.setFinalLoanGrade(this -> finalLoanGrade);
            data.setLoanDecision(this -> loanDecision);
            data.setLoanStatus(this -> loanStatus);
            data.setEndOfTermCopyingDone(this -> endOfTermCopyingDone);

            return data;
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
                            "mean_amount_to_pay_at_next_insstallment REAL,"
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
                            "mean_amount_to_pay_at_next_insstallment, "
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