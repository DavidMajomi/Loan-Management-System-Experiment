#ifndef ECONOMICMETRICS_H_INCLUDED
#define ECONOMICMETRICS_H_INCLUDED

#include <iostream>

using namespace std;
class EconomicMetrics
{
private:
    bool lockClass = false;
    double federalFundsRatePercent, yearOnYearInflationRatePercent, gdp;
    double baseYearlyInterestRatePercentForLoans, baseMonthlyInterestRatePercentForLoans;
    double superPrimeRate;
    double primeRate;
    double nearPrimeRate;
    double subPrimeRate;
    double deepSubprimeRrate = 30.00;

public:
    void setFederalFundsRatePercent(double ffr)
    {
        if (lockClass == false)
        {
            federalFundsRatePercent = ffr;
            baseYearlyInterestRatePercentForLoans = federalFundsRatePercent + 3;
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
            exit(1);
        }

    }
    double getFederalFundsRate() const
    {
        return federalFundsRatePercent;
    }
    double getBaseYearlyInterestRatePercentForLoans() const
    {
        return baseYearlyInterestRatePercentForLoans;
    }
    double getBaseMonthlyInterestRatePercentForLoans() const
    {
        return baseMonthlyInterestRatePercentForLoans;
    }
    void setYearOnYearInflationRatePercent(double rate)
    {
        if (lockClass == false)
        {
            yearOnYearInflationRatePercent = rate;
        }
        else
        {
            cout << " Error, cannot set value to a locked class. This is done to replicate a constant. This ensures that values cannot be changed / modified unnecesserily by accident when using the dll. " << endl;
            exit(1);
        }
    }
    double getYearOnYearInflationRatePercent() const
    {
        return yearOnYearInflationRatePercent;
    }
    double getSuperPrimeRate() const
    {
        return superPrimeRate;
    }
    double getPrimeRate() const
    {
        return primeRate;
    }
    double getNearPrimeRate() const
    {
        return nearPrimeRate;
    }
    double getSubPrimeRate() const
    {
        return subPrimeRate;
    }
    double getDeepSubPrimeRate() const
    {
        return deepSubprimeRrate;
    }
    void lockModificationOfClass()
    {
        lockClass = true;
    }
};

#endif // ECONOMICMETRICS_H_INCLUDED