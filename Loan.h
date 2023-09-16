#ifndef LOAN_H_INCLUDED
#define LOAN_H_INCLUDED


#include "constants.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


class Loan
{
private:
    unsigned short int creditScore, duration;
    string userName;
    double loanAmount, finalMonthlyInterestRate, monthlyIncome, financialReserves, debtToIncomeRatio, recoveryRate, monthlyDebtPaymentsFromLoan, outstandingMonthlyDebtPaymentsPriorToLoan,
           totalMonthlyDebtPaymentsAfterLoan, lossGivenDefault, defaultRiskScore, loanViabilityScore, finalAdjustedViabilityScore, normalizedCreditScore, normalizedmonthlyIncome, normalizedLoanAmount,
           normalizedInterest, normalizedDuration, normalizedFinancialReserves;


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
    static double calculateLoanViabilityScore(double normalizedCreditScore, double normalizedmonthlyIncome, double debtToIncomeRatio, double normalizedLoanAmount, double normalizedDuration, double lossGivenDefault, double normalizedFinancialReserves, double defaultRiskScore);
    double calculateInterestForDefaultRisk (double baseRate);
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
};


double Loan::normalizeScore(double rawScore, double maxScore, double minScore)
{
    unsigned short int maxScaleValue = 1, minScaleValue = 0;
    double normalizedScore;

    normalizedScore = ((rawScore - minScore) / (maxScore - minScore)) * (maxScaleValue - minScaleValue) + (minScaleValue);

    return normalizedScore;
}


double Loan::calculateLoanViabilityScore(double normalizedCreditScore, double normalizedmonthlyIncome, double debtToIncomeRatio, double normalizedLoanAmount, double normalizedDuration, double lossGivenDefault, double normalizedFinancialReserves, double defaultRiskScore)
{
    double loanViabilityScore;

    loanViabilityScore = (normalizedCreditScore * CREDIT_SCORE_WEIGHT) + (normalizedmonthlyIncome * MONTHLY_INCOME_WEIGHT) + (debtToIncomeRatio * DEBT_TO_INCOME_RATIO_WEIGHT)  + (normalizedLoanAmount * LOAN_AMOUNT_WEIGHT) + (normalizedDuration * LOAN_DURATION_WEIGHT)
                       + (lossGivenDefault * LOSS_GIVEN_DEFAULT_WEIGHT) + (normalizedFinancialReserves * FINANCIAL_RESERVES_WEIGHT) + (defaultRiskScore * DEFAULT_RISK_SCORE_WEIGHT);


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

    // loanViabilityScore = (normalizedCreditScore * CREDIT_SCORE_WEIGHT) + (normalizedmonthlyIncome * MONTHLY_INCOME_WEIGHT) + (BEST_DEBT_TO_INCOME_RATIO * DEBT_TO_INCOME_RATIO_WEIGHT)  
    //                         + (normalizedLoanAmount * LOAN_AMOUNT_WEIGHT) + (normalizedDuration * LOAN_DURATION_WEIGHT)+ (normalizedInterest * INTEREST_RATE_WEIGHT) 
    //                         + (BEST_LOSS_GIVEN_DEFAULT * LOSS_GIVEN_DEFAULT_WEIGHT) + (normalizedFinancialReserves * FINANCIAL_RESERVES_WEIGHT) + (BEST_DEFAULT_RISK_SCORE * DEFAULT_RISK_SCORE_WEIGHT);

    loanViabilityScore = calculateLoanViabilityScore(normalizedCreditScore, normalizedmonthlyIncome, BEST_DEBT_TO_INCOME_RATIO, normalizedLoanAmount, normalizedDuration, BEST_LOSS_GIVEN_DEFAULT, normalizedFinancialReserves, BEST_DEFAULT_RISK_SCORE);

    // //cout << " Best loan viability score = " << loanViabilityScore << endl;

    return loanViabilityScore;
}


// Need to review the logic here as well as finding a way to put it in the class we will see how it goes
double Loan::calculateWorstCreditMetrics ()
{
    double loanViabilityScore, normalizedCreditScore, normalizedmonthlyIncome, normalizedLoanAmount, normalizedInterest, normalizedDuration, normalizedFinancialReserves;

    normalizedCreditScore =  Loan::normalizeScore(MIN_CREDIT_SCORE, MAX_CREDIT_SCORE, MIN_CREDIT_SCORE);
    normalizedDuration = Loan::normalizeScore(MIN_LOAN_DURATION, MAX_LOAN_DURATION, MIN_LOAN_DURATION);
    normalizedFinancialReserves = Loan::normalizeScore(MIN_FINANCIAL_RESERVES, MAX_FINANCIAL_RESERVES, MIN_FINANCIAL_RESERVES);
    normalizedInterest = Loan::normalizeScore(WORST_FINAL_MONTHLY_INTEREST_RATE, MAX_INTEREST_RATE, MIN_INTEREST_RATE);
    normalizedmonthlyIncome = Loan::normalizeScore(MIN_MONTHLY_INCOME, MAX_MONTHLY_INCOME, MIN_MONTHLY_INCOME);
    normalizedLoanAmount = Loan::normalizeScore(MAX_LOAN_AMOUNT, MAX_LOAN_AMOUNT, MIN_LOAN_AMOUNT);

    loanViabilityScore = (normalizedCreditScore * CREDIT_SCORE_WEIGHT) + (normalizedmonthlyIncome * MONTHLY_INCOME_WEIGHT) + (WORST_DEBT_TO_INCOME_RATIO * DEBT_TO_INCOME_RATIO_WEIGHT)  + (normalizedLoanAmount * LOAN_AMOUNT_WEIGHT) + (normalizedDuration * LOAN_DURATION_WEIGHT)
                            + (normalizedInterest * INTEREST_RATE_WEIGHT) + (WORST_LOSS_GIVEN_DEFAULT * LOSS_GIVEN_DEFAULT_WEIGHT) + (normalizedFinancialReserves * FINANCIAL_RESERVES_WEIGHT) + (WORST_DEFAULT_RISK_SCORE * DEFAULT_RISK_SCORE_WEIGHT);

    // //cout << " Worst loan viability score = " << loanViabilityScore << endl;

    return loanViabilityScore;
}


