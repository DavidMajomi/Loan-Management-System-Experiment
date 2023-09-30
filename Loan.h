#ifndef LOAN_H_INCLUDED
#define LOAN_H_INCLUDED

#include "constants.h"
#include "EconomicMetrics.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

EconomicMetrics CURRENT_METRICS;    // This class stores financial metrics recieved from external program using the dll file. Its vales are the
                                    // first to be mdifies before performing any operations.
class Loan
{
private:
    unsigned short int creditScore, duration;
    string userName;
    double loanAmount, finalMonthlyInterestRate, monthlyIncome, financialReserves, debtToIncomeRatio, recoveryRate, monthlyDebtPaymentsFromLoan,
           outstandingMonthlyDebtPaymentsPriorToLoan, totalMonthlyDebtPaymentsAfterLoan, lossGivenDefault, defaultRiskScore, loanViabilityScore,
           finalAdjustedViabilityScore, interestRateByGroup, bestPossibleRate = CURRENT_METRICS.getSuperPrimeRate(), worstPossibleRate = CURRENT_METRICS.getDeepSubPrimeRate();


    static double normalizeScore(double rawScore, double maxScore, double minScore);

    double calculateDefaultRisk ();  // function not needed now since calc interest rate is not complete
    
    void simple_set_credit_metrics();

    void set_monthly_debt_payments ()
    {
        monthlyDebtPaymentsFromLoan = loanAmount / duration;
        outstandingMonthlyDebtPaymentsPriorToLoan = monthlyIncome * debtToIncomeRatio;
        totalMonthlyDebtPaymentsAfterLoan = outstandingMonthlyDebtPaymentsPriorToLoan + monthlyDebtPaymentsFromLoan;
    }

public:
    double adjustLoanViabiltyScore (double rawLoanViabilityScore);
    static double calculateWorstCreditMetrics();
    static double calculateBestCreditMetrics();
    // static double calculateLoanViabilityScore(double normalizedCreditScore, double normalizedmonthlyIncome, double debtToIncomeRatio, double normalizedLoanAmount, double normalizedDuration, double lossGivenDefault, double normalizedFinancialReserves, double defaultRiskScore);
    double calculateInterestForDefaultRisk ();
    void setFinalMonthlyInterestRate ();
    Loan(int values)
    {

    }
    void setCreditScore (int creditScoreValue)
    {
        creditScore = creditScoreValue;
    }
    void setUserName (string name)
    {
        userName = name;
    }
    void setLoanAmount (double amount)
    {
        loanAmount = amount;
    }
    void setLoanDuration(int loanDuration)
    {
        duration = loanDuration;
    }
    void setMonthlyIncome (double income)
    {
        monthlyIncome = income;
    }
    void setFinancialReserves(double financialReserveValues)
    {
        financialReserves = financialReserveValues;
    }
    void setDebtToIncomeRatio (double debtToIncomeRatioValue)
    {
        debtToIncomeRatio = debtToIncomeRatioValue; // outstanding dti prior to loan
    }
    void computeCreditData ()
    {
        simple_set_credit_metrics();
    }
    string getUserName() const
    {
        return userName;
    }
    int getCreditScore () const
    {
        return creditScore;
    }
    double getMonthlyIncome () const
    {
        return monthlyIncome;
    }
    double getFinancialReserves () const
    {
        return financialReserves;
    }
    double getDebtToIncomeRatio() const
    {
        return debtToIncomeRatio;
    }
    int getDurationInMonths() const
    {
        return duration;
    }
    double getLoanAmount() const
    {
        return loanAmount;
    }
    double getMonthlyInterestRate() const
    {
        return finalMonthlyInterestRate;
    }
    double getYearlyInterestRate () const
    {
        return finalMonthlyInterestRate * 12;
    }
    double getLossGivenDefault() const
    {
        return lossGivenDefault;
    }
    double getRecoveryRate () const
    {
        return recoveryRate;
    }
    double getTotalOutstandingMonthlyDebtPaymentsAfterLoan () const
    {
        return totalMonthlyDebtPaymentsAfterLoan;
    }
    double getDefaultRiskScore () const
    {
        return defaultRiskScore;
    }
    double getLoanViabilityScore () const
    {
        return loanViabilityScore;
    }
    double getFinalAdjustedLoanViabilityScore() const
    {
        return finalAdjustedViabilityScore;
    }
    double getInterestRateByGroup() const
    {
        return interestRateByGroup;
    }
    double getBestPossibleRate() const
    {
        return bestPossibleRate;
    }
    double getWorstPossibleRate() const
    {
        return worstPossibleRate;
    }
};


double Loan::normalizeScore(double rawScore, double maxScore, double minScore)
{
    unsigned short int maxScaleValue = 1, minScaleValue = 0;
    double normalizedScore;

    normalizedScore = ((rawScore - minScore) / (maxScore - minScore)) * (maxScaleValue - minScaleValue) + (minScaleValue);

    return normalizedScore;
}


