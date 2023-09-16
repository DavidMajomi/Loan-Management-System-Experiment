#ifndef ECONOMICMETRICS_H_INCLUDED
#define ECONOMICMETRICS_H_INCLUDED


class EconomicMetrics
{
private:
    double federalFundsRatePercent, baseRate, yearOnYearInflationRatePercent, gdp;
public:
    void setFederalFundsRatePercent(double ffr)
    {
        federalFundsRatePercent = ffr;
    }
    double getFederalFundsRate()
    {
        return federalFundsRatePercent;
    }
    void setBaseRate(double rate)
    {
        baseRate = rate;
    }
    double getBaseRate()
    {
        return baseRate;
    }
    void setYearOnYearInflationRatePercent(double rate)
    {
        yearOnYearInflationRatePercent = rate;
    }
    double getYearOnYearInflationRatePercent()
    {
        return yearOnYearInflationRatePercent;
    }
};

#endif // ECONOMICMETRICS_H_INCLUDED