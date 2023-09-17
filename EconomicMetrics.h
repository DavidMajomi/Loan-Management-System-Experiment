#ifndef ECONOMICMETRICS_H_INCLUDED
#define ECONOMICMETRICS_H_INCLUDED


class EconomicMetrics
{
private:
    double federalFundsRatePercent, baseYearlyInterestRatePercentForLoans, baseMonthlyInterestRatePercentForLoans, yearOnYearInflationRatePercent, gdp;

public:
    void setFederalFundsRatePercent(double ffr)
    {
        federalFundsRatePercent = ffr;
        baseYearlyInterestRatePercentForLoans = federalFundsRatePercent + 3;
        baseMonthlyInterestRatePercentForLoans = baseYearlyInterestRatePercentForLoans / 12;

    }
    double getFederalFundsRate()
    {
        return federalFundsRatePercent;
    }
    double getBaseYearlyInterestRatePercentForLoans()
    {
        return baseYearlyInterestRatePercentForLoans;
    }
    double getBaseMonthlyInterestRatePercentForLoans() const
    {
        return baseMonthlyInterestRatePercentForLoans;
    }
    void setYearOnYearInflationRatePercent(double rate)
    {
        yearOnYearInflationRatePercent = rate;
    }
    double getYearOnYearInflationRatePercent() const
    {
        return yearOnYearInflationRatePercent;
    }
};

#endif // ECONOMICMETRICS_H_INCLUDED