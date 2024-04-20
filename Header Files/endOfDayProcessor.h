#pragma once

#include "processor.h"
#include "loanDatabaseManager.h"


namespace endOfDayProcessor
{
    using namespace Processor;

    bool makeFundTransferAsPayout()
    {
        return true;
    }


    void processPriorApplications()
    {
        vector<vector <string>> data = databaseManager::getAllApplicationsBesideTodays();

        for(int count = 0; count < data.size(); count++)
        {
            bool successCopyToCompletedTable = false;
            userDataFromDb userInfo(data[count]);
            loanUpdates changes = userInfo.getNewUpdates();

            string loanGrade;
            loanGrade = changes.getFinalLoanGrade();

            if(changes.getLoanStatus() == "Completed")
            {
                successCopyToCompletedTable = databaseManager::copyUserDataToCompletedTable(userInfo);
            }
            else if(changes.getLoanStatus() == "Defaulted")
            {
                successCopyToCompletedTable = databaseManager::copyUserDataToDefaultedTable(userInfo);
            }
            else
            {
                double time = databaseAbstraction::update(DATABASE_NAME, "users", "duration_to_next_installment_days", to_string(changes.getDurationToNextInstallmentDays()), "Loan_id", (changes.getLoanId()));
                double timeH = databaseAbstraction::update(DATABASE_NAME, "users",  "final_loan_grade", loanGrade, "Loan_id", (changes.getLoanId()));
                double timeB = databaseAbstraction::update(DATABASE_NAME, "users", "loan_decision", to_string(changes.getLoanDecision()), "Loan_id", (changes.getLoanId()));
                double timeC = databaseAbstraction::update(DATABASE_NAME, "users", "loan_status", (changes.getLoanStatus()), "Loan_id", (changes.getLoanId()));
                double timeD = databaseAbstraction::update(DATABASE_NAME, "users", "applied_today_or_not", to_string(changes.getAppliedToday()), "Loan_id", (changes.getLoanId()));
            }
            
            
        }

        
    }


    void processNewApplications()
    {
        reportData report;
        vector<vector <string>> data = databaseManager::getTodaysApplications();

        if(!(data.empty()))
        {
            for(int count = 0; count < data.size(); count++)
            {
                userDataFromDb userInfo(data[count]);
                loanUpdates changes = userInfo.getNewUpdates();

                string loanGrade;
                loanGrade = changes.getFinalLoanGrade();
                

                double time = databaseAbstraction::update(DATABASE_NAME, "users", "duration_to_next_installment_days", to_string(changes.getDurationToNextInstallmentDays()), "Loan_id", (changes.getLoanId()));
                double timeH = databaseAbstraction::update(DATABASE_NAME, "users",  "final_loan_grade", loanGrade, "Loan_id", (changes.getLoanId()));
                double timeB = databaseAbstraction::update(DATABASE_NAME, "users", "loan_decision", to_string(changes.getLoanDecision()), "Loan_id", (changes.getLoanId()));
                double timeC = databaseAbstraction::update(DATABASE_NAME, "users", "loan_status", (changes.getLoanStatus()), "Loan_id", (changes.getLoanId()));
                double timeD = databaseAbstraction::update(DATABASE_NAME, "users", "applied_today_or_not", to_string(changes.getAppliedToday()), "Loan_id", (changes.getLoanId()));

                // newApplicationChanges.push_back(userInfo.getNewUpdates());
                
                report.update(userInfo);
            }


            report.processStats();
            string insertFormat = report.getSqlInsertFormat();
            string statementWithData = report.getInsertStatementWithData();

            double timeTaken = databaseAbstraction::storeSingleRowInDbUsingSingleInsert(DATABASE_NAME, insertFormat, "reports", statementWithData);

        }

    }
    

    void startEndOfDayProcessing()
    {
        processPriorApplications();
        processNewApplications();
    }
}
