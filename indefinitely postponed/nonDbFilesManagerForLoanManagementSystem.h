#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <filesystem>// cpp 17 reference https://en.cppreference.com/w/cpp/filesystem/current_paths
#include "EconomicMetrics.h"
#include "loan.h"

namespace fs = std::filesystem;

using namespace std;

int convert_to_int (string valueToConvert)
{
    int convertedValue = stoi(valueToConvert);

    return convertedValue;
}


double convert_to_double (string valueToConvert)
{
    double convertedValue;
    convertedValue = stod(valueToConvert);

    return convertedValue;
}


class nonDbFilesManager
{
private:
    const string CURRENT_FULL_PATH = fs::current_path().string();
    const string CSV_FILE_FOR_ALL_GENERATED_LOAN_DATA = CURRENT_FULL_PATH + "\\Folder with Generated Data\\allGeneratedLoanData.csv";     // Based only on historical generated data, no new generated data here
    const string OUTPUT_CSV_FILE_FOR_PROCESSED_DATA = CURRENT_FULL_PATH + "\\Csv Files For Analysis\\processedLoanData.csv";
    const string CSV_FILE_FOR_STORING_ANALAYZED_DB_VALUES = CURRENT_FULL_PATH + "\\Csv Files For Analysis\\analyzedDataFromDb.csv";
    const string CSV_FILE_FOR_TEMP_GENERATED_DATA_FOR_DB = CURRENT_FULL_PATH + "\\Folder with Generated Data\\tempGeneratedLoanDataForDbStorage.csv";


    bool readGeneratedData (ifstream& inputFile, vector <Loan>& loanAccounts, unsigned short int devMenuResponse)
    {
        int count = 0, values, creditScoreInteger, durationInMonthsInteger;
        bool fileOpeningError = false;
        double monthlyIncomeDecimal, financialReservesDecimal, debtToIncomeRatioDecimal, loanAmonutRequestedDeciaml;
        string userName, creditScore, monthlyIncome, financialReserves, debtToIncomeRatio, durationInMonths, loanAmountRequested;


        if (devMenuResponse == 2)
        {
            // //cout << " 2" << endl;
            inputFile.open(CSV_FILE_FOR_ALL_GENERATED_LOAN_DATA); // Based only on historical generated data, no new generated data here
        }
        else if (devMenuResponse == 1)
        {
            // This contains freshly generated data from python
            inputFile.open(CSV_FILE_FOR_TEMP_GENERATED_DATA_FOR_DB);    // Data from here would be stored in database (data analysis on new generated data)
        }

        if (inputFile.fail())
        {
            cout << " File opening failure. " << endl;
            fileOpeningError = true;
            // exit(1);
        }
        else
        {

            while (getline(inputFile, userName, ','))
            {
                values = count;

                // cout << " This is the name of the customer applying to this position. " << endl;


                getline(inputFile, creditScore, ',');
                getline(inputFile, monthlyIncome, ',');
                getline(inputFile, financialReserves, ',');
                getline(inputFile, debtToIncomeRatio, ',');
                getline(inputFile, durationInMonths, ',');
                getline(inputFile, loanAmountRequested, '\n');


                if (count > 0)
                {
                    values = count - 1;
                    Loan userAccount(values);

                    creditScoreInteger = convert_to_int(creditScore);
                    monthlyIncomeDecimal = convert_to_double(monthlyIncome);
                    financialReservesDecimal = convert_to_double(financialReserves);
                    debtToIncomeRatioDecimal = convert_to_double(debtToIncomeRatio);
                    durationInMonthsInteger = convert_to_int(durationInMonths);
                    loanAmonutRequestedDeciaml = convert_to_double(loanAmountRequested);

                    userAccount.setUserName(userName);
                    userAccount.setCreditScore(creditScoreInteger);
                    userAccount.setMonthlyIncome(monthlyIncomeDecimal);
                    userAccount.setFinancialReserves(financialReservesDecimal);
                    userAccount.setDebtToIncomeRatio(debtToIncomeRatioDecimal);
                    userAccount.setLoanDuration(durationInMonthsInteger);
                    userAccount.setLoanAmount(loanAmonutRequestedDeciaml);
                    // userAccount.set_monthly_debt_payments();
                    userAccount.computeCreditData();
                    userAccount.setFinalMonthlyInterestRate();

                    loanAccounts.push_back(userAccount);

                }

                count++;
            }

            inputFile.close();
        }

        
        return fileOpeningError;
    }


    bool outputToFile (ofstream& outputCsvFile, vector <Loan>& loanAccounts)
    {
        int numLoanAccounts;
        bool fileOpeningError = false;

        outputCsvFile.open(OUTPUT_CSV_FILE_FOR_PROCESSED_DATA);


        if (outputCsvFile.fail())
        {
            //cout << " Output File Opening Error. " << endl;
            fileOpeningError = true;
        }
        else
        {
            numLoanAccounts = loanAccounts.size();
            //cout << " This is num processed values. outputFile function: " << numLoanAccounts << endl;

            outputCsvFile << "Name,credit_score,monthly_income,financial_reserves,debt_to_income_ratio,Duration_in_months,loan_amount_requested,Monthly_interest_rate,Interest_rate_over_a_year,"
                        "loss_Given_Default,Recovery_Rate,outstanding_Monthly_Debt_Payments,";
            outputCsvFile << "default_risk_score,Loan_Viability_Score,Adjusted_Loan_viability_Score" << endl;

            for (int count = 0; count < numLoanAccounts; count++)
            {
                outputCsvFile << loanAccounts[count].getUserName() << ",";
                outputCsvFile << loanAccounts[count].getCreditScore() << ",";
                outputCsvFile << loanAccounts[count].getMonthlyIncome() << ",";
                outputCsvFile << loanAccounts[count].getFinancialReserves() << ",";
                outputCsvFile << loanAccounts[count].getDebtToIncomeRatio() << ",";
                outputCsvFile << loanAccounts[count].getDurationInMonths() << ",";
                outputCsvFile << loanAccounts[count].getLoanAmount() << ",";
                outputCsvFile << loanAccounts[count].getMonthlyInterestRate() << ",";
                outputCsvFile << loanAccounts[count].getYearlyInterestRate() << ",";
                outputCsvFile << loanAccounts[count].getLossGivenDefault() << ",";
                outputCsvFile << loanAccounts[count].getRecoveryRate() << ",";
                outputCsvFile << loanAccounts[count].getTotalOutstandingMonthlyDebtPaymentsAfterLoan() << ",";
                outputCsvFile << loanAccounts[count].getDefaultRiskScore() << ",";
                outputCsvFile << loanAccounts[count].getLoanViabilityScore() << ",";
                outputCsvFile << loanAccounts[count].getFinalAdjustedLoanViabilityScore() << "\n";
            }


            outputCsvFile.close();
        }


        return fileOpeningError;

    }
    };