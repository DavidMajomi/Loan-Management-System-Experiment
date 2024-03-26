import os
import json
import ctypes
from pathlib import Path
from header_file_for_testing_dll import test_changing_base_rate, test_storing_generated_data_in_db_from_csv, test_adding_and_computing_for_single_user_data



PATH = str(Path.cwd())

FORMAT = 'utf-8'

OUTPUT_DLL_FILE_FOR_SERVER_PATH = PATH + "\\loanManagementServerLibrary.dll"

    
customer_data = {
    "user_name" : None,
    "user_credit_score" : None,
    "user_monthly_income" : None,
    "user_financial_reserves" : None,
    "user_debt_to_income_ratio" : None,
    "user_loan_amoumnt_requested" : None,
    "user_loan_duration" : None,
    "user_loan_id" : None,
    "user_has_loan_id" : None
}

os.system("make")
os.system("make clean")
    
cpp_library = ctypes.CDLL(OUTPUT_DLL_FILE_FOR_SERVER_PATH, winmode = 0)

test_changing_base_rate(cpp_library)
# test_bool = test_storing_generated_data_in_db_from_csv(cpp_library)

# print(f" This is result of test storing data: {test_bool}")
# print(" This is a test")

user_name = "test baba"#input("Enter name in the form firstName Lastname: ")
# user_credit_score = input("Enter your Credit Score: ")
user_credit_score = "850"# str(user_credit_score)
# user_monthly_income = input("Enter your monthly income: ")
user_monthly_income = "12000"# str(user_monthly_income)
# user_financial_reserves = "200000"# input("Enter your financial reserves: ")
user_financial_reserves = "50000" # str(user_financial_reserves)
# user_debt_to_income_ratio = input("Enter your debt to income ratio: ")
user_debt_to_income_ratio = "0" # str(user_debt_to_income_ratio)
user_loan_amoumnt_requested = "20000" # str(user_loan_amoumnt_requested)
# loan_duration_to_cpp = input("Enter the duration of the loan: ")
user_loan_duration = "1" # str(loan_duration_to_cpp)

customer_data = {
    "user_name" : user_name,
    "user_credit_score" : user_credit_score,
    "user_monthly_income" : user_monthly_income,
    "user_financial_reserves" : user_financial_reserves,
    "user_debt_to_income_ratio" : user_debt_to_income_ratio,
    "user_loan_amoumnt_requested" : user_loan_amoumnt_requested,
    "user_loan_duration" : user_loan_duration
}

test_adding_and_computing_for_single_user_data(customer_data, cpp_library)
print(" This is a test")

# user_data = customer_data
# recieved_instructions = recieved_data["instructions"]

# menu_response = recieved_instructions["menu_response"]
# dev_menu_response= recieved_instructions["dev_menu_response"]
# search_menu_response = recieved_instructions["search_menu_response"]



# cpp_library.addIndividualizedDataToDb(data_to_cpp)

# return_state = cpp_library.readAndStoreGeneratedDataInDb(recieved_instructions["dev_menu_response"])

# operation_state_to_return = cpp_library.readAndStoreGeneratedDataForAnalysis(recieved_instructions["dev_menu_response"])

# operation_state_to_return = cpp_library.readAllDatabaseDataForAnalysis()



        