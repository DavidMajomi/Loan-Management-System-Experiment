#pragma once

#include "constants.h"
#include <iostream>

using namespace std;

class EconomicMetrics
{
private:
    static bool lockClass;
    static double spreadForInterestRate;
    static double federalFundsRatePercent, yearOnYearInflationRatePercent, thisYearsGdp, lastYearsGdp;
    static double baseYearlyInterestRatePercentForLoans, baseMonthlyInterestRatePercentForLoans;
    static double superPrimeRate, primeRate, nearPrimeRate, subPrimeRate;
    static double deepSubprimeRrate;

    static bool threeMonthYieldSet;
    static bool tenYearYieldSet;
    static double threeMonthYield;
    static double tenYearYield;
    static double threeMonthAndTenYearYieldSpread;

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
        if (lockClass == false)
        {
            threeMonthYield = yieldRate;
            threeMonthYieldSet = true;
        }
        else
        {
            cout << " Error, cannot set value to a locked class. This is done to replicate a constant. This ensures that values cannot be changed by accident when using the dll. " << endl;
            cout << " This error is in the EconomicMetrics.h file in the setYearOnYearInflationRatePercent(double rate) function. " << endl;
            exit(1);
        }

        
    }
    void setTenYearYield(double yieldRate){
        if (lockClass == false)
        {
            tenYearYield = yieldRate;
            threeMonthYieldSet = true;
        }
        else
        {
            cout << " Error, cannot set value to a locked class. This is done to replicate a constant. This ensures that values cannot be changed by accident when using the dll. " << endl;
            cout << " This error is in the EconomicMetrics.h file in the setYearOnYearInflationRatePercent(double rate) function. " << endl;
            exit(1);

        }

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
    bool getClassModificationState() const{
        return lockClass;
    }
};

// EconomicMetrics::initializeStaticValuesForEconomicMetrics();


bool EconomicMetrics::lockClass = false;
double EconomicMetrics::spreadForInterestRate = 3;
double EconomicMetrics::deepSubprimeRrate = 30;
bool EconomicMetrics::threeMonthYieldSet = false;
bool EconomicMetrics::tenYearYieldSet = false;
double EconomicMetrics::federalFundsRatePercent, yearOnYearInflationRatePercent, thisYearsGdp, lastYearsGdp;
double EconomicMetrics::baseYearlyInterestRatePercentForLoans, EconomicMetrics::baseMonthlyInterestRatePercentForLoans;
double EconomicMetrics::superPrimeRate, EconomicMetrics::primeRate, EconomicMetrics::nearPrimeRate, EconomicMetrics::subPrimeRate;
