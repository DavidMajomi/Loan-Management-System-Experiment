#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "timeManip.h"
#include "matrixCalculator.h"
#include "constants.h"
#include "EconomicMetrics.h"

using namespace std;


EconomicMetrics CURRENT_METRICS;    // This class stores financial metrics recieved from external program using the dll file. Its vales are the
                                    // first to be modified before performing any operations.
class Loan
{
private:
    unsigned short int creditScore, duration;
    string userName, timeOfApplication, loanDueDate, monthlyInstallmentDueDate, sqlInsertFormat, stringSqlInsertData;
    string defaultLoanDecisionProcessing = "2";

    double loanAmount, finalMonthlyInterestRate, monthlyIncome, financialReserves, debtToIncomeRatio, recoveryRate, monthlyDebtPaymentsFromLoan,
           outstandingMonthlyDebtPaymentsPriorToLoan, totalMonthlyDebtPaymentsAfterLoan, lossGivenDefault, defaultRiskScore, finalLoanViabilityScore,
           finalAdjustedLoanViabilityScore, interestRateByGroup, bestPossibleRate = CURRENT_METRICS.getSuperPrimeRate(), worstPossibleRate = CURRENT_METRICS.getDeepSubPrimeRate(),
           calculatedBestPossibleLoanViabilityScore, calculatedWorstPossibleLoanViabilityScore, calculatedBestPossibleAdjustedLoanViabilityScore, 
           calculatedWorstPossibleAdjustedLoanViabilityScore, matrixBasedAdjustedLoanViabilityScore, potentialProfitFromLoan;


    static double normalizeScore(double rawScore, double maxScore, double minScore);

    double calculateDefaultRisk ();  // function not needed now since calc interest rate is not complete

    double calculateWorstCreditMetrics();
    
    double calculateBestCreditMetrics();

    double calculateInterestForDefaultRisk ();
    
    double setFinalLoanViabilityScore();
    

    string encapsulateStringForDb(string value)
    {
        return "'" + value + "'";
    }


    string createSqlInsertData()
    {
        string stringFinalSqlInsertStatement;

        stringFinalSqlInsertStatement = "'" + userName + "'," + "'" + timeOfApplication + "',";
        stringFinalSqlInsertStatement = stringFinalSqlInsertStatement 
        + to_string(creditScore) + "," 
        + to_string(monthlyIncome) + "," 
        + to_string(financialReserves) + "," 
        + to_string(debtToIncomeRatio) + "," 
        + to_string(duration) + "," 
        + encapsulateStringForDb(monthlyInstallmentDueDate) + ","
        + encapsulateStringForDb(loanDueDate) + ","
        + to_string(loanAmount) + "," 
        + to_string(finalMonthlyInterestRate) + "," 
        + to_string(getYearlyInterestRate()) + ","
        + to_string(lossGivenDefault) + "," 
        + to_string(recoveryRate) + ","
        + to_string(outstandingMonthlyDebtPaymentsPriorToLoan + loanAmount) + "," 
        + to_string(outstandingMonthlyDebtPaymentsPriorToLoan) + "," 
        + to_string(loanAmount / duration) + "," 
        + to_string(defaultRiskScore) + "," 
        + to_string(finalLoanViabilityScore) + "," 
        + to_string(finalAdjustedLoanViabilityScore) + "," 
        + to_string(matrixBasedAdjustedLoanViabilityScore) + "," 
        + to_string(interestRateByGroup) + "," 
        + to_string(bestPossibleRate) + ","
        + to_string(worstPossibleRate) + "," 
        + "''"+ "," 
        + to_string(potentialProfitFromLoan) + "," 
        + to_string(calculatedBestPossibleLoanViabilityScore)+ "," 
        + to_string(calculatedWorstPossibleLoanViabilityScore)+ "," 
        + to_string(loanAmount + potentialProfitFromLoan) + "," 
        + defaultLoanDecisionProcessing + "," 
        + "'Processing'" + "," 
        + to_string((int)(true)) + "," 
        + "1234567890" + ","
        + to_string((int)(false));

        
        // cout << stringSqlInsertData << endl;

        return "INSERT INTO users " + USERS_TABLE_INSERT_FORMT + stringFinalSqlInsertStatement + ");"; 
    }


    double calculatePotentialProfitFromLoan()
    {
        return loanAmount * (finalMonthlyInterestRate / 100) * duration;
    }


public:
    double adjustLoanViabiltyScore (double rawLoanViabilityScore);
    // static double calculateWorstCreditMetrics();
    // static double calculateBestCreditMetrics();
    // static double calculateLoanViabilityScore(double normalizedCreditScore, double normalizedmonthlyIncome, double debtToIncomeRatio, double normalizedLoanAmount, double normalizedDuration, double lossGivenDefault, double normalizedFinancialReserves, double defaultRiskScore);
    
    double setFinalMonthlyInterestRate();
    Loan(string newUserName, int creditScoreInteger, double monthlyIncomeDecimal, double financialReservesDecimal, double debtToIncomeRatioDecimal, int durationInMonthsInteger, double loanAmonutRequestedDeciaml)
    {
        time_t rawtime;
        time(&rawtime);
        timeOfApplication = ctime(&rawtime);
        monthlyInstallmentDueDate = timeManip::getDateNMonthsFromDateStr(localtime(&rawtime), 1);
        loanDueDate = timeManip::getDateNMonthsFromDateStr(localtime(&rawtime), durationInMonthsInteger);
        
        this->userName = newUserName;
        creditScore = (creditScoreInteger);
        monthlyIncome = (monthlyIncomeDecimal);
        financialReserves = (financialReservesDecimal);
        debtToIncomeRatio = (debtToIncomeRatioDecimal);
        duration = (durationInMonthsInteger);
        loanAmount = loanAmonutRequestedDeciaml;
        lossGivenDefault = (loanAmount - financialReserves) / loanAmount; // SOURCE = WIKIPEDIA
        recoveryRate = 1 - lossGivenDefault;



        defaultRiskScore = calculateDefaultRisk();
        finalLoanViabilityScore = setFinalLoanViabilityScore();


        finalAdjustedLoanViabilityScore = adjustLoanViabiltyScore(finalLoanViabilityScore);

        calculatedBestPossibleAdjustedLoanViabilityScore = adjustLoanViabiltyScore(calculatedBestPossibleLoanViabilityScore);
        calculatedWorstPossibleAdjustedLoanViabilityScore =  adjustLoanViabiltyScore(calculatedWorstPossibleLoanViabilityScore);

        matrixBasedAdjustedLoanViabilityScore = matrixCalculator::calculateMatrixBasedALVS(calculatedWorstPossibleLoanViabilityScore, 1, calculatedWorstPossibleAdjustedLoanViabilityScore,
                                                                                         calculatedBestPossibleLoanViabilityScore, 1, calculatedBestPossibleAdjustedLoanViabilityScore, finalLoanViabilityScore);

        finalMonthlyInterestRate = setFinalMonthlyInterestRate();
        potentialProfitFromLoan = calculatePotentialProfitFromLoan();

        
        stringSqlInsertData = createSqlInsertData();
        sqlInsertFormat = "CREATE TABLE IF NOT EXISTS users" + USERS_TABLE_COLUMN_FORMAT;
    }
    string getUserName() const{
        return userName;
    }
    int getCreditScore () const{
        return creditScore;
    }
    double getMonthlyIncome () const{
        return monthlyIncome;
    }
    double getFinancialReserves () const{
        return financialReserves;
    }
    double getDebtToIncomeRatio() const{
        return debtToIncomeRatio;
    }
    int getDurationInMonths() const{
        return duration;
    }
    double getLoanAmount() const{
        return loanAmount;
    }
    double getMonthlyInterestRate() const{
        return finalMonthlyInterestRate;
    }
    double getYearlyInterestRate () const{
        return finalMonthlyInterestRate * 12;
    }
    double getLossGivenDefault() const{
        return lossGivenDefault;
    }
    double getRecoveryRate () const{
        return recoveryRate;
    }
    double getTotalOutstandingMonthlyDebtPaymentsAfterLoan () const{
        return totalMonthlyDebtPaymentsAfterLoan;
    }
    double getDefaultRiskScore () const{
        return defaultRiskScore;
    }
    double getLoanViabilityScore () const{
        return finalLoanViabilityScore;
    }
    double getFinalAdjustedLoanViabilityScore() const{
        return finalAdjustedLoanViabilityScore;
    }
    double getInterestRateByGroup() const{
        return interestRateByGroup;
    }
    double getBestPossibleRate() const{
        return bestPossibleRate;
    }
    double getWorstPossibleRate() const{
        return worstPossibleRate;
    }
    string getTimeOfApplication() const{
        return timeOfApplication;
    }
    double getCalculatedBestPossibleLoanViabilityScore() const{
        return calculatedBestPossibleLoanViabilityScore;
    }
    double getCalculatedWorstPossibleLoanViabilityScore() const{
        return calculatedWorstPossibleLoanViabilityScore;
    }
    double getCalculatedBestPossibleAdjustedLoanViabilityScore() const{
        return calculatedBestPossibleAdjustedLoanViabilityScore;
    }
    double getCalculatedWorstPossibleAdjustedLoanViabilityScore() const{
        return calculatedWorstPossibleAdjustedLoanViabilityScore;
    }
    double getMatrixBasedAdjustedLoanViabilityScore() const{
        return matrixBasedAdjustedLoanViabilityScore;
    }
    string getSqlInsertFormat() const{
        return sqlInsertFormat;
    }
    string getInsertStatementWithData() const{
        return stringSqlInsertData;
    }
};