double Loan::calculateInterestForDefaultRisk (double baseRate)
{
    if (creditScore >= 800)
    {
        baseRate = baseRate + 2;

    }
    else if (creditScore >= 740 && creditScore < 800)
    {
        baseRate = baseRate + 6;
    }
    else if (creditScore >= 670 && creditScore <= 739)
    {
        baseRate = baseRate + 9;
    }
    else if (creditScore >=580 && creditScore <= 669)
    {
        baseRate = baseRate + 12;
    }
    else if (creditScore >= 300 && creditScore <= 579)
    {
        baseRate = baseRate + 20;
    }

    return baseRate / 12;
}


double Loan::adjustLoanViabiltyScore (double rawLoanViabilityScore)
{
    unsigned short int maxScaleValue = 100, minScaleValue = 0;
    double adjustedViabilityScore, bestLoanViabilityScore, worstLoanViabilityScore;

    bestLoanViabilityScore = calculateBestCreditMetrics();
    worstLoanViabilityScore = calculateWorstCreditMetrics();
    adjustedViabilityScore = (((rawLoanViabilityScore - worstLoanViabilityScore) / (bestLoanViabilityScore - worstLoanViabilityScore)) * (maxScaleValue - minScaleValue)) + (minScaleValue);

    return adjustedViabilityScore;
}


double Loan::calculateDefaultRisk ()  // function not needed now since calc interest rate is not complete
{
    //int  creditScore = 850;
    //double lossGivenDefault = 0, duration = 19, loanAmount = 200000, bestRecoveryRate = 1, calculatedDefaultRisk;
    double bestRate, finalInterestRate, calculatedDefaultRisk, bestMonthlyRate;

    // bestMonthlyRate = BASE_INTEREST_RATE_FOR_CALCULATION / 12;
    finalInterestRate = calculateInterestForDefaultRisk(BEST_MONTHLY_INTEREST_RATE_FOR_CALCULATION);      // since at best credit rate, base rate is the automatic rate
    calculatedDefaultRisk = finalInterestRate - BEST_MONTHLY_INTEREST_RATE_FOR_CALCULATION;

    return calculatedDefaultRisk;
}


// When minimizing inefficiencies in this programme, initialize the credit metrics instead of assignning them values after decleration
void Loan::simple_set_credit_metrics ()
{
    normalizedCreditScore =  normalizeScore(creditScore, MAX_CREDIT_SCORE, MIN_CREDIT_SCORE);
    normalizedDuration = normalizeScore(duration, MAX_LOAN_DURATION, MIN_LOAN_DURATION);
    normalizedFinancialReserves = normalizeScore(financialReserves, MAX_FINANCIAL_RESERVES, MIN_FINANCIAL_RESERVES);
    normalizedInterest = normalizeScore(finalMonthlyInterestRate, MAX_INTEREST_RATE, MIN_INTEREST_RATE);
    normalizedmonthlyIncome = normalizeScore(monthlyIncome, MAX_MONTHLY_INCOME, MIN_MONTHLY_INCOME);
    normalizedLoanAmount = normalizeScore(loanAmount, MAX_LOAN_AMOUNT, MIN_LOAN_AMOUNT);

    lossGivenDefault = (loanAmount - financialReserves) / loanAmount; // SOURCE = WIKIPEDIA
    recoveryRate = 1 - lossGivenDefault;
    defaultRiskScore = calculateDefaultRisk();

    loanViabilityScore = calculateLoanViabilityScore(normalizedCreditScore, normalizedmonthlyIncome, debtToIncomeRatio, normalizedLoanAmount, normalizedDuration, lossGivenDefault, normalizedFinancialReserves, defaultRiskScore);

    finalAdjustedViabilityScore = adjustLoanViabiltyScore(loanViabilityScore);

    // //cout << " This is adjusted Loan viability score: " << finalAdjustedViabilityScore << endl;

    
}



// double normalizeScoreOutsideClass(double rawScore, double maxScore, double minScore)
// {
//     double normalizedScore, maxScaleValue = 1, minScaleValue = 0;

//     normalizedScore = ((rawScore - minScore) / (maxScore - minScore)) * (maxScaleValue - minScaleValue) + (minScaleValue);

//     return normalizedScore;
// }



#endif // LOAN_H_INCLUDED
