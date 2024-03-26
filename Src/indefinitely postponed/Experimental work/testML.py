import pandas as pd
import numpy as np
from sklearn import linear_model
import matplotlib.pyplot as pyplot
import pickle

super_prime_rate = 9.33
deep_sub_prime_rate = 30.00

slope = (deep_sub_prime_rate - super_prime_rate) / -100 
df = pd.read_csv("analyzedDataFromDb.csv")

# print(df)

test_predict_adjusted_loan_viability_score_object = linear_model.LinearRegression()

test_predict_adjusted_loan_viability_score_object.fit(df[["credit_score", "monthly_income", "financial_reserves", "debt_to_income_ratio", "Duration_in_months", "loan_amount_requested",
                                "loss_Given_Default", "default_risk_score"]], df['Adjusted_Loan_viability_Score'])


# credit_score = 850
# monthly_income = 2966.61
# financial_reserves = 3530.38
# debt_to_income_ratio = 0.68
# Duration_in_months = 60
# loan_amount_requested = 1861

credit_score = 831
monthly_income = 1921.70
financial_reserves = 1084.64
debt_to_income_ratio = 0.42
Duration_in_months = 13
loan_amount_requested = 9413


if (credit_score >= 781):
    interestRateByGroup = super_prime_rate
    
elif (credit_score >= 661 and credit_score <= 780):
    interestRateByGroup = super_prime_rate
    
elif (credit_score >= 601 and credit_score <= 660):
    interestRateByGroup = super_prime_rate
    
elif (credit_score >= 500 and credit_score <= 600):
    interestRateByGroup = super_prime_rate
    
elif (credit_score <= 499):
    interestRateByGroup = super_prime_rate
    
monthly_interest_rate_by_group = interestRateByGroup /12
    
defult_risk_score = monthly_interest_rate_by_group - (super_prime_rate / 12)

loss_Given_Default = (loan_amount_requested - financial_reserves) / loan_amount_requested; # SOURCE = WIKIPEDIA

adjusted_loan_viability_score = float(test_predict_adjusted_loan_viability_score_object.predict([[credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, loss_Given_Default, defult_risk_score]]))


normal_monthly_interest_rate = (slope * adjusted_loan_viability_score) + deep_sub_prime_rate

list_of_models = [test_predict_adjusted_loan_viability_score_object]

print(adjusted_loan_viability_score)
print(f" This is normal rate: {normal_monthly_interest_rate} ")
print(f" This is default risk score: {defult_risk_score} ")

with open("LMSModel.pickle", "wb") as file:
    pickle.dump(list_of_models, file)
