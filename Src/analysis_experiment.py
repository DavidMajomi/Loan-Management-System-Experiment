import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, mean_absolute_error
from sklearn import preprocessing
from sklearn import linear_model
from sklearn.preprocessing import StandardScaler
import pickle
from sklearn import tree
from sklearn.tree import DecisionTreeClassifier
from sklearn.tree import DecisionTreeRegressor
# from sklearn.linear_model import LogisticRegression



# scale = StandardScaler()

# df = pd.read_csv("../Csv Files For Analysis/analyzedDataFromDb.csv")
# new_df = df.drop(columns = ['final_loan_grade', 'Name'])
# # some_df = df

# # print(df.worst_possible_rate)
# # print(df.Name)
# # print(df.info())
# # print(new_df.info())

# # new_df = df.dropna()
# # print(df.to_string())
# # print(df.duplicated())
# # print(new_df.to_string())
# print(new_df.corr())

# # df.plot()
# # plt.show()
# # x = 
# # [Name	credit_score	monthly_income	financial_reserves	debt_to_income_ratio	Duration_in_months	loan_amount_requested	Monthly_interest_rate	Interest_rate_over_a_year	loss_Given_Default	Recovery_Rate	outstanding_Monthly_Debt_Payments	default_risk_score	Loan_Viability_Score	Adjusted_Loan_viability_Score	]


# # columns = [
# #     'Name', 'credit_score', 'monthly_income', 'financial_reserves',
# #     'debt_to_income_ratio', 'Duration_in_months', 'loan_amount_requested',
# #     'Monthly_interest_rate', 'Interest_rate_over_a_year', 'loss_Given_Default',
# #     'Recovery_Rate', 'outstanding_Monthly_Debt_Payments', 'default_risk_score'
# #     # 'Loan_Viability_Score'
# # ]

# columns = [
#     'credit_score', 'monthly_income', 'financial_reserves',
#     'debt_to_income_ratio', 'Duration_in_months', 'loan_amount_requested'
#     # 'Monthly_interest_rate', 'Interest_rate_over_a_year', 'loss_Given_Default',
#     # 'Recovery_Rate', 'outstanding_Monthly_Debt_Payments', 'default_risk_score'
#     # 'Loan_Viability_Score'
# ]


# x = df[columns]
# # y = df['Adjusted_Loan_viability_Score']
# scaledX = scale.fit_transform(x)
# y = df['Loan_Viability_Score']

# regr = linear_model.LinearRegression()
# regr.fit(scaledX,y)

# # predicted = regr.predict([[850, 12000, 50000, 0, 1, 20000]])
# scaled = scale.transform([[850, 12000, 50000, 0, 1, 20000]])
# predicted = regr.predict([scaled[0]])
# print(predicted)

super_prime_rate = 8.33
deep_sub_prime_rate = 30.00

# slope = (deep_sub_prime_rate - super_prime_rate) / -100 


    
df = pd.read_csv("../Csv Files For Analysis/analyzedDataFromDb.csv")
df = df.dropna()
df = df.drop_duplicates()
df = df.drop(columns=['Name', 'final_loan_grade'])
# print(df.info())
# print(df.corr())
df_corr = df.corr()
# print(df_corr["Interest_rate_over_a_year"])
# print(df_corr['loss_Given_Default'])


def predictYearlyInterestRateByGroup(credit_score):
        
    columns = ["credit_score"]
    x = df[columns]
    y = df['interest_rate_by_group']

    X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.4, random_state=101) 

    model = DecisionTreeRegressor()

    model.fit(X_train.values, y_train.values)

    predictions = model.predict(X_test)

    print("Predicting Yearly interest rate by group")
    print("Mean Squared error: ", mean_squared_error(y_test, predictions))
    print("Mean absolute error: ", mean_absolute_error(y_test, predictions))
    
    return round(float(model.predict([[credit_score]])), 2), model


def predictALVS(credit_score, monthly_income, financial_reserves, 
                                                          debt_to_income_ratio, Duration_in_months, 
                                                          loan_amount_requested, 
                                                          loss_Given_Default, 
                                                          defult_risk_score):
    
    columns = ["credit_score", "monthly_income", "financial_reserves", "debt_to_income_ratio", "Duration_in_months", "loan_amount_requested",
                                    "loss_Given_Default", "default_risk_score"]
    x = df[columns]
    y = df['Adjusted_Loan_viability_Score']

    X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.4, random_state=101) 

    model = LinearRegression()

    model.fit(X_train.values, y_train.values)

    predictions = model.predict(X_test)

    # print("Mean Squared error: ", mean_squared_error(y_test, predictions))
    # print("Mean absolute error: ", mean_absolute_error(y_test, predictions))
    
    return round(float(model.predict([[credit_score, monthly_income, financial_reserves, 
                                                          debt_to_income_ratio, Duration_in_months, 
                                                          loan_amount_requested, 
                                                          loss_Given_Default, 
                                                          defult_risk_score]])), 2), model


def predictDefaultRiskScore(monthly_interest_rate_by_groups):
    columns = ["interest_rate_by_group"]
    # columns = ["interest_rate_by_group", "best_possible_rate", "worst_possible_rate"]

    x = df[columns]
    x = x.div(12)
    y = df['default_risk_score']

    X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.4, random_state=101) 

    modelRate = LinearRegression()

    modelRate.fit(X_train.values, y_train.values)

    predictions = modelRate.predict(X_test)

    print("predicting default risk score")
    print("Mean Squared error: ", mean_squared_error(y_test, predictions))
    print("Mean absolute error: ", mean_absolute_error(y_test, predictions))
    
    # default_risk_score = float(modelRate.predict([[monthly_interest_rate_by_group, super_prime_rate, deep_sub_prime_rate]]))
    default_risk_score = float(modelRate.predict([[monthly_interest_rate_by_group]]))
    
    return round((default_risk_score), 2), modelRate


