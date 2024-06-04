import pickle



def predict_yearly_interest_rate_by_group(credit_score):
    with open('LMSModel.pickle', 'rb') as file: 
        modelList = pickle.load(file) 
  
    model = modelList[0]
    
    return round(float((model.predict([[credit_score]])[0])), 2)


def predict_default_risk_score(monthly_interest_rate_by_group):
    with open('LMSModel.pickle', 'rb') as file: 
        modelList = pickle.load(file) 
  
    model = modelList[1]
    
    return round(float((model.predict([[monthly_interest_rate_by_group]])[0])), 2)  


def predict_loss_given_default(loan_amount_requested, financial_reserves):
    with open('LMSModel.pickle', 'rb') as file: 
        modelList = pickle.load(file) 
  
    model = modelList[2]
    return round(float((model.predict([[loan_amount_requested, financial_reserves]])[0])), 2) 
  

def  get_predicted_adjusted_loan_viability_score(credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, 
                                               loan_amount_requested, loss_Given_Default, defult_risk_score):
    with open('LMSModel.pickle', 'rb') as file: 
        modelList = pickle.load(file) 
  
    model = modelList[3]
    
    adjusted_loan_viability_score = (model.predict([[credit_score, 
                                                     monthly_income, 
                                                     financial_reserves, 
                                                     debt_to_income_ratio, 
                                                     Duration_in_months, 
                                                     loan_amount_requested, 
                                                     loss_Given_Default, 
                                                     defult_risk_score]]))
    
    return adjusted_loan_viability_score[0]


def predict_interest_rate_from_alvs(alvs):
    with open('LMSModel.pickle', 'rb') as file: 
        modelList = pickle.load(file) 
  
    model = modelList[4]
    
    return round(float((model.predict([[alvs]])[0])), 2)


def get_predicted_loan_decision(adjusted_lona_viability_score):
    with open('LMSModel.pickle', 'rb') as file: 
        modelList = pickle.load(file) 
  
    model = modelList[5]
    
    decison = (model.predict([[adjusted_lona_viability_score]]))
    
    return decison[0]

    

credit_score = 612
monthly_income = 6361.51
financial_reserves = 17294.92
debt_to_income_ratio = 0.40
Duration_in_months = 59
loan_amount_requested = 14185.0


interestRateByGroup = predict_yearly_interest_rate_by_group(credit_score)
    
monthly_interest_rate_by_group = interestRateByGroup / 12
    
defult_risk_score = predict_default_risk_score(monthly_interest_rate_by_group)

loss_Given_Default = predict_loss_given_default(loan_amount_requested, financial_reserves)
    
score = get_predicted_adjusted_loan_viability_score(credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested, loss_Given_Default, defult_risk_score)
decision = get_predicted_loan_decision(score)

print("Score: ", round(score, 2))
print(f"Yearly Rate: {predict_interest_rate_from_alvs(score)}")
print(f"Monthly Rate: {round((predict_interest_rate_from_alvs(score) / 12), 2)}")
print("Decision: ", decision)