double Loan::normalizeScore(double rawScore, double maxScore, double minScore)
{
    unsigned short int maxScaleValue = 1, minScaleValue = 0;

    return ((rawScore - minScore) / (maxScore - minScore)) * (maxScaleValue - minScaleValue) + (minScaleValue);
}


inline double calculateLoanViabilityScore(double normalizedCreditScore, double normalizedmonthlyIncome, double debtToIncomeRatio, 
                                   double normalizedLoanAmount, double normalizedDuration, double lossGivenDefault, 
                                   double normalizedFinancialReserves, double defaultRiskScore)
{
    return (normalizedCreditScore * CREDIT_SCORE_WEIGHT) + (normalizedmonthlyIncome * MONTHLY_INCOME_WEIGHT) + 
            (debtToIncomeRatio * DEBT_TO_INCOME_RATIO_WEIGHT)  + (normalizedLoanAmount * LOAN_AMOUNT_WEIGHT) + (normalizedDuration * LOAN_DURATION_WEIGHT) +
            (lossGivenDefault * LOSS_GIVEN_DEFAULT_WEIGHT) + (normalizedFinancialReserves * FINANCIAL_RESERVES_WEIGHT) + (defaultRiskScore * DEFAULT_RISK_SCORE_WEIGHT);
}


double Loan::calculateBestCreditMetrics()
{
    double loanViabilityScore, normalizedCreditScore, normalizedmonthlyIncome, normalizedLoanAmount, normalizedDuration, normalizedFinancialReserves;

    normalizedCreditScore =  Loan::normalizeScore(MAX_CREDIT_SCORE, MAX_CREDIT_SCORE, MIN_CREDIT_SCORE);
    normalizedDuration = Loan::normalizeScore(MAX_LOAN_DURATION, MAX_LOAN_DURATION, MIN_LOAN_DURATION);
    normalizedFinancialReserves = Loan::normalizeScore(MAX_FINANCIAL_RESERVES, MAX_FINANCIAL_RESERVES, MIN_FINANCIAL_RESERVES);
    normalizedmonthlyIncome = Loan::normalizeScore(MAX_MONTHLY_INCOME, MAX_MONTHLY_INCOME, MIN_MONTHLY_INCOME);
    normalizedLoanAmount = Loan::normalizeScore(MIN_LOAN_AMOUNT, MAX_LOAN_AMOUNT, MIN_LOAN_AMOUNT);

    loanViabilityScore = calculateLoanViabilityScore(normalizedCreditScore, normalizedmonthlyIncome, BEST_DEBT_TO_INCOME_RATIO, normalizedLoanAmount, normalizedDuration, BEST_LOSS_GIVEN_DEFAULT, normalizedFinancialReserves, BEST_DEFAULT_RISK_SCORE);

    calculatedBestPossibleLoanViabilityScore  = loanViabilityScore;

    return loanViabilityScore;
}


