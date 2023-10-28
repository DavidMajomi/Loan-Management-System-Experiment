// #ifndef ECONOMICMETRICS_H_INCLUDED
// #define ECONOMICMETRICS_H_INCLUDED

#pragma once

#include <iostream>

using namespace std;

class EconomicMetrics
{
private:
    bool lockClass = false;
    double spreadForInterestRate = 3;
    double federalFundsRatePercent, yearOnYearInflationRatePercent, thisYearsGdp, lastYearsGdp;
    double baseYearlyInterestRatePercentForLoans, baseMonthlyInterestRatePercentForLoans;
    double superPrimeRate, primeRate, nearPrimeRate, subPrimeRate;
    double deepSubprimeRrate = 30.00;

    bool threeMonthYieldSet = false;
    bool tenYearYieldSet = false;
    double threeMonthYield;
    double tenYearYield;
    double threeMonthAndTenYearYieldSpread;

public:
    void setFederalFundsRatePercent(double ffr){
        if (lockClass == false)
        {
            federalFundsRatePercent = ffr;
            baseYearlyInterestRatePercentForLoans = federalFundsRatePercent + spreadForInterestRate;
            baseMonthlyInterestRatePercentForLoans = baseYearlyInterestRatePercentForLoans / 12;
            superPrimeRate = baseYearlyInterestRatePercentForLoans;
            primeRate = superPrimeRate + 4.15;
            nearPrimeRate = primeRate + 5.09;
            subPrimeRate = nearPrimeRate  + 6.00;
            deepSubprimeRrate = 30.00;

        }
        else
        {
            cout << " Error, cannot set value to a locked class. This is done to replicate a constant. This ensures that values cannot be changed by accident when using the dll. " << endl;
            cout << " This error is in the EconomicMetrics.h file in the setYearOnYearInflationRatePercent(double rate) function. " << endl;
            exit(1);
        }

    }
    void setThreeMonthYield(double yieldRate){
        threeMonthYield = yieldRate;
        threeMonthYieldSet = true;

    }
    void setTenYearYield(double yieldRate){
        tenYearYield = yieldRate;
        threeMonthYieldSet = true;
    }
    void setThreeMonthAndTenYearYieldSpread(){
        if (threeMonthYield && tenYearYieldSet)
        {
            threeMonthAndTenYearYieldSpread = tenYearYield - threeMonthYield;
        }
        else
        {
            cout << " Error, attempted to calculate three Month And Ten Year Yield Spread without setting those vlaues. " << endl;
            exit(1);
        }

    }
    void setYearOnYearInflationRatePercent(double rate){
        if (lockClass == false)
        {
            yearOnYearInflationRatePercent = rate;
        }
        else
        {
            cout << " Error, cannot set value to a locked class. This is done to replicate a constant. This ensures that values cannot be changed / modified unnecesserily by accident when using the dll. " << endl;
            cout << " This error is in the EconomicMetrics.h file in the setYearOnYearInflationRatePercent(double rate) function. " << endl;
            exit(1);
        }
    }
    double getFederalFundsRate() const{
        return federalFundsRatePercent;
    }
    double getBaseYearlyInterestRatePercentForLoans() const{
        return baseYearlyInterestRatePercentForLoans;
    }
    double getBaseMonthlyInterestRatePercentForLoans() const{
        return baseMonthlyInterestRatePercentForLoans;
    }
    double getYearOnYearInflationRatePercent() const{
        return yearOnYearInflationRatePercent;
    }
    double getSuperPrimeRate() const{
        return superPrimeRate;
    }
    double getPrimeRate() const{
        return primeRate;
    }
    double getNearPrimeRate() const{
        return nearPrimeRate;
    }
    double getSubPrimeRate() const{
        return subPrimeRate;
    }
    double getSpreadForInterestRate() const{
        return spreadForInterestRate;
    }
    double getDeepSubPrimeRate() const{
        return deepSubprimeRrate;
    }
    void lockModificationOfClass(){
        lockClass = true;
    }
    void unlockClassForModification(){
        lockClass = false;
    }
    double getThreeMonthAndTenYearYieldSpread() const{
        return threeMonthAndTenYearYieldSpread; 
    }
};

// #endif // ECONOMICMETRICS_H_INCLUDED