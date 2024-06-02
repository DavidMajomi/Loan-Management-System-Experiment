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
from sklearn.linear_model import LogisticRegression



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



    
df = pd.read_csv("../Csv Files For Analysis/analyzedDataFromDb.csv")
df = df.dropna()
df = df.drop(columns=['Name'])
# print(df)

def predictYearlyInterestRateByGroup(credit_score):
        
    columns = ["credit_score"]
    x = df[columns]
    y = df['interest_rate_by_group']

    X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.4, random_state=101) 

    model = DecisionTreeRegressor()

    model.fit(X_train.values, y_train.values)

    predictions = model.predict(X_test)

    print("Mean Squared error: ", mean_squared_error(y_test, predictions))
    print("Mean absolute error: ", mean_absolute_error(y_test, predictions))
    
    return float(model.predict([[credit_score]]))


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
    
    return float(model.predict([[credit_score, monthly_income, financial_reserves, 
                                                          debt_to_income_ratio, Duration_in_months, 
                                                          loan_amount_requested, 
                                                          loss_Given_Default, 
                                                          defult_risk_score]])), model


def predictDefaultRiskScore(monthly_interest_rate_by_group, super_prime_rate, deep_sub_prime_rate):
    columns = ["interest_rate_by_group"]
    # columns = ["interest_rate_by_group", "best_possible_rate", "worst_possible_rate"]

    x = df[columns]
    x = x.div(12)
    y = df['default_risk_score']

    X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.4, random_state=101) 

    modelRate = LinearRegression()

    modelRate.fit(X_train.values, y_train.values)

    predictions = modelRate.predict(X_test)

    print("Mean Squared error: ", mean_squared_error(y_test, predictions))
    print("Mean absolute error: ", mean_absolute_error(y_test, predictions))
    
    # default_risk_score = float(modelRate.predict([[monthly_interest_rate_by_group, super_prime_rate, deep_sub_prime_rate]]))
    default_risk_score = float(modelRate.predict([[monthly_interest_rate_by_group]]))
    
    # return default_risk_score, modelRate
    return monthly_interest_rate_by_group - ((super_prime_rate - 3) / 12), modelRate


def predictInterestRateFromAlvs(alvs):
    columns = ['Adjusted_Loan_viability_Score']
    x = df[columns]
    y = df['Interest_rate_over_a_year']

    X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.4, random_state=101) 

    model = LinearRegression()

    model.fit(X_train.values, y_train.values)

    predictions = model.predict(X_test)

    print("Mean Squared error: ", mean_squared_error(y_test, predictions))
    print("Mean absolute error: ", mean_absolute_error(y_test, predictions))
    
    return float(model.predict([[alvs]])), model
  
  
credit_score = 850
monthly_income = 12000
financial_reserves = 50000
debt_to_income_ratio = 0
Duration_in_months = 1
loan_amount_requested = 20000


# credit_score = 350
# monthly_income = 2000
# financial_reserves = 1084.64
# debt_to_income_ratio = 0.42
# Duration_in_months = 13
# loan_amount_requested = 9413
  
interestRateByGroup = predictYearlyInterestRateByGroup(credit_score)

    
monthly_interest_rate_by_group = interestRateByGroup / 12
    
# defult_risk_score = monthly_interest_rate_by_group - (super_prime_rate / 12)
print(monthly_interest_rate_by_group - (super_prime_rate / 12))
print(super_prime_rate)
print("_____________________")
defult_risk_score, defaulr_risk_model = predictDefaultRiskScore(monthly_interest_rate_by_group, super_prime_rate, deep_sub_prime_rate)

loss_Given_Default = (loan_amount_requested - financial_reserves) / loan_amount_requested; # SOURCE = WIKIPEDIA


adjusted_loan_viability_score, alvsModel = predictALVS(credit_score, monthly_income, financial_reserves, 
                                                          debt_to_income_ratio, Duration_in_months, 
                                                          loan_amount_requested, 
                                                          loss_Given_Default, 
                                                          defult_risk_score)

# normal_monthly_interest_rate = (slope * adjusted_loan_viability_score) + deep_sub_prime_rate
normal_yearly_interest_rate, yearlyInterestRateModel = predictInterestRateFromAlvs(adjusted_loan_viability_score)



print(adjusted_loan_viability_score)
print(f"This is interest rate by group: {interestRateByGroup}")
print(f"This is monthly interest rate by group: {monthly_interest_rate_by_group}")
print(f"This is  ")
print(f"This is ")
print(f"This is ")
print(f" This is normal rate: {normal_yearly_interest_rate} ")
print(f" This is default risk score: {defult_risk_score} ")


score = df[['Adjusted_Loan_viability_Score']]
decision = df['loan_decision']

theTree = DecisionTreeClassifier()
theTree = theTree.fit(score.values, decision.values)

print("Loan Decision: ", theTree.predict([[adjusted_loan_viability_score]]))

list_of_models = [alvsModel, theTree]

with open("LMSModel.pickle", "wb") as file:
    pickle.dump(list_of_models, file)
