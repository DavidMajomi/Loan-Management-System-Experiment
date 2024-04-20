#pragma once

#include <fstream>
#include "Loan.h"
#include "processor.h"
#include "databaseAbstraction.h"

namespace databaseManager
{
    using namespace std;
    // Matrix positions of db values
    const unsigned short int LOAN_ID_POSITION = 0;
    const unsigned short int NAME_POSITION = 1;
    const unsigned short int TIME_OF_APPLICATION_POSITION = 2;
    const unsigned short int CREDIT_SCORE_POSITION = 3;
    const unsigned short int MONTHLY_INCOME_POSITION = 4;
    const unsigned short int FINANCIAL_RESERVES_POSITION = 5;
    const unsigned short int DEBT_TO_INCOME_RATIO_POSITION = 6;
    const unsigned short int LOAN_DURATION_POSITION = 7;
    const unsigned short int REQUESTED_LOAN_AMOUNT_POSITION = 8;
    const unsigned short int MONTHLY_INTEREST_RATE_POSITION = 9;
    const unsigned short int YEARLY_INTEREST_RATE_POSITION = 10;
    const unsigned short int LOSS_GIVEN_DEFAULT_POSITION = 11;
    const unsigned short int RECOVERY_RATE_POSITION = 12;
    const unsigned short int OUTSTANDING_MONTHLY_DEBT_PAYMENTS_POSITION = 13;
    const unsigned short int DEFAULT_RISK_SCORE_POSITION = 14;
    const unsigned short int LOAN_VIABILITY_SCORE_POSITION = 15;
    const unsigned short int ADJUSTED_LOAN_VIABILITY_SCORE_POSITION = 16;
    const unsigned short int MATRIX_BASED_ADJUSTED_LOAN_VIABILITY_SCORE_POSITION = 17;
    const unsigned short int INTERETS_RATE_BY_GROUP_POSITION = 18;
    const unsigned short int BEST_POSSIBLE_RATE_POSITION = 19;
    const unsigned short int WORST_POSSIBLE_RATE_POSITION = 20;
    const unsigned short int FINAL_LOAN_GRADE_POSITION = 21;
    
    
    // Table Names
    const string REPORTS_TABLE_NAME = "reports";
    const string TABLE_OF_INITIAL_USER_APPLICATION = "users";
    const string REJECTED_USERS_TABLE_NAME = "rejected_users";
    const string ACCEPTED_USERS_TABLE_NAME = "accepted_users";
    const string DEFAULTING_USERS_TABLE_NAME = "defaulting_users";

    

    


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
        vector<vector<string>> dataMatrix = databaseAbstraction::retrieveAllUserDataFromDatabaseForMatrix(DATABASE_NAME, TABLE_OF_INITIAL_USER_APPLICATION);

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
        vector<vector<string>> dbValues = databaseAbstraction::retreiveDataWithMatchingValue(DATABASE_NAME, TABLE_OF_INITIAL_USER_APPLICATION, "Loan_id", to_string(loanId));
        
        return (dbValues[0][NAME_POSITION]);
    }



    vector<vector<string>> getTodaysApplications()
    {
        vector<vector<string>> data;

        data = databaseAbstraction::retreiveDataWithMatchingValue(DATABASE_NAME, TABLE_OF_INITIAL_USER_APPLICATION, "applied_today_or_not", "1");

        // printMatrixValues(data);

        return data;
    }
    
    
    vector<vector <string>> getAllApplicationsBesideTodays()
    {
        vector<vector<string>> data;

        data = databaseAbstraction::retreiveDataWithMatchingValue(DATABASE_NAME, TABLE_OF_INITIAL_USER_APPLICATION, "applied_today_or_not", "0");

        // printMatrixValues(data);

        return data;
        
    }


    bool addLoanUser(Loan userData)
    {
        string insertFormat = userData.getSqlInsertFormat();
        string statementWithData = userData.getInsertStatementWithData();
        double timeTaken = databaseAbstraction::storeSingleRowInDbUsingSingleInsert(DATABASE_NAME, insertFormat, TABLE_OF_INITIAL_USER_APPLICATION, statementWithData);

        return true;
    }


    bool changeDateToNextInstallment(int loanId, int changeTo)
    {

        return true;
    }


    bool copyUserDataToCompletedTable(Processor::userDataFromDb userData)
    {
        string insertFormat = userData.getSqlInsertformat();
        string statementWithData = userData.getSqlInsertValues();

        double timeTaken = databaseAbstraction::storeSingleRowInDbUsingSingleInsert(DATABASE_NAME, insertFormat, TABLE_OF_INITIAL_USER_APPLICATION, statementWithData);
       
        return true;
    }


    bool copyUserDataToDefaultedTable(Processor::userDataFromDb userData)
    {
        string insertFormat = userData.getSqlInsertformat();
        string statementWithData = userData.getSqlInsertValues();

        double timeTaken = databaseAbstraction::storeSingleRowInDbUsingSingleInsert(DATABASE_NAME, insertFormat, TABLE_OF_INITIAL_USER_APPLICATION, statementWithData);
       
        return true;
    }
    
    
}