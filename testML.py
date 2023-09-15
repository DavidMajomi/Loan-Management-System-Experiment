import pandas as pd
import numpy as np
from sklearn import linear_model
import matplotlib.pyplot as pyplot
import pickle

df = pd.read_csv("analyzedDataFromDb.csv")

# print(df)

# print(df["loan_amount_requested"])
 
test_predict_adjusted_loan_viability_score_object = linear_model.LinearRegression()
predict_default_risk_score = linear_model.LinearRegression()
predict_interest_rate = linear_model.LinearRegression()
predict_loan_viability_score = linear_model.LinearRegression()

predict_interest_rate.fit(df[["credit_score", "monthly_income", "financial_reserves", "debt_to_income_ratio", "Duration_in_months", "loan_amount_requested", "loss_Given_Default"]], df['Monthly_interest_rate'])
predict_default_risk_score.fit(df[["credit_score", "monthly_income", "financial_reserves", "debt_to_income_ratio", "Duration_in_months", "loan_amount_requested", "Monthly_interest_rate", "loss_Given_Default"]], df['default_risk_score'])
predict_loan_viability_score.fit(df[["credit_score", "monthly_income", "financial_reserves", "debt_to_income_ratio", "Duration_in_months", "loan_amount_requested", "Monthly_interest_rate", "loss_Given_Default", "default_risk_score"]], df['Loan_Viability_Score'])
test_predict_adjusted_loan_viability_score_object.fit(df[["credit_score", "monthly_income", "financial_reserves", "debt_to_income_ratio", "Duration_in_months", "loan_amount_requested",
                         "Monthly_interest_rate", "loss_Given_Default", "default_risk_score", "Loan_Viability_Score"]], df['Adjusted_Loan_viability_Score'])


credit_score = 411
monthly_income = 2966.61
financial_reserves = 3530.38
debt_to_income_ratio = 0.68
Duration_in_months = 34
loan_amount_requested = 1861
loss_Given_Default = (loan_amount_requested - financial_reserves) / loan_amount_requested; # SOURCE = WIKIPEDIA
predicted_monthly_interest_rate = float(predict_interest_rate.predict([[credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, loss_Given_Default]]))
predicted_default_risk_score = float(predict_default_risk_score.predict([[credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, predicted_monthly_interest_rate, loss_Given_Default]]))
predicted_loan_viability_score = float(predict_loan_viability_score.predict([[credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, predicted_monthly_interest_rate, loss_Given_Default, predicted_default_risk_score]]))
# predict_loan_viability_score.-


# print(regressionObject.coef_)
test_predict_adjusted_loan_viability_score = test_predict_adjusted_loan_viability_score_object.predict([[credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, predicted_monthly_interest_rate, loss_Given_Default, predicted_default_risk_score, predicted_loan_viability_score]])
# test_prediction = regressionObject.predict([[411, 2966.61, 3530.38, 0.68, 34, 1861, 2.194170, -0.897034,  1.183120, 0.076221]])

list_of_models = [predict_interest_rate, predict_default_risk_score, predict_loan_viability_score, test_predict_adjusted_loan_viability_score_object]
print(test_predict_adjusted_loan_viability_score)

with open("LMSModel.pickle", "wb") as file:
    pickle.dump(list_of_models, file)