// Need to review the logic here as well as finding a way to put it in the class we will see how it goes
double Loan::calculateWorstCreditMetrics ()
{
    double loanViabilityScore, normalizedCreditScore, normalizedmonthlyIncome, normalizedLoanAmount, normalizedDuration, normalizedFinancialReserves;

    normalizedCreditScore =  Loan::normalizeScore(MIN_CREDIT_SCORE, MAX_CREDIT_SCORE, MIN_CREDIT_SCORE);
    normalizedDuration = Loan::normalizeScore(MIN_LOAN_DURATION, MAX_LOAN_DURATION, MIN_LOAN_DURATION);
    normalizedFinancialReserves = Loan::normalizeScore(MIN_FINANCIAL_RESERVES, MAX_FINANCIAL_RESERVES, MIN_FINANCIAL_RESERVES);
    normalizedmonthlyIncome = Loan::normalizeScore(MIN_MONTHLY_INCOME, MAX_MONTHLY_INCOME, MIN_MONTHLY_INCOME);
    normalizedLoanAmount = Loan::normalizeScore(MAX_LOAN_AMOUNT, MAX_LOAN_AMOUNT, MIN_LOAN_AMOUNT);

    loanViabilityScore = calculateLoanViabilityScore(normalizedCreditScore, normalizedmonthlyIncome, WORST_DEBT_TO_INCOME_RATIO, normalizedLoanAmount, normalizedDuration, WORST_LOSS_GIVEN_DEFAULT, normalizedFinancialReserves, WORST_DEFAULT_RISK_SCORE);

    calculatedWorstPossibleLoanViabilityScore = loanViabilityScore;

    return loanViabilityScore;
}


/**
 * @brief Funtion: It sets a base inteest rate by group used in calculating default risk sourced form CFPB's Market report, as well as Forbe's
 * Average Personal Loan Interest Rates By Credit Score "https://www.forbes.com/advisor/personal-loans/personal-loan-rates/". 
 * The results from the linked article are the foundation of this function, however the values for the rates are modified to better 
 * integrate with this program.
 * 
 * @param baseRate 
 * @return double 
 */
double Loan::calculateInterestForDefaultRisk ()
{
    if (creditScore >= 781)
    {
        interestRateByGroup = CURRENT_METRICS.getSuperPrimeRate();
    }
    else if (creditScore >= 661 && creditScore <= 780)
    {
        interestRateByGroup = CURRENT_METRICS.getPrimeRate();
    }
    else if (creditScore >= 601 && creditScore <= 660)
    {
        interestRateByGroup = CURRENT_METRICS.getNearPrimeRate();
    }
    else if (creditScore >= 500 && creditScore <= 600)
    {
        interestRateByGroup = CURRENT_METRICS.getSubPrimeRate();
    }
    else if (creditScore <= 499)
    {
        interestRateByGroup = CURRENT_METRICS.getDeepSubPrimeRate();
    }

    return interestRateByGroup / 12;
}


/**
 * @brief Funtion: Sets the interest rate based on the adjusted loan viability score. It uses a basic linear model to calculate the interest rate
 * 
 */
double Loan::setFinalMonthlyInterestRate ()
{
    double baseRate, mathematicalSlope = ((CURRENT_METRICS.getDeepSubPrimeRate() - CURRENT_METRICS.getSuperPrimeRate()) / (-100));
    // double baseRate, mathematicalSlope = ((DEEP_SUBPRIME_RATE - CURRENT_METRICS.getBaseYearlyInterestRatePercentForLoans()) / (-100));

    monthlyDebtPaymentsFromLoan = loanAmount / duration;
    outstandingMonthlyDebtPaymentsPriorToLoan = monthlyIncome * debtToIncomeRatio;
    totalMonthlyDebtPaymentsAfterLoan = outstandingMonthlyDebtPaymentsPriorToLoan + monthlyDebtPaymentsFromLoan;


    // Think of this as a linear model represented by the equation y = slope(m) * finalAdjustedLoanViabilityScore (x) + getDeepSubPrimeRate (b)
    baseRate = (mathematicalSlope * finalAdjustedLoanViabilityScore) + CURRENT_METRICS.getDeepSubPrimeRate();

    if (baseRate < CURRENT_METRICS.getSuperPrimeRate())
    {
        baseRate = CURRENT_METRICS.getSuperPrimeRate();
    }

    return baseRate / 12;
}


/**
 * @brief Function: It adjusts the given loan viability score to a sclae between the max scale value and the min scale value.
 * 
 * @param rawLoanViabilityScore 
 * @return double 
 */
double Loan::adjustLoanViabiltyScore (double rawLoanViabilityScore)
{
    unsigned short int maxScaleValue = 100, minScaleValue = 0;
    double adjustedViabilityScore, bestLoanViabilityScore, worstLoanViabilityScore;

    bestLoanViabilityScore = calculateBestCreditMetrics();
    worstLoanViabilityScore = calculateWorstCreditMetrics();
    DISPLAY << " This is best lvs " + to_string( bestLoanViabilityScore);
    DISPLAY << " This is worst lvs " + to_string(worstLoanViabilityScore);
    DISPLAY << " This is raw lvs " + to_string(rawLoanViabilityScore);
    adjustedViabilityScore = (((rawLoanViabilityScore - worstLoanViabilityScore) / (bestLoanViabilityScore - worstLoanViabilityScore)) * (maxScaleValue - minScaleValue)) + (minScaleValue);

    return adjustedViabilityScore;
}


double Loan::calculateDefaultRisk ()  // function not needed now since calc interest rate is not complete
{
    double monthlyInterestRateByCreditGroup, calculatedDefaultRisk;

    monthlyInterestRateByCreditGroup = calculateInterestForDefaultRisk();

    return (monthlyInterestRateByCreditGroup - CURRENT_METRICS.getBaseMonthlyInterestRatePercentForLoans());
}


// When minimizing inefficiencies in this program, initialize the credit metrics instead of assignning them values after decleration
double Loan::setFinalLoanViabilityScore()
{
    double normalizedCreditScore, normalizedmonthlyIncome, normalizedLoanAmount, normalizedInterest, normalizedDuration, 
           normalizedFinancialReserves, normalizedDefaultRiskScore, baseRate = CURRENT_METRICS.getBaseMonthlyInterestRatePercentForLoans();

    normalizedCreditScore =  normalizeScore(creditScore, MAX_CREDIT_SCORE, MIN_CREDIT_SCORE);
    normalizedDuration = normalizeScore(duration, MAX_LOAN_DURATION, MIN_LOAN_DURATION);
    normalizedFinancialReserves = normalizeScore(financialReserves, MAX_FINANCIAL_RESERVES, MIN_FINANCIAL_RESERVES);
    normalizedmonthlyIncome = normalizeScore(monthlyIncome, MAX_MONTHLY_INCOME, MIN_MONTHLY_INCOME);
    normalizedLoanAmount = normalizeScore(loanAmount, MAX_LOAN_AMOUNT, MIN_LOAN_AMOUNT);
    normalizedDefaultRiskScore = normalizeScore(defaultRiskScore, (CURRENT_METRICS.getDeepSubPrimeRate() - baseRate), (CURRENT_METRICS.getSuperPrimeRate() - baseRate));

    // DISPLAY << normalizedCreditScore << ENDLINE;
    // DISPLAY << normalizedDuration << ENDLINE;
    DISPLAY << " raw default risk score " + to_string(defaultRiskScore);
    DISPLAY << " normalized default risk score " + to_string(normalizedDefaultRiskScore);

    
    return calculateLoanViabilityScore(normalizedCreditScore, normalizedmonthlyIncome, debtToIncomeRatio, normalizedLoanAmount, normalizedDuration, lossGivenDefault, normalizedFinancialReserves, normalizedDefaultRiskScore);
}