def predictInterestRateFromAlvs(alvs, deep_sub_prime_rate, super_prime_rate):
    columns = ['Adjusted_Loan_viability_Score']
    x = df[columns]
    y = df['Interest_rate_over_a_year']

    X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.4, random_state=101) 

    model = DecisionTreeRegressor()

    model.fit(X_train.values, y_train.values)

    predictions = model.predict(X_test)

    print("Pridicting final rate")
    print("Mean Squared error: ", mean_squared_error(y_test, predictions))
    print("Mean absolute error: ", mean_absolute_error(y_test, predictions))
    
    # return ((slope * alvs) + deep_sub_prime_rate), model
    return round(float(model.predict([[alvs]])), 2), model


def predictlossGivenDefault(loan_amount_requested, financial_reserves):
    columns = ['loan_amount_requested', 'financial_reserves']
    x = df[columns]
    y = df['loss_Given_Default']

    X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.4, random_state=101) 

    model = DecisionTreeRegressor()

    model.fit(X_train.values, y_train.values)

    predictions = model.predict(X_test)

    print("Pridicting loss given default")
    print("Mean Squared error: ", mean_squared_error(y_test, predictions))
    print("Mean absolute error: ", mean_absolute_error(y_test, predictions))
    
    # return ((slope * alvs) + deep_sub_prime_rate), model
    return round(float(model.predict([[loan_amount_requested, financial_reserves]])), 2), model
  
  
def directAlvsPredictor(credit_score, monthly_income, financial_reserves, debt_to_income_ratio, Duration_in_months, loan_amount_requested):
    columns = ["credit_score", "monthly_income", "financial_reserves", "debt_to_income_ratio", "Duration_in_months", "loan_amount_requested"]
    x = df[columns]
    y = df['Adjusted_Loan_viability_Score']

    X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.4, random_state=101) 

    model = DecisionTreeRegressor()

    model.fit(X_train.values, y_train.values)

    predictions = model.predict(X_test)

    print("Predicting ALVS directly")
    print("Mean Squared error: ", mean_squared_error(y_test, predictions))
    print("Mean absolute error: ", mean_absolute_error(y_test, predictions))
    
    # return ((slope * alvs) + deep_sub_prime_rate), model
    return round(float(model.predict([[credit_score, monthly_income, financial_reserves, 
                                                          debt_to_income_ratio, Duration_in_months, 
                                                          loan_amount_requested]])), 2), model  
    
    
credit_score = 850
monthly_income = 12000
financial_reserves = 50000
debt_to_income_ratio = 0
Duration_in_months = 1
loan_amount_requested = 20000

# credit_score = 612
# monthly_income = 6361.51
# financial_reserves = 17294.9
# debt_to_income_ratio = 0.4
# Duration_in_months = 59
# loan_amount_requested = 14185
  
interestRateByGroup, interest_rate_by_group_model = predictYearlyInterestRateByGroup(credit_score)

    
monthly_interest_rate_by_group = round((interestRateByGroup / 12), 2)
    
defult_risk_score, default_risk_model = predictDefaultRiskScore(monthly_interest_rate_by_group)

# loss_Given_Default = (loan_amount_requested - financial_reserves) / loan_amount_requested; # SOURCE = WIKIPEDIA
loss_Given_Default, loss_Given_Default_model = predictlossGivenDefault(loan_amount_requested, financial_reserves)


adjusted_loan_viability_score, alvsModel = predictALVS(credit_score, monthly_income, financial_reserves, 
                                                          debt_to_income_ratio, Duration_in_months, 
                                                          loan_amount_requested, 
                                                          loss_Given_Default, 
                                                          defult_risk_score)


direct_alvs, direct_alvs_predictor = directAlvsPredictor(credit_score, monthly_income, financial_reserves, 
                                                          debt_to_income_ratio, Duration_in_months, 
                                                          loan_amount_requested)


normal_yearly_interest_rate, yearly_interest_rate_model = predictInterestRateFromAlvs(adjusted_loan_viability_score, deep_sub_prime_rate, super_prime_rate)



print(f"This is interest rate by group: {interestRateByGroup}")
print(f"This is monthly interest rate by group: {monthly_interest_rate_by_group}")
print(f"This is loss given default: {loss_Given_Default}")
# print(f"This is ")
# print(f"This is ")
print(f"This is direct alvs: {direct_alvs}")
print(f"This is alvs: {adjusted_loan_viability_score}")
print(f"This is yearly interest rate: {normal_yearly_interest_rate} ")
print(f"This is default risk score: {defult_risk_score} ")
# print(f"This is slope {slope}")


score = df[['Adjusted_Loan_viability_Score']]
decision = df['loan_decision']

theTree = DecisionTreeClassifier()
theTree = theTree.fit(score.values, decision.values)

print("Loan Decision: ", theTree.predict([[adjusted_loan_viability_score]]))

list_of_models = [interest_rate_by_group_model, default_risk_model, loss_Given_Default_model, alvsModel, yearly_interest_rate_model, theTree]

with open("LMSModel.pickle", "wb") as file:
    pickle.dump(list_of_models, file)


