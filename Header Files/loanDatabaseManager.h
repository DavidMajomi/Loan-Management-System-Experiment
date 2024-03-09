#include <fstream>
#include "Loan.h"

#include "databaseAbstraction.h"

namespace databaseManager
{
    // Matrix positions of db values
    const int NAME_POSITION = 1;
    using namespace std;


    template <typename T>
    void printMatrixValues(vector<vector <T>> dBDataMatrix)
    {
        int matrixSize = dBDataMatrix.size();
        for(int count = 0; count < matrixSize; count++)
        {
            for(int j = 0; j < dBDataMatrix[count].size(); j++)
            {
                cout << dBDataMatrix[count][j] << endl;
            }

            cout << endl << endl;
            
        }
    }

    vector<vector<string>> getAllDbDATA()
    {
        vector<vector<string>> dataMatrix = databaseAbstraction::retrieveAllUserDataFromDatabaseForMatrix(DATABASE_NAME, DATABASE_TABLE_WITH_INITIAL_APPLICATION);

        return dataMatrix;
    }


    int retrieveAllUserDataFromDatabaseAndOutputToCsv(ofstream& outputCsvFile)
    {
        int matrixSize;
        
        string outputDBDataToCsvHeader = "Name,credit_score,monthly_income,financial_reserves,debt_to_income_ratio,Duration_in_months,loan_amount_requested,Monthly_interest_rate,Interest_rate_over_a_year,"
        "loss_Given_Default,Recovery_Rate,outstanding_Monthly_Debt_Payments,"
        "default_risk_score,Loan_Viability_Score,Adjusted_Loan_viability_Score,matrix_based_adjusted_loan_viability_score,interest_rate_by_group,best_possible_rate,worst_possible_rate";
        
        
        vector<vector<string>> dataMatrix = getAllDbDATA();

        outputCsvFile.open("dbtest.csv");
        
        if (outputCsvFile.fail())
        {
            throw " Error opening File to output database values.";
        }
        else
        {
            matrixSize = dataMatrix.size();

            outputCsvFile << outputDBDataToCsvHeader << endl;

            for(int count = 0; count < matrixSize; count++)
            {
                for(int j = 0; j < dataMatrix[count].size(); j++)
                {
                    if(j != 2)          // Do not print the time of application into the csv file
                    {

                        outputCsvFile << dataMatrix[count][j];

                        if(j <= (dataMatrix[count].size() - 2))
                        {
                            outputCsvFile << ",";
                        }
                        else
                        {
                            outputCsvFile << "\n";
                        }
                    }
                }

            }
            
            outputCsvFile.close();
        }
            
        return 0;
    }


    string retreiveUserNameMatchingLoanId(int loanId)
    {
        vector<vector<string>> dbValues = databaseAbstraction::retreiveDataWithMatchingValue(DATABASE_NAME, "users", "Loan_id", to_string(loanId));
        
        return (dbValues[0][NAME_POSITION]);
    }

    
    bool addLoanUser(Loan userData)
    {
        string insertFormat = userData.getSqlInsertFormat();
        string statementWithData = userData.getInsertStatementWithData();
        double timeTaken = databaseAbstraction::storeSingleRowInDbUsingSingleInsert(DATABASE_NAME, insertFormat, "users", statementWithData);

        return true;
    }
    
    
}