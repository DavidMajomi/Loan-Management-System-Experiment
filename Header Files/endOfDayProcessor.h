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
        cout << "Prior applications." << endl;
        vector<vector <string>> data = databaseManager::getAllApplicationsBesideTodays();

        for(int count = 0; count < data.size(); count++)
        {
            bool successCopyToCompletedTable = false;
            userDataFromDb userInfo(data[count]);
            loanUpdates changes = userInfo.getNewUpdates();

            string loanGrade;
            loanGrade = changes.getFinalLoanGrade();

            cout << "Loan status: " << changes.getLoanStatus() << endl;

            if(changes.getLoanStatus() == "Completed" && (changes.getEndOfTermCopyingDone() == (int)false))
            {
                cout << (bool)(changes.getEndOfTermCopyingDone()) << endl;
                successCopyToCompletedTable = databaseManager::copyUserDataToCompletedTable(userInfo);
                double timeT = databaseAbstraction::update(DATABASE_NAME, "users", "end_of_term_copying_done", to_string((int)(true)), "Loan_id", (changes.getLoanId()));
            }
            else if(changes.getLoanStatus() == "Defaulted" && (changes.getEndOfTermCopyingDone() == (int)false))
            {
                cout << (bool)(changes.getEndOfTermCopyingDone()) << endl;

                successCopyToCompletedTable = databaseManager::copyUserDataToDefaultedTable(userInfo);
                double timeJ = databaseAbstraction::update(DATABASE_NAME, "users", "end_of_term_copying_done", to_string((int)(true)), "Loan_id", (changes.getLoanId()));

            }


            double time = databaseAbstraction::update(DATABASE_NAME, "users", "duration_to_next_installment_days", to_string(changes.getDurationToNextInstallmentDays()), "Loan_id", (changes.getLoanId()));
            double timeY = databaseAbstraction::update(DATABASE_NAME, "users", "duration_to_loan_settlement_months", to_string(changes.getDurationToLoanSettlementMonths()), "Loan_id", (changes.getLoanId()));
            double timeH = databaseAbstraction::update(DATABASE_NAME, "users",  "final_loan_grade", loanGrade, "Loan_id", (changes.getLoanId()));
            double timeB = databaseAbstraction::update(DATABASE_NAME, "users", "loan_decision", to_string(changes.getLoanDecision()), "Loan_id", (changes.getLoanId()));
            double timeC = databaseAbstraction::update(DATABASE_NAME, "users", "loan_status", (changes.getLoanStatus()), "Loan_id", (changes.getLoanId()));
            double timeD = databaseAbstraction::update(DATABASE_NAME, "users", "applied_today_or_not", to_string(changes.getAppliedToday()), "Loan_id", (changes.getLoanId()));
            
            
        }

        
    }


    void processNewApplications()
    {
        cout << "New Application" << endl;
        reportData report;
        vector<vector <string>> data = databaseManager::getTodaysApplications();

        if(!(data.empty()))
        {
            for(int count = 0; count < data.size(); count++)
            {
                cout << "Rerun" << endl;

                userDataFromDb userInfo(data[count]);
                loanUpdates changes = userInfo.getNewUpdates();

                string loanGrade;
                loanGrade = changes.getFinalLoanGrade();
                

                double time = databaseAbstraction::update(DATABASE_NAME, "users", "duration_to_next_installment_days", to_string(changes.getDurationToNextInstallmentDays()), "Loan_id", (changes.getLoanId()));
                double timeH = databaseAbstraction::update(DATABASE_NAME, "users", "final_loan_grade", loanGrade, "Loan_id", (changes.getLoanId()));
                double timeB = databaseAbstraction::update(DATABASE_NAME, "users", "loan_decision", to_string(changes.getLoanDecision()), "Loan_id", (changes.getLoanId()));
                double timeC = databaseAbstraction::update(DATABASE_NAME, "users", "loan_status", (changes.getLoanStatus()), "Loan_id", (changes.getLoanId()));
                double timeD = databaseAbstraction::update(DATABASE_NAME, "users", "applied_today_or_not", to_string(changes.getAppliedToday()), "Loan_id", (changes.getLoanId()));

                // newApplicationChanges.push_back(userInfo.getNewUpdates());
                
                report.update(userInfo);
            }


            report.processStats();
            cout << "after process stats" << endl;

            string insertFormat = report.getSqlInsertFormat();
            string statementWithData = report.getInsertStatementWithData();

            cout << "Get sql values" << endl;
            cout << endl;
            cout << insertFormat << endl;
            cout << statementWithData << endl;

            double timeTaken = databaseAbstraction::storeSingleRowInDbUsingSingleInsert(DATABASE_NAME, insertFormat, "reports", statementWithData);

        }

    }
    

    void startEndOfDayProcessing()
    {
        cout << "Starting processing" << endl;
        processPriorApplications();
        processNewApplications();
    }
}
