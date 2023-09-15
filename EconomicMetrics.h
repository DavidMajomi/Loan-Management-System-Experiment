#ifndef ECONOMICMETRICS_H_INCLUDED
#define ECONOMICMETRICS_H_INCLUDED


class EconomicMetrics
{
private:
    double federalFundsRate, baseRate;
public:
    void setFederalFundsRate(double ffr)
    {
        federalFundsRate = ffr;
    }
    double getFederalFundsRate()
    {
        return federalFundsRate;
    }
    double setBaseRate(double rate)
    {
        baseRate = rate;
    }
};

#endif // ECONOMICMETRICS_H_INCLUDED