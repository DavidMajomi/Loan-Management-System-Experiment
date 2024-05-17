import os
import csv
import json
import ctypes
import requests
import random
import sqlite3
import datetime
from faker import Faker
from pathlib import Path
from colorama import Fore

# NEXT TASK: Add a proper debugging mode to reduce the manual methods to the prograam.


PATH = str(Path.cwd())

FORMAT = 'utf-8'

SQLITE3_DATABASE_PATH = PATH + "\\Database files\\loans.db"

OUTPUT_DLL_FILE_PATH = PATH + "\\loanManagementLibrary.dll"  
OUTPUT_DLL_FILE_FOR_SERVER_PATH = PATH + "\\loanManagementServerLibrary.dll"
CSV_FILE_FOR_ALL_GENERATED_DATA_THROUGHOUT_PROGRAM_HISTORY = PATH + "\\Folder with Generated Data\\allGeneratedLoanData.csv"
CSV_FILE_FOR_TEMP_GENERATED_DATA_FOR_db = PATH + "\\Folder with Generated Data\\tempGeneratedLoanDataForDbStorage.csv"


MAX_VALUES_TO_GENERATE = 100000

class UserData(ctypes.Structure):
    _fields_ = [("user_name", ctypes.c_char_p),
                ("user_credit_score", ctypes.c_short),
                ("user_monthly_income", ctypes.c_double),
                ("user_financial_reserves", ctypes.c_double),
                ("user_debt_to_income_ratio", ctypes.c_double),
                ("user_loan_amoumnt_requested", ctypes.c_double),
                ("user_loan_duration", ctypes.c_int)]
        
        
def validate_string_input_for_num_value (data_to_validate, max_value, min_value):
    valid_values = True
    
    stringLength = len(data_to_validate)
    num_value = int(data_to_validate)
    
    if ((num_value < min_value) or (num_value > max_value)):
        valid_values = False
    else:    
        for i in range(stringLength):
            characterValue =  data_to_validate[i]
            
            if not characterValue.isdigit():
                valid_values = False
        
    return valid_values
            

def menu():
    valid_inputs = False
    
    while (valid_inputs == False):
        print(" Welcome to loan management system. Read and follow the recieved_instructions below to perform your operation. ", "\n")
        
        print(" To add a new loan, enter 1. ")
        print(" To search for loan data enter 2.")
        print(" To open dev menu, enter 3.")
        print(" To Run the program using the dll file enter 4.")
        
        user_menu_response = input(" What would you like to do: ")
        
        min_options = 1
        max_options = 4
        
        valid_inputs = validate_string_input_for_num_value(user_menu_response, max_options, min_options)
        
        if (valid_inputs is False):
            print(" Data enteered is in invalid format. \n")
    
    user_menu_response = int(user_menu_response)
    
    return user_menu_response


def menu_for_server_client():
    valid_inputs = False
    
    while (valid_inputs == False):
        print(" Welcome to loan management system. Read and follow the recieved_instructions below to perform your operation. ", "\n")
        
        print(" To add a new loan, enter 1. ")
        print(" To search for loan data enter 2.")
        print(" To open dev menu, enter 3.")
        
        user_menu_response = input(" What would you like to do: ")
        
        min_options = 1
        max_options = 3
        
        valid_inputs = validate_string_input_for_num_value(user_menu_response, max_options, min_options)
        
        if (valid_inputs is False):
            print(" Data enteered is in invalid format. \n")
    
    user_menu_response = int(user_menu_response)
    
    return user_menu_response


def display_dev_menu ():
    valid_inputs = False
    
    while (valid_inputs is False):
        
        print(" This is dev menu for loan management system. Select from the options below what you would like to do. \n")

        print("1.) Enter 1 to generate and store new data in database.")
        print("2.) Enter 2 to perform data analysis on all csv generated data throughout the history of the program in csv file for data analysis.")
        print("3.) Enter 3 to retrive all stored database values in csv file for data analysis. \n")
        print("4.) Just run c++ nothing else enter 4.", "\n")

        dev_menu_response = input(" What would you like to do: ")
        
        # Change these anytime you modify the number of available user options
        min_options = 1         
        max_options = 4
        
        valid_inputs = validate_string_input_for_num_value(dev_menu_response, max_options, min_options)
        
        if (valid_inputs is False):
            print(" Data enteered is in invalid format. \n")

    dev_menu_response = int(dev_menu_response)
    print(dev_menu_response)
    
    return dev_menu_response


def display_dev_menu_for_server_client():
    num_data_to_generate = None
    numDaysToSimulate = None
    valid_inputs = False
    
    while (valid_inputs is False):
        
        print(" This is dev menu for loan management system. Select from the options below what you would like to do. \n")

        print("1.) Enter 1 to generate and store new data in database.")
        print("2.) Enter 2 to perform data analysis on all csv generated data throughout the history of the program in csv file for data analysis.")
        print("3.) Enter 3 to retrive all stored database values in csv file for data analysis.")
        print("4.) Enter 4 to force start end of day processing.")
        print("5.) Enter 5 to simulate multiple days of end of day processing. \n")

        dev_menu_response = input(" What would you like to do: ")
        
        # Change these anytime you modify the number of available user options
        min_options = 1         
        max_options = 5
        
        valid_inputs = validate_string_input_for_num_value(dev_menu_response, max_options, min_options)
        
        if (valid_inputs is False):
            print(" Data enteered is in invalid format. \n")

    dev_menu_response = int(dev_menu_response)
    
    if (dev_menu_response == 1):
        num_data_to_generate = int(input(f" How much data would you like to generate (how many users do you want to generate) note cannot generate more than, {MAX_VALUES_TO_GENERATE} users at a time: "))
    elif (dev_menu_response == 5):
        numDaysToSimulate = int(input(f" How many days would you like to simulate: "))
        num_data_to_generate = None
    else:
        num_data_to_generate = None
        numDaysToSimulate = None
    
    return dev_menu_response, num_data_to_generate, numDaysToSimulate


def get_customer_data_from_cli_for_server():
    
    user_name = "test python"#input("Enter name in the form firstName Lastname: ")
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
    
    
    return customer_data


# Add functionality to generate time of application to ensure different scenarios for end of day processing to create and test payment functionality
def generate_data (num_data_to_generate):
    print(" In function to generate data")
    fake = Faker()

    loan_data_header = ['Name', "credit score", 'monthly income', 'financial reserves', 'debt to income ratio', 'Duration in months', 'loan amount requested']
    loan_data = []
    
    min_options = 0
    
    
    if ((num_data_to_generate < min_options) or (num_data_to_generate > MAX_VALUES_TO_GENERATE)):
        print(" Data entered is in invalid format. \n")
        
    else:
        num_data_to_generate = int(num_data_to_generate)

        # Generate user data
        for i in range(num_data_to_generate):
            credit_score = random.randint(300, 850)
            user_name = fake.name()
            user_monthly_income = round(random.uniform(900, 12000), 2)
            user_debt_to_income_ratio = round(random.uniform(0.00, 1.00), 2)
            
            if (user_monthly_income < 3000):
                financial_reserves = round(random.uniform(500.00, 5000.00), 2)
            elif (user_monthly_income > 3000 and user_monthly_income < 5000):
                financial_reserves = round(random.uniform(5000.00, 10000.00), 2)
            elif (user_monthly_income > 5000 and user_monthly_income < 10000):
                financial_reserves = round(random.uniform(10000.00, 20000.00), 2)
            elif (user_monthly_income > 10000 and user_monthly_income <= 20000):
                financial_reserves = round(random.uniform(20000.00, 35000.00), 2)
            else:
                financial_reserves = round(random.uniform(35000.00, 50000.00), 2)
                
            loan_duration_in_months = random.randint(2, 60)
            loan_amonut_requested = random.randint(500, 20000)
                
            loan_data.append([user_name, credit_score, user_monthly_income, financial_reserves, user_debt_to_income_ratio, loan_duration_in_months, loan_amonut_requested])
            
            if (i % 10000 == 0):
                print(f"\n \n \n \n This is num generated data: {i} \n \n")
            
        if os.path.exists(CSV_FILE_FOR_ALL_GENERATED_DATA_THROUGHOUT_PROGRAM_HISTORY):
            with open(CSV_FILE_FOR_ALL_GENERATED_DATA_THROUGHOUT_PROGRAM_HISTORY, "a", newline = '') as file:
                writer = csv.writer(file)
                writer.writerows(loan_data)    
        else:
            with open(CSV_FILE_FOR_ALL_GENERATED_DATA_THROUGHOUT_PROGRAM_HISTORY, "w", newline = '') as file:
                writer = csv.writer(file)
                writer.writerow(loan_data_header)
                writer.writerows(loan_data)
        
        with open(CSV_FILE_FOR_TEMP_GENERATED_DATA_FOR_db, "w", newline = '') as file:  # This is used to store newly generated data to be used
            writer = csv.writer(file)
            writer.writerow(loan_data_header)
            writer.writerows(loan_data)
        
        print(" Loan data has been written successfully.")


def menu_to_search_for_loan_from_server():
    valid_inputs = False
    customer_name = None
    loan_id = None
    user_has_loan_id = False
    
    while (valid_inputs == False):
        print(" This is search for loan data menu. \n")
        print(".1) If you have your loan id enter 1")
        print(".2) If you do not have your loan id, enter 2 ")
        
        user_response = input(" What is your response: ")
        
        min_options = 1
        max_options = 2
        
        valid_inputs = validate_string_input_for_num_value(user_response, max_options, min_options)
        
        if (valid_inputs is False):
            print(" Data enteered is in invalid format. \n")
            
    user_response = int(user_response)
    
    if (user_response == 1):
        user_has_loan_id = True
        loan_id = input("Enter Loan ID: ")
        
    elif (user_response == 2):
        customer_name = str(input("Enter your name first name first: "))
        
    search_menu_response_data = {
            "user_name" : customer_name,
            "user_has_loan_id" : user_has_loan_id, 
            "user_loan_id" : loan_id
        }
    
    return user_response, search_menu_response_data


def menu_to_search_for_loan():
    valid_inputs = False
    
    while (valid_inputs == False):
        print(" This is search for loan data menu. \n")
        print(".1) If you have your loan id enter 1")
        print(".2) If you do not have your loan id, enter 2 ")
        
        user_response = input(" What is your response: ")
        
        min_options = 1
        max_options = 2
        
        valid_inputs = validate_string_input_for_num_value(user_response, max_options, min_options)
        
        if (valid_inputs is False):
            print(" Data enteered is in invalid format. \n")
            
    user_response = int(user_response)
    
    return user_response

    
def search_for_loan_data_given_loan_id_from_server(recieved_loan_id):
    operation_state_data = {
        "successful_search" : False,
        "found_user_data" : False,
        "error_searching_db" : False,
        "sqlite_error_value" : None
    }
    
    user_accessible_db_data = {
        "loan_id" : None,
        "user_name" : None,
        "credit_score" : None,
        "monthly_income" : None,
        "financial_reserves" : None,
        "debt_to_income_ratio" : None,
        "loan_duration_left" : None,
        "requested_loan_amount" : None,
        "monthly_interest_rate" : None,
        "yearly_interst_rate" : None
        
    }
    
    try:
        # Connect to the SQLite database
        conn = sqlite3.connect(SQLITE3_DATABASE_PATH)
        cursor = conn.cursor()

        # Replace 'your_table' with the name of your table and 'primary_key_column' with the name of the primary key column
        cursor.execute("SELECT * FROM users WHERE Loan_id = ?", (recieved_loan_id,))

        # Fetch the result (should be a single row if primary key is unique)
        row = cursor.fetchone()

        # If the row is not None, print or process the data
        if row:
            operation_state_data["successful_search"] = True
            operation_state_data["found_user_data"] = True
            # print("Row found:")
            # print(row, "\n")
            (loan_id, 
            user_name, 
            time_of_application,
            credit_score, 
            monthly_income, 
            financial_reserves,
            debt_to_income_ratio,
            loan_duration,
            duration_to_next_installment_days,
            duration_to_loan_settlement_months,
            requested_loan_amount,
            monthly_interest_rate,   
            yearly_interest_rate,
            loss_given_default,
            recovery_rate,
            outstanding_monthly_debt_paymentd_from_loan,
            outstanding_monthly_debt_payments_prior_to_loan,
            amount_to_pay_at_next_installment,
            default_risk_score,
            loan_viability_score,                
            adjusted_loan_viability_score,
            matrix_based_adjusted_loan_viability_score,
            interest_rate_by_group,
            best_possible_yearly_rate,
            worst_possible_yearly_rate,
            final_loan_grade,
            potential_profit_from_loan,
            calculated_best_possible_loan_viabbility_score,
            calculated_worst_possible_loan_viabbility_score,
            amount_of_current_loan_and_interests_left,
            loan_decision,
            loan_status,
            applied_today_or_not,
            account_number,
            endOfProcessing) = row
            # print(loan_id, user_name, credit_score, monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rates, yearly_interst_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_payments_to_satisfy_loan, default_risk_score, loan_viability_score, adjusted_loan_viability_score)
            
            # retrieved_user_data = {
            #     "loan_id" : loan_id,
            #     "user_name" : user_name,
            #     "credit_score" : credit_score,
            #     "monthly_income" : monthly_income,
            #     "financial_reserves" : financial_reserves,
            #     "debt_to_income_ratio" : debt_to_income_ratio,
            #     "loan_duration_left" : loan_duration,
            #     "requested_loan_amount" : requested_loan_amount,
            #     "monthly_interest_rate" : monthly_interest_rate,
            #     "yearly_interst_rate" : yearly_interest_rate
                
            #     # "loss_given_default" : loss_given_default,
            #     # "recovery_rate" : recovery_rate,
            #     # "outstanding_monthly_debt_payments_to_satisfy_loan" : outstanding_monthly_debt_payments_to_satisfy_loan,
            #     # "default_risk_score" : default_risk_score,
            #     # "loan_viability_score" : loan_viability_score,
            #     # "adjusted_loan_viability_score" : adjusted_loan_viability_score
            # }
            retrieved_user_data = {
                    "loan_id" : loan_id,
                    "user_name" : user_name,
                    "credit_score" : credit_score,
                    "monthly_income" : monthly_income,
                    "financial_reserves" : financial_reserves,
                    "debt_to_income_ratio" : debt_to_income_ratio,
                    "loan_duration_left" : loan_duration,
                    "duration_to_next_installment_days" : duration_to_next_installment_days,
                    "duration_to_loan_settlement_months" : duration_to_loan_settlement_months,
                    "requested_loan_amount" : requested_loan_amount,
                    "monthly_interest_rate" : monthly_interest_rate,
                    "yearly_interst_rate" : yearly_interest_rate,
                    "outstanding_monthly_debt_paymentd_from_loan" : outstanding_monthly_debt_paymentd_from_loan,
                    "outstanding_monthly_debt_payments_prior_to_loan" : outstanding_monthly_debt_payments_prior_to_loan,
                    "amount_to_pay_at_next_installment" : amount_to_pay_at_next_installment,
                    "loan_decision" :loan_decision,
                    "loan_status" : loan_status,
                    "account_number" : account_number
                }
            # print(f" print loan id {loan_id}")
            
            user_accessible_db_data.update(retrieved_user_data)

        else:
            operation_state_data["successful_search"] = True
            operation_state_data["found_user_data"] = False
            print("Row not found.")
    except sqlite3.Error as e:
        operation_state_data["successful_search"] = False
        operation_state_data["error_searching_db"] = True
        operation_state_data["sqlite_error_value"] = str(e)
        
        # print("Error:", e)
        
    finally:
        # Close the cursor and the connection
        cursor.close()
        conn.close()
        
        
    return operation_state_data, user_accessible_db_data


def search_for_loan_data_without_loan_id_for_server(user_name):
    list_of_loan_data = []
    
    operation_state_to_return = {
        "added_user_data_successfully" : False,
        "error_opening_file_to_store_generated_data" : False,
        "successful_search" : False,
        "found_user_data" : False,
        "error_searching_db" : False,
        "sqlite_error_value" : None,
        "error_opening_file_to_store_analyzed_data" : False,
        "error_getting_data_from_db_to_analyze" : False
    }
    
    single_retrieved_user_data_to_return = {
        "loan_id" : None,
        "user_name" : None,
        "credit_score" : None,
        "monthly_income" : None,
        "financial_reserves" : None,
        "debt_to_income_ratio" : None,
        "loan_duration_left" : None,
        "requested_loan_amount" : None,
        "monthly_interest_rate" : None,
        "yearly_interst_rate" : None
    }
    

    try:
        # Connect to the SQLite database
        conn = sqlite3.connect(SQLITE3_DATABASE_PATH)
        cursor = conn.cursor()

        cursor.execute("SELECT * FROM users WHERE name = ?", (user_name,))

        rows = cursor.fetchall()
        
        # If the row is not None, print or process the data
        if rows:
            operation_state_to_return["successful_search"] = True
            operation_state_to_return["found_user_data"] = True
            # print("Data found:")
            # print(rows, "\n")
            num_rows = len(rows)
            # print("Num rows = ", num_rows)
            
            for data in rows:
                (loan_id, 
                user_name, 
                time_of_application,
                credit_score, 
                monthly_income, 
                financial_reserves,
                debt_to_income_ratio,
                loan_duration,
                duration_to_next_installment_days,
                duration_to_loan_settlement_months,
                requested_loan_amount,
                monthly_interest_rate,   
                yearly_interest_rate,
                loss_given_default,
                recovery_rate,
                outstanding_monthly_debt_paymentd_from_loan,
                outstanding_monthly_debt_payments_prior_to_loan,
                amount_to_pay_at_next_installment,
                default_risk_score,
                loan_viability_score,                
                adjusted_loan_viability_score,
                matrix_based_adjusted_loan_viability_score,
                interest_rate_by_group,
                best_possible_yearly_rate,
                worst_possible_yearly_rate,
                final_loan_grade,
                potential_profit_from_loan,
                calculated_best_possible_loan_viabbility_score,
                calculated_worst_possible_loan_viabbility_score,
                amount_of_current_loan_and_interests_left,
                loan_decision,
                loan_status,
                applied_today_or_not,
                account_number,
                endOfProcessing) = data
                
                
                retrieved_user_data = {
                    "loan_id" : loan_id,
                    "user_name" : user_name,
                    "credit_score" : credit_score,
                    "monthly_income" : monthly_income,
                    "financial_reserves" : financial_reserves,
                    "debt_to_income_ratio" : debt_to_income_ratio,
                    "loan_duration_left" : loan_duration,
                    "duration_to_next_installment_days" : duration_to_next_installment_days,
                    "duration_to_loan_settlement_months" : duration_to_loan_settlement_months,
                    "requested_loan_amount" : requested_loan_amount,
                    "monthly_interest_rate" : monthly_interest_rate,
                    "yearly_interst_rate" : yearly_interest_rate,
                    "outstanding_monthly_debt_paymentd_from_loan" : outstanding_monthly_debt_paymentd_from_loan,
                    "outstanding_monthly_debt_payments_prior_to_loan" : outstanding_monthly_debt_payments_prior_to_loan,
                    "amount_to_pay_at_next_installment" : amount_to_pay_at_next_installment,
                    "loan_decision" :loan_decision,
                    "loan_status" : loan_status,
                    "account_number" : account_number
                }
                
                retrieved_user_data_copy = retrieved_user_data.copy()
                
                list_of_loan_data.append(retrieved_user_data_copy)
                # print(list_of_loan_data) 
 
        else:
            operation_state_to_return["successful_search"] = True
            operation_state_to_return["found_user_data"] = False
            

            print("Row not found.")
    except sqlite3.Error as e:
        operation_state_to_return["successful_search"] = False
        operation_state_to_return["error_searching_db"] = True
        operation_state_to_return["sqlite_error_value"] = str(e)
        print("Error:", e)
    finally:
        # Close the cursor and the connection
        cursor.close()
        conn.close()
       
        # print(" List of loan data: ",list_of_loan_data) 
        return list_of_loan_data, operation_state_to_return
    
    
def compile_dll_with_make():
    os.system("make")
    os.system("make clean")
    
    
def display_single_retrieved_data(retrieved_user_data):
    print(Fore.WHITE)
    user_name = str(input(" Enter your name to confirm your identity: "))
    
    if (user_name == retrieved_user_data['user_name']):

        print("Loan id: ", retrieved_user_data['loan_id'])
        print("Your Fullname: ", retrieved_user_data['user_name'])
        print("Your Credit Score: ", retrieved_user_data['credit_score'])
        print("Your Stated Monhtly Income: $", retrieved_user_data['monthly_income'])
        print("Your stated Financial Reserves Valuation: $", retrieved_user_data['financial_reserves'])
        print("Your provided debt to income ratio:", retrieved_user_data['debt_to_income_ratio'])
        print("Your requested Loan Duration is", retrieved_user_data['loan_duration_left'], "months")
        print("Your requested Loan Amount: $", retrieved_user_data['requested_loan_amount'])
        print("Your monthly interest rate:", retrieved_user_data['monthly_interest_rate'], "%")
        print("Your Monthly Interest over a year:", retrieved_user_data['yearly_interst_rate'], "%")
        
        if (bool(retrieved_user_data['loan_decision']) == True):
            print("Loan application decision:", "Applied Succesfully, your loan has been granted.")
            print("Your total outstanding monthly debt payments from previous and current loans at time of application:", retrieved_user_data["outstanding_monthly_debt_paymentd_from_loan"])
            print("Amount to pay at next installment", retrieved_user_data["amount_to_pay_at_next_installment"])
            print("Loan Status:", retrieved_user_data["loan_status"], "\n")
        else:
            print("Loan application decision:", "Applied Succesfully, however your appication has been denied.", " \n")
                
        
    else:
        print(" Credentials do not match")
 

def display_multiple_retrieved_data(list_of_retrieved_user_data):
    print(Fore.WHITE)

    print("Your Fullname: ", list_of_retrieved_user_data[0]['user_name'])
    
    for retrieved_user_data in list_of_retrieved_user_data:
        print("Loan id: ", retrieved_user_data['loan_id'])
        print("Your stated Credit Score at the time: ", retrieved_user_data['credit_score'])
        print("Your Stated Monhtly Income at the time: $", retrieved_user_data['monthly_income'])
        print("Your stated Financial Reserves Valuation at the time: $", retrieved_user_data['financial_reserves'])
        print("Your provided debt to income ratio at the time of application: ", retrieved_user_data['debt_to_income_ratio'])
        print("Your requested Loan Duration is", retrieved_user_data['loan_duration_left'], "months")
        print("Your requested Loan Amount: $", retrieved_user_data['requested_loan_amount'])
        print("Your monthly interest rate:", retrieved_user_data['monthly_interest_rate'], "%")
        print("Your Monthly Interest over a year:", retrieved_user_data['yearly_interst_rate'], "%")
        
        if (bool(retrieved_user_data['loan_decision']) == True):
            print("Loan application decision:", "Applied Succesfully, your loan has been granted.")
            print("Your total outstanding monthly debt payments from previous and current loans at time of application:", retrieved_user_data["outstanding_monthly_debt_paymentd_from_loan"])
            print("Amount to pay at next installment", retrieved_user_data["amount_to_pay_at_next_installment"])
            print("Loan Status:", retrieved_user_data["loan_status"], "\n")
        else:
            print("Loan application decision:", "Applied Succesfully, however your appication has been denied.", " \n")
                
        
             
        
        print("\n")


def dev_menu_response(instructions, operation_state):
    print(Fore.WHITE)
    
    if (instructions["dev_menu_response"] == 1):
        if not (operation_state["error_opening_file_to_store_generated_data"]):
            print(Fore.GREEN + " Generated Data Successfully")
        else:
            print(Fore.RED + " Failed to generate data.")
    elif (instructions["dev_menu_response"] == 2):
        if not (operation_state["error_opening_file_to_store_analyzed_data"]):
                print(Fore.GREEN + " Analyzed Data Successfully")
        else:
            print(Fore.RED + " Failed to analyze data.")
                
    elif (instructions["dev_menu_response"] == 3):
        
        if (instructions["generate_data_for_db"] == True):
            
            if not operation_state["error_opening_file_to_store_generated_data"]:
                print(Fore.GREEN + " Analyzed Data Successfully")
            else:
                print(Fore.RED + " Failed to analyze data.")
            
        elif (dev_menu_response == 2):
            # if not instructions["perform_data_analysis_on_all_generated_csv_data"]:
            
            if not operation_state["error_opening_file_to_store_analyzed_data"]:
                print(Fore.GREEN + " Analyzed Database values Successfully")
            else:
                print(Fore.RED + " Failed to store all datatbase values in csv file for analysis.")
                
        elif (dev_menu_response == 3):
            if not operation_state["error_getting_data_from_db_to_analyze"]:
                print(Fore.GREEN + " Analyzed Database values Successfully")
            else:
                print(Fore.RED + " Failed to store all datatbase values in csv file for analysis.")
                
    
def get_prime_rate_with_alpha_vantage_api():
    change_base_rate = True

    if os.path.exists(PATH + "\\..\\API keys\\alphaVantageApiKey.txt"):
        with open((PATH + "\\..\\API keys\\alphaVantageApiKey.txt"), "r") as file:
            api_key = file.readline()
    else:
        change_base_rate = False

    url = f'https://www.alphavantage.co/query?function=FEDERAL_FUNDS_RATE&interval=monthly&apikey={api_key}'
    returnedData = requests.get(url)
    data = returnedData.json()

    # last_month = data["data"][0]["date"]
    last_months_federal_funds_rate = float(data["data"][0]["value"])
    
    last_months_federal_funds_rate = ctypes.c_double(last_months_federal_funds_rate)

    # jsonData = json.dumps(data, indent = 2)

    # print(last_month)
    # print(last_months_prime_rate)
    
    return change_base_rate, last_months_federal_funds_rate


def use_python_for_cpp_eceonomic_metrics():
    changed_base_rate = True

    if os.path.exists(PATH + "\\API keys\\alphaVantageApiKey.txt"):
        with open((PATH + "\\API keys\\alphaVantageApiKey.txt"), "r") as file:
            api_key = file.readline()
    else:
        changed_base_rate = False

    url = f'https://www.alphavantage.co/query?function=FEDERAL_FUNDS_RATE&interval=monthly&apikey={api_key}'
    returnedData = requests.get(url)
    data = returnedData.json()

    last_months_federal_funds_rate = float(data["data"][0]["value"])
    
    print(f" This is last months federal funds rate: {last_months_federal_funds_rate}")
    last_months_federal_funds_rate = ctypes.c_double(last_months_federal_funds_rate)


    url = f'https://www.alphavantage.co/query?function=TREASURY_YIELD&interval=daily&maturity=10year&apikey={api_key}'

    returnedData = requests.get(url)
    data_for_ten_year_yield = returnedData.json()


    last_months_ten_year_yield = float(data_for_ten_year_yield["data"][0]["value"])

    url = f'https://www.alphavantage.co/query?function=TREASURY_YIELD&interval=daily&maturity=3month&apikey={api_key}'


    returnedData = requests.get(url)
    data_for_three_month_yield = returnedData.json()

    last_months_three_month_yield = float(data_for_three_month_yield["data"][0]["value"])


    print(" Interval = daily")
    print(f" Last months 3 month yield = {last_months_three_month_yield}")
    print(f" Last months 10 year yield = {last_months_ten_year_yield}")

    print(f" Yield Spread = { last_months_ten_year_yield - last_months_three_month_yield}")

    if ((last_months_ten_year_yield - last_months_three_month_yield) < 0):
        print(" There is a yield curve inversion which suggests lowered investor confidence in long term economic success. There should be increased tightening on loan grants.")
    else:
        print(" This is a normal yield result suggesting normal economic activities. ")
        
    print(" This is barrier \n \n  \n")
    url = f'https://www.alphavantage.co/query?function=REAL_GDP&interval=annual&apikey={api_key}'
    returnedData = requests.get(url)
    data = returnedData.json()

    # print(data)
    
    return changed_base_rate, last_months_federal_funds_rate

    
def change_base_rate_for_server(cpp_library, this_months_prime_rate):
    cpp_library.changeBaseRate(this_months_prime_rate)
 
   
def use_cpp_from_server(recieved_data, cpp_library):
    user_data = recieved_data["customer_data"]
    recieved_instructions = recieved_data["instructions"]
    
    list_of_retrieved_user_data = []
    
    operation_state_to_return = {
        "added_user_data_successfully" : False,
        "error_opening_file_to_store_generated_data" : False,
        "successful_search" : False,
        "found_user_data" : False,
        "error_searching_db" : False,
        "sqlite_error_value" : None,
        "error_opening_file_to_store_analyzed_data" : False,
        "error_getting_data_from_db_to_analyze" : False,
        "succesfull_end_of_day_processing" : False
        # "running_end_of_day_processing " : False
    }
    
    single_retrieved_user_data_to_return = {
                    "loan_id" : None,
                    "user_name" : None,
                    "credit_score" : None,
                    "monthly_income" : None,
                    "financial_reserves" : None,
                    "debt_to_income_ratio" : None,
                    "loan_duration_left" : None,
                    "duration_to_next_installment_days" : None,
                    "duration_to_loan_settlement_months" : None,
                    "requested_loan_amount" : None,
                    "monthly_interest_rate" : None,
                    "yearly_interst_rate" : None,
                    "outstanding_monthly_debt_paymentd_from_loan" : None,
                    "outstanding_monthly_debt_payments_prior_to_loan" : None,
                    "amount_to_pay_at_next_installment" : None,
                    "loan_decision" : None,
                    "loan_status" : None,
                    "account_number" : None
                }
    
    data_for_each_loan_item = {
        "retrieved_user_data_to_return" : single_retrieved_user_data_to_return
    }

    # print(user_data)
    print(" On cpp server side")
    
    menu_response = recieved_instructions["menu_response"]
    dev_menu_response= recieved_instructions["dev_menu_response"]
    search_menu_response = recieved_instructions["search_menu_response"]
    
    if (menu_response == 1): # Add individualized loan using data
        # print(f" Thi is user data before db {user_data['user_name']}")
        
        addIndividualizedDataToDb = cpp_library.addIndividualizedDataToDb
        addIndividualizedDataToDb.restype = ctypes.c_bool
        
        # data_to_cpp = UserData(user_data['user_name'].encode(FORMAT), int(user_data['user_credit_score']), float(user_data['user_monthly_income']), float(user_data['user_financial_reserves']), float(user_data['user_debt_to_income_ratio']), float(user_data['user_loan_amoumnt_requested']), int(user_data['user_loan_duration']))
        
        data_to_cpp = UserData(str(user_data['user_name']).encode(FORMAT), 
                    int(user_data['user_credit_score']), 
                    float(user_data['user_monthly_income']), 
                    float(user_data['user_financial_reserves']), 
                    float(user_data['user_debt_to_income_ratio']), 
                    float(user_data['user_loan_amoumnt_requested']), 
                    int(user_data['user_loan_duration']))
        
        operation_state_to_return["added_user_data_successfully"] = not(addIndividualizedDataToDb(data_to_cpp))
        print(operation_state_to_return["added_user_data_successfully"])
        
    elif (menu_response == 2):
        
        if (user_data["user_has_loan_id"] == True):
            search_for_loan_operation_state, recovered_db_data = search_for_loan_data_given_loan_id_from_server(int(user_data["user_loan_id"]))
            # print(f"recovered data = {recovered_db_data}")
            
            single_retrieved_user_data_to_return.update(recovered_db_data)
            operation_state_to_return.update(search_for_loan_operation_state)
            
            data_for_each_loan_item = {
                "retrieved_user_data_to_return" : single_retrieved_user_data_to_return
            }
            
            list_of_retrieved_user_data.append(data_for_each_loan_item)
        else:
            temp_list_data, temp_operation_state = search_for_loan_data_without_loan_id_for_server(user_data["user_name"])
            
            operation_state_to_return.update(temp_operation_state)
            if operation_state_to_return["found_user_data"] == True:
                
                print(temp_list_data[0])
                single_retrieved_user_data_to_return.update(temp_list_data[0])  # Error in this line that needs to be fixed as soon as possible
                list_of_retrieved_user_data.extend(temp_list_data)
            
    elif (menu_response == 3):
    
        if (recieved_instructions["generate_data_for_db"] == True):
            readAndStoreGeneratedDataInDb = cpp_library.readAndStoreGeneratedDataInDb
            readAndStoreGeneratedDataInDb.restype = ctypes.c_bool
            
            generate_data(recieved_instructions["num_data_to_generate"])
            
            error_opening_file_to_store_generated_data = (readAndStoreGeneratedDataInDb(recieved_instructions["dev_menu_response"]))
            
            print(f" This is bool for error generating data: {error_opening_file_to_store_generated_data}")
            operation_state_to_return["error_opening_file_to_store_generated_data"] = error_opening_file_to_store_generated_data
            
        elif (dev_menu_response == 2):
            # recieved_instructions["perform_data_analysis_on_all_generated_csv_data"] = True
            operation_state_to_return["error_opening_file_to_store_analyzed_data"] = bool(cpp_library.readAndStoreGeneratedDataForAnalysis(recieved_instructions["dev_menu_response"]))
            print(f" This is the bool value for error opening file line 720 {operation_state_to_return['error_opening_file_to_store_analyzed_data']}")
        elif (dev_menu_response == 3):
            # recieved_instructions["store_all_db_data_for_external_analysis"] = True
            operation_state_to_return["error_getting_data_from_db_to_analyze"] = bool(cpp_library.readAllDatabaseDataForAnalysis())
            
        elif(recieved_instructions["start_end_of_day_processing"] == True):
            # if(recieved_instructions[""])
            
            for x in range(int((recieved_instructions["num_days_to_simulate"]))):
                print("Performing end of days")
                operation_state_to_return["succesfull_end_of_day_processing"] = not (bool(cpp_library.startEndOfDayOperations()))
            
            
            
    data_to_send_Back_to_client = {
        "operation_state_to_return" : operation_state_to_return,
        "retrieved_user_data_to_return" : single_retrieved_user_data_to_return,
        "list_of_retrieved_user_data" : list_of_retrieved_user_data
    }
        
    print(" \n Done")
    return data_to_send_Back_to_client
    
    
    
