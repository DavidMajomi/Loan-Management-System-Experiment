#include <string>


namespace LoanProcessor
{
    using namespace std;

    class userDataFromDB
    {
        int loanId;
        string userName;
        string timeOfApplication;
        int creditScore;
        double monthlyIncome;
        double financialReserves;
        double debtToIncomeRati;
        double loanDuration;

        int durationToNextInstallmentDays;
        double requestedLoanAmount;
        double monthlyInterestRate;
        double yearlyInterestRate;
        double lossGivenDefault;
        double recoveryRate;

        double outsytandingMonthlyDebtPaymentsPriorToLoan;
        double amounttoPayAtNextInsstallment;
        double defaultRiskScore;
        double loanViabilityScore;

        double adjustedLoanViabilityScore;
        double matrixBasedAdjustedLoanViabilityScore;
        double interestRateByGroup;
        double bestPossibleYearlyRate;

        double worstPossibleYearlyRate;
        char finalLoanGrade;
        double potentialProfitFromLoan;
        double calculatedBestPossibleAdjustedLoanViabilityScore;
        double calculatedWorstpossibleAdjustedLoanViabilityScore;
        
        double amountOfCurrentLoanAndInteerestsLeft;
        int loanDecision;
        string loanStatus;
        int appliedToday;
        int accountNumber;
    };
    

    void processFinalLoanGrade()
    {

    }

    void processAndAddFinalLoanGradeToDb()
    {
        
    }


    void makeFundTransferAsPayout()
    {

    }


    void addReport()
    {

    }

    void updateInstallmentpaymentDates()
    {


    }

    void moveCompletedLoanTOCompletedTable()
    {

    }

    void moveDefaultingLoanToDefaultingTable()
    {


    }

    void moveRejectedApplicantToRejectedTable()
    {

    }

    void startEndOfDayProcessing()
    {

    }
}