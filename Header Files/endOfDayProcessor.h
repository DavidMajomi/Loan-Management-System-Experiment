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


    int processPriorApplications(string date)
    {
        // cout << "Prior applications." << endl;
        vector<vector <string>> data = databaseManager::getAllApplicationsBesideTodays();

        for(int count = 0; count < data.size(); count++)
        {
            bool successCopyToCompletedTable = false;

            Processor::userDataFromDb userInfo(data[count], date);
            loanUpdates changes = userInfo.getNewUpdates();

            string loanGrade;
            loanGrade = changes.getFinalLoanGrade();

            if(changes.getLoanStatus() == "Completed" && (changes.getEndOfTermCopyingDone() == (int)false))
            {
                double timeT = databaseAbstraction::update(DATABASE_NAME, "users", "end_of_term_copying_done", to_string((int)(true)), "Loan_id", (changes.getLoanId()));
                double timeGH = databaseAbstraction::update(DATABASE_NAME, "users", "loan_status", (changes.getLoanStatus()), "Loan_id", (changes.getLoanId()));
            }
            else if(changes.getLoanStatus() == "Defaulted" && (changes.getEndOfTermCopyingDone() == (int)false))
            {
                double timeJ = databaseAbstraction::update(DATABASE_NAME, "users", "end_of_term_copying_done", to_string((int)(true)), "Loan_id", (changes.getLoanId()));
                double timeFH = databaseAbstraction::update(DATABASE_NAME, "users", "loan_status", (changes.getLoanStatus()), "Loan_id", (changes.getLoanId()));
            }

            if(changes.getChangeInstallmentDate() == true)
            {
                double time = databaseAbstraction::update(DATABASE_NAME, "users", "duration_to_installment_days", (changes.getDurationToNextInstallmentDays()), "Loan_id", (changes.getLoanId()));

            }

        }
        
        return data.size();
    }


    int processNewApplications(string date)
    {
        // cout << "New Application" << endl;
        reportData report;
        vector<vector <string>> data = databaseManager::getTodaysApplications();

        if(!(data.empty()))
        {
            for(int count = 0; count < data.size(); count++)
            {
                // cout << "Rerun" << endl;

                userDataFromDb userInfo(data[count], date);
                loanUpdates changes = userInfo.getNewUpdates();

                string loanGrade;
                loanGrade = changes.getFinalLoanGrade();
                

                // double time = databaseAbstraction::update(DATABASE_NAME, "users", "duration_to_next_installment_days", to_string(changes.getDurationToNextInstallmentDays()), "Loan_id", (changes.getLoanId()));
                double timeH = databaseAbstraction::update(DATABASE_NAME, "users", "final_loan_grade", loanGrade, "Loan_id", (changes.getLoanId()));
                double timeB = databaseAbstraction::update(DATABASE_NAME, "users", "loan_decision", to_string(changes.getLoanDecision()), "Loan_id", (changes.getLoanId()));
                double timeC = databaseAbstraction::update(DATABASE_NAME, "users", "loan_status", (changes.getLoanStatus()), "Loan_id", (changes.getLoanId()));
                double timeD = databaseAbstraction::update(DATABASE_NAME, "users", "applied_today_or_not", to_string(changes.getAppliedToday()), "Loan_id", (changes.getLoanId()));

                // newApplicationChanges.push_back(userInfo.getNewUpdates());
                
                report.update(userInfo);
            }


            report.processStats();
            // cout << "after process stats" << endl;

            string insertFormat = report.getSqlInsertFormat();
            string statementWithData = report.getInsertStatementWithData();

            // cout << "Get sql values" << endl;
            cout << endl;
            // cout << insertFormat << endl;
            // cout << statementWithData << endl;

            double timeTaken = databaseAbstraction::storeSingleRowInDbUsingSingleInsert(DATABASE_NAME, insertFormat, "reports", statementWithData);

        }

        return data.size();
    }
    

    int startEndOfDayProcessing(string date)
    {

        int numNewApplications = 0;
        int numPriorApplications = 0;

        cout << "Starting processing" << endl;
        numPriorApplications = processPriorApplications(date);
        numNewApplications = processNewApplications(date);
        cout << "Done Processing" << endl;
        
        cout << endl;
        
        // cout << "Number of new applications processed = " << numNewApplications << endl;
        // cout << "Number of prior applications processed = " << numPriorApplications << endl;

        return numNewApplications + numPriorApplications;

    }
}
