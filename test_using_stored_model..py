import pickle

credit_score = 520
monthly_income = 2966.61
financial_reserves = 3530.38
debt_to_income_ratio = 0.68
Duration_in_months = 34
loan_amount_requested = 1861
loss_Given_Default = (loan_amount_requested - financial_reserves) / loan_amount_requested; # SOURCE = WIKIPEDIA


with open("LMSModel.pickle", "rb") as file:
    recieved_model = pickle.load(file)
    
pred_inteest_rate = recieved_model[0]
pred_default_risk_score = recieved_model[1]
pred_loan_viability_score = recieved_model[2]
pred_ALVS = recieved_model[3]

interest_rate = float(pred_inteest_rate.predict([[credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, loss_Given_Default]]))
default_risk_score = float(pred_default_risk_score.predict([[credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, interest_rate, loss_Given_Default]]))
LVS = float(pred_loan_viability_score.predict([[credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, interest_rate, loss_Given_Default, default_risk_score]]))
ALVS = pred_ALVS.predict([[credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, interest_rate, loss_Given_Default, default_risk_score, LVS]])
print(ALVS)

print("DOne 2")

