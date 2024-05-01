import pickle

def get_predicted_adjusted_loan_viability_score(credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, loss_Given_Default, defult_risk_score):
    with open('LMSModel.pickle', 'rb') as file: 
        modelList = pickle.load(file) 
  
    model = modelList[0]
    
    adjusted_loan_viability_score = (model.predict([[credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, loss_Given_Default, defult_risk_score]]))
    
    return adjusted_loan_viability_score[0]


def get_predicted_loan_decision(adjusted_lona_viability_score):
    with open('LMSModel.pickle', 'rb') as file: 
        modelList = pickle.load(file) 
  
    model = modelList[1]
    
    decison = (model.predict([[adjusted_lona_viability_score]]))
    
    return decison[0]

    
super_prime_rate = 8.33
deep_sub_prime_rate = 30.00

slope = (deep_sub_prime_rate - super_prime_rate) / -100 

credit_score = 850
monthly_income = 12000
financial_reserves = 50000
debt_to_income_ratio = 0
Duration_in_months = 1
loan_amount_requested = 20000

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
    
score = get_predicted_adjusted_loan_viability_score(credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, loss_Given_Default, defult_risk_score)
decision = get_predicted_loan_decision(score)

print("Score: ", score)
print("Decision: ", decision)