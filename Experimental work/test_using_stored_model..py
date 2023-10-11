import pickle

super_prime_rate = 9.33
deep_sub_prime_rate = 30

slope = (deep_sub_prime_rate - super_prime_rate) / -100 

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

with open("LMSModel.pickle", "rb") as file:
    recieved_model = pickle.load(file)
    
pred_ALVS = recieved_model[0]


ALVS = float(pred_ALVS.predict([[credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, loss_Given_Default, defult_risk_score]]))

normal_interest_rate = (slope * ALVS) + deep_sub_prime_rate


print(ALVS)
print(f" This is normal rate: {normal_interest_rate} ")
print(f" This is default risk score: {defult_risk_score} ")
print("Done")