double calculateLoanViabilityScore(double normalizedCreditScore, double normalizedmonthlyIncome, double debtToIncomeRatio, 
                                   double normalizedLoanAmount, double normalizedDuration, double lossGivenDefault, 
                                   double normalizedFinancialReserves, double defaultRiskScore)
{
    double loanViabilityScore;

    loanViabilityScore = (normalizedCreditScore * CREDIT_SCORE_WEIGHT) + (normalizedmonthlyIncome * MONTHLY_INCOME_WEIGHT) + 
                         (debtToIncomeRatio * DEBT_TO_INCOME_RATIO_WEIGHT)  + (normalizedLoanAmount * LOAN_AMOUNT_WEIGHT) + (normalizedDuration * LOAN_DURATION_WEIGHT) +
                         (lossGivenDefault * LOSS_GIVEN_DEFAULT_WEIGHT) + (normalizedFinancialReserves * FINANCIAL_RESERVES_WEIGHT) + (defaultRiskScore * DEFAULT_RISK_SCORE_WEIGHT);


    return loanViabilityScore;
}


double Loan::calculateBestCreditMetrics()
{
    double loanViabilityScore, normalizedCreditScore, normalizedmonthlyIncome, normalizedLoanAmount, normalizedInterest, normalizedDuration, normalizedFinancialReserves;

    normalizedCreditScore =  Loan::normalizeScore(MAX_CREDIT_SCORE, MAX_CREDIT_SCORE, MIN_CREDIT_SCORE);
    normalizedDuration = Loan::normalizeScore(MAX_LOAN_DURATION, MAX_LOAN_DURATION, MIN_LOAN_DURATION);
    normalizedFinancialReserves = Loan::normalizeScore(MAX_FINANCIAL_RESERVES, MAX_FINANCIAL_RESERVES, MIN_FINANCIAL_RESERVES);
    normalizedInterest = Loan::normalizeScore(BEST_FINAL_MONTHLY_INTEREST_RATE, MAX_INTEREST_RATE, MIN_INTEREST_RATE);
    normalizedmonthlyIncome = Loan::normalizeScore(MAX_MONTHLY_INCOME, MAX_MONTHLY_INCOME, MIN_MONTHLY_INCOME);
    normalizedLoanAmount = Loan::normalizeScore(MIN_LOAN_AMOUNT, MAX_LOAN_AMOUNT, MIN_LOAN_AMOUNT);
    // normalizedDefaultRiskScore = normalizeScore(BEST_DEFAULT_RISK_SCORE, MAX_LOAN_AMOUNT, MIN_LOAN_AMOUNT);

    // loanViabilityScore = (normalizedCreditScore * CREDIT_SCORE_WEIGHT) + (normalizedmonthlyIncome * MONTHLY_INCOME_WEIGHT) + (BEST_DEBT_TO_INCOME_RATIO * DEBT_TO_INCOME_RATIO_WEIGHT)  
    //                         + (normalizedLoanAmount * LOAN_AMOUNT_WEIGHT) + (normalizedDuration * LOAN_DURATION_WEIGHT)+ (normalizedInterest * INTEREST_RATE_WEIGHT) 
    //                         + (BEST_LOSS_GIVEN_DEFAULT * LOSS_GIVEN_DEFAULT_WEIGHT) + (normalizedFinancialReserves * FINANCIAL_RESERVES_WEIGHT) + (BEST_DEFAULT_RISK_SCORE * DEFAULT_RISK_SCORE_WEIGHT);

    loanViabilityScore = calculateLoanViabilityScore(normalizedCreditScore, normalizedmonthlyIncome, BEST_DEBT_TO_INCOME_RATIO, normalizedLoanAmount, normalizedDuration, BEST_LOSS_GIVEN_DEFAULT, normalizedFinancialReserves, BEST_DEFAULT_RISK_SCORE);

    // cout << " Best loan viability score = " << loanViabilityScore << endl;

    return loanViabilityScore;
}


// Need to review the logic here as well as finding a way to put it in the class we will see how it goes
double Loan::calculateWorstCreditMetrics ()
{
    double loanViabilityScore, normalizedCreditScore, normalizedmonthlyIncome, normalizedLoanAmount, normalizedInterest, normalizedDuration, normalizedFinancialReserves;

    normalizedCreditScore =  Loan::normalizeScore(MIN_CREDIT_SCORE, MAX_CREDIT_SCORE, MIN_CREDIT_SCORE);
    normalizedDuration = Loan::normalizeScore(MIN_LOAN_DURATION, MAX_LOAN_DURATION, MIN_LOAN_DURATION);
    normalizedFinancialReserves = Loan::normalizeScore(MIN_FINANCIAL_RESERVES, MAX_FINANCIAL_RESERVES, MIN_FINANCIAL_RESERVES);
    // normalizedInterest = Loan::normalizeScore(WORST_FINAL_MONTHLY_INTEREST_RATE, MAX_INTEREST_RATE, MIN_INTEREST_RATE);
    normalizedmonthlyIncome = Loan::normalizeScore(MIN_MONTHLY_INCOME, MAX_MONTHLY_INCOME, MIN_MONTHLY_INCOME);
    normalizedLoanAmount = Loan::normalizeScore(MAX_LOAN_AMOUNT, MAX_LOAN_AMOUNT, MIN_LOAN_AMOUNT);

    loanViabilityScore = calculateLoanViabilityScore(normalizedCreditScore, normalizedmonthlyIncome, WORST_DEBT_TO_INCOME_RATIO, normalizedLoanAmount, normalizedDuration, WORST_LOSS_GIVEN_DEFAULT, normalizedFinancialReserves, WORST_DEFAULT_RISK_SCORE);

    // cout << " Worst loan viability score = " << loanViabilityScore << endl;

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
void Loan::setFinalMonthlyInterestRate ()
{
    double baseRate, mathematicalSlope = ((CURRENT_METRICS.getDeepSubPrimeRate() - CURRENT_METRICS.getSuperPrimeRate()) / (-100));
    // double baseRate, mathematicalSlope = ((DEEP_SUBPRIME_RATE - CURRENT_METRICS.getBaseYearlyInterestRatePercentForLoans()) / (-100));

    set_monthly_debt_payments();


    // Think of this as a linear model represented by the equation y = slope(m) * finalAdjustedViabilityScore (x) + getDeepSubPrimeRate (b)
    baseRate = (mathematicalSlope * finalAdjustedViabilityScore) + CURRENT_METRICS.getDeepSubPrimeRate();

    if (baseRate < CURRENT_METRICS.getSuperPrimeRate())
    {
        baseRate = CURRENT_METRICS.getSuperPrimeRate();
    }

    finalMonthlyInterestRate = baseRate / 12;

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
    // cout << " This is best lvs " << bestLoanViabilityScore << endl;
    // cout << " This is worst lvs " << worstLoanViabilityScore << endl;
    // cout << " This is raw lvs " << rawLoanViabilityScore << endl;
    adjustedViabilityScore = (((rawLoanViabilityScore - worstLoanViabilityScore) / (bestLoanViabilityScore - worstLoanViabilityScore)) * (maxScaleValue - minScaleValue)) + (minScaleValue);

    return adjustedViabilityScore;
}


double Loan::calculateDefaultRisk ()  // function not needed now since calc interest rate is not complete
{
    double monthlyInterestRateByCreditGroup, calculatedDefaultRisk;

    monthlyInterestRateByCreditGroup = calculateInterestForDefaultRisk();
    calculatedDefaultRisk = monthlyInterestRateByCreditGroup - CURRENT_METRICS.getBaseMonthlyInterestRatePercentForLoans();

    return calculatedDefaultRisk;
}


// When minimizing inefficiencies in this program, initialize the credit metrics instead of assignning them values after decleration
void Loan::simple_set_credit_metrics ()
{
    double normalizedCreditScore, normalizedmonthlyIncome, normalizedLoanAmount, normalizedInterest, normalizedDuration, 
           normalizedFinancialReserves, normalizedDefaultRiskScore, baseRate = CURRENT_METRICS.getBaseMonthlyInterestRatePercentForLoans();
    
    defaultRiskScore = calculateDefaultRisk();
    
    normalizedCreditScore =  normalizeScore(creditScore, MAX_CREDIT_SCORE, MIN_CREDIT_SCORE);
    normalizedDuration = normalizeScore(duration, MAX_LOAN_DURATION, MIN_LOAN_DURATION);
    normalizedFinancialReserves = normalizeScore(financialReserves, MAX_FINANCIAL_RESERVES, MIN_FINANCIAL_RESERVES);
    normalizedInterest = normalizeScore(finalMonthlyInterestRate, MAX_INTEREST_RATE, MIN_INTEREST_RATE);
    normalizedmonthlyIncome = normalizeScore(monthlyIncome, MAX_MONTHLY_INCOME, MIN_MONTHLY_INCOME);
    normalizedLoanAmount = normalizeScore(loanAmount, MAX_LOAN_AMOUNT, MIN_LOAN_AMOUNT);
    normalizedDefaultRiskScore = normalizeScore(defaultRiskScore, (CURRENT_METRICS.getDeepSubPrimeRate() - baseRate), (CURRENT_METRICS.getSuperPrimeRate() - baseRate));

    // cout << normalizedCreditScore << endl;
    // cout << normalizedDuration << endl;
    // cout << " raw default risk score " << defaultRiskScore << endl;
    // cout << " normalized default risk score " << normalizedDefaultRiskScore << endl;

    lossGivenDefault = (loanAmount - financialReserves) / loanAmount; // SOURCE = WIKIPEDIA
    recoveryRate = 1 - lossGivenDefault;

    loanViabilityScore = calculateLoanViabilityScore(normalizedCreditScore, normalizedmonthlyIncome, debtToIncomeRatio, normalizedLoanAmount, normalizedDuration, lossGivenDefault, normalizedFinancialReserves, normalizedDefaultRiskScore);

    finalAdjustedViabilityScore = adjustLoanViabiltyScore(loanViabilityScore);

    // cout << " This is adjusted Loan viability score: " << finalAdjustedViabilityScore << endl;

}



#endif // LOAN_H_INCLUDED
