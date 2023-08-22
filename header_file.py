import os
import csv
import ctypes
import random
import sqlite3
import subprocess
from faker import Faker
from colorama import Fore


FORMAT = 'utf-8'
STAND_ALONE_CPP_EXECUTABLE = "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\just c++.exe"  
MAIN_CPP_FILE = "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\main.cpp"
SQLITE3_DATABASE_PATH = 'C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\bam_bam.db'
SQLITE3_OBJECT_FILE_PATH = "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\sqlite3.o"
LIBRARY_CPP_FILE_PATH = "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\loanManagementLibrary.cpp"
LIBRARY_CPP_FILE_PATH_FOR_SERVER = "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\loanManagementLibraryForServer.cpp"
OUTPUT_DLL_FILE_PATH = "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\loanManagementLibrary.dll"  
OUTPUT_DLL_FILE_FOR_SERVER_PATH = "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\loanManagementSeverLibrary.dll"  
CPP_EXECUTABLE_FROM_PYTHON_PATH = "C:\\Users\\David\\Documents\\loanManagementSystem\\executable from python interface.exe"  

class UserData(ctypes.Structure):
    _fields_ = [("user_name", ctypes.c_char_p),
                ("user_credit_score", ctypes.c_short),
                ("user_monthly_income", ctypes.c_double),
                ("user_financial_reserves", ctypes.c_double),
                ("user_debt_to_income_ratio", ctypes.c_double),
                ("user_loan_amoumnt_requested", ctypes.c_double),
                ("user_loan_duration", ctypes.c_int)]


class Loan:
    def __init__(self, loan_id, user_name, credit_score, monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rates, yearly_interst_rate, loss_given_default, recovery_rate, 
                 outstanding_monthly_debt_payments_to_satisfy_loan, default_risk_score, loan_viability_score, adjusted_loan_viability_score):
        
        self.loan_id = loan_id
        self.user_name = user_name
        self.credit_score = credit_score
        self.monthly_income = round(monthly_income, 2)
        self.financial_reserves = round(financial_reserves, 2)
        self.debt_to_income_ratio = debt_to_income_ratio
        self.loan_duration = loan_duration
        self.requested_laon_amount = round(requested_loan_amount, 2)
        self.monthly_interest_rate = round(monthly_interest_rates, 2)
        self.yearly_interest_rate = round(yearly_interst_rate, 2)
        self.loss_given_default = loss_given_default
        self.recovery_rate = recovery_rate
        self.outstanding_monthly_debt_payments_to_satisfy_loan = outstanding_monthly_debt_payments_to_satisfy_loan
        self.default_risk_score = default_risk_score
        self.loan_viability_score = loan_viability_score
        self.adjusted_loan_viability_score = adjusted_loan_viability_score
        
    def display_loan_data_to_console(self):
        print("Loan id: ", self.loan_id)
        print("Your Fullname: ", self.user_name)
        print("Your Credit Score: ", self.credit_score)
        print("Your Stated Monhtly Income: $", self.monthly_income)
        print("Your stated Financial Reserves Valuation: $", self.financial_reserves)
        print("Your provided debt to income ratio:", self.debt_to_income_ratio)
        print("Your requested Loan Duration is", self.loan_duration, "months")
        print("Your requested Loan Amount: $", self.requested_laon_amount)
        print("Your monthly interest rate:", self.monthly_interest_rate, "%")
        print("Your Monthly Interest over a year:", self.yearly_interest_rate, "% \n")
        
        
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
    valid_inputs = False
    
    while (valid_inputs is False):
        
        print(" This is dev menu for loan management system. Select from the options below what you would like to do. \n")

        print("1.) Enter 1 to generate and store new data in database.")
        print("2.) Enter 2 to perform data analysis on all csv generated data throughout the history of the program in csv file for data analysis.")
        print("3.) Enter 3 to retrive all stored database values in csv file for data analysis. \n")

        dev_menu_response = input(" What would you like to do: ")
        
        # Change these anytime you modify the number of available user options
        min_options = 1         
        max_options = 3
        
        valid_inputs = validate_string_input_for_num_value(dev_menu_response, max_options, min_options)
        
        if (valid_inputs is False):
            print(" Data enteered is in invalid format. \n")

    dev_menu_response = int(dev_menu_response)
    
    if (dev_menu_response == 1):
        num_data_to_generate = int(input(" How much data would you like to generate (how many users do you want to generate) note cannot generate of 20 million users at a time: "))
    else:
        num_data_to_generate = None
    
    
    
    print(dev_menu_response)
    
    return dev_menu_response, num_data_to_generate


def get_customer_data_from_cli_for_server():
    
    user_name = "test baba"#input("Enter name in the form firstName Lastname: ")
    # user_credit_score = input("Enter your Credit Score: ")
    user_credit_score = "850"# str(user_credit_score)
    # user_monthly_income = input("Enter your monthly income: ")
    user_monthly_income = "12000"# str(user_monthly_income)
    # user_financial_reserves = "200000"# input("Enter your financial reserves: ")
    user_financial_reserves = "200000" # str(user_financial_reserves)
    # user_debt_to_income_ratio = input("Enter your debt to income ratio: ")
    user_debt_to_income_ratio = "1" # str(user_debt_to_income_ratio)
    user_loan_amoumnt_requested = "20000" # str(user_loan_amoumnt_requested)
    # loan_duration_to_cpp = input("Enter the duration of the loan: ")
    user_loan_duration = "30" # str(loan_duration_to_cpp)
    
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


def add_loan_using_the_cpp_program():

    # Compile the C++ program with sqlite object file (if needed)
    compile_cpp_command = ["g++", MAIN_CPP_FILE, SQLITE3_OBJECT_FILE_PATH, "-o", CPP_EXECUTABLE_FROM_PYTHON_PATH] #original
    subprocess.run(compile_cpp_command, check=True)
    
    # Run the C++ application as a subprocess
    cpp_process = subprocess.Popen([CPP_EXECUTABLE_FROM_PYTHON_PATH], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    # user_data
    request = '0'
    menu_response = '1'
    user_name = "test baba"#input("Enter name in the form firstName Lastname: ")
    # user_credit_score = input("Enter your Credit Score: ")
    user_credit_score = "850"# str(user_credit_score)
    # user_monthly_income = input("Enter your monthly income: ")
    user_monthly_income = "12000"# str(user_monthly_income)
    # user_financial_reserves = "200000"# input("Enter your financial reserves: ")
    user_financial_reserves = "200000" # str(user_financial_reserves)
    # user_debt_to_income_ratio = input("Enter your debt to income ratio: ")
    user_debt_to_income_ratio = "1" # str(user_debt_to_income_ratio)
    
    enter_new_loan_data = 0

    re_run = False  # This allows to modify the number of outputs to c++
    while (enter_new_loan_data == 0):
        
        # user_loan_amoumnt_requested = input("Enter the amount of money you want to borrow: ")
        user_loan_amoumnt_requested = "20000" # str(user_loan_amoumnt_requested)
        # loan_duration_to_cpp = input("Enter the duration of the loan: ")
        loan_duration_to_cpp = "30" # str(loan_duration_to_cpp)
        enter_new_loan_data = input("Do you want to add a new loan application. Enter 0 for yes, or enter any other number for no: ")
        enter_new_loan_data = str(enter_new_loan_data)
        
    
        # fix entering loan dat as c++ program doesnt progress because of wait function.

        # Send inputs to the C++ application
        if (re_run is False):
            
            inputs = [
                request, "\n",
                menu_response, "\n",
                user_name, "\n",
                user_credit_score, "\n",
                user_monthly_income, "\n",
                user_financial_reserves, "\n",
                user_debt_to_income_ratio, "\n",
                user_loan_amoumnt_requested, "\n",
                loan_duration_to_cpp, "\n",
                enter_new_loan_data, "\n"
            ]
        elif (re_run is True):
            inputs = [
                user_loan_amoumnt_requested, "\n",
                loan_duration_to_cpp, "\n",
                enter_new_loan_data, "\n"
            ]
            

        enter_new_loan_data = int(enter_new_loan_data)
        
        if (enter_new_loan_data == 0):
            re_run = True
        
        for input_data in inputs:
            cpp_process.stdin.write(input_data.encode())


    cpp_process.stdin.close()

    # Read the output and error streams from the C++ application
    output = cpp_process.stdout.read().decode()
    errors = cpp_process.stderr.read().decode()

    cpp_process.stdout.close()
    cpp_process.stderr.close()
    
    # Wait for the C++ application to finish
    cpp_process.wait()
    
    print("output: ", output, "\n")
    print("Errors for debugging: ", errors, "\n")


def interact_cpp_dev_menu (dev_menu_response):

    compile_cpp_command = ["g++", MAIN_CPP_FILE, SQLITE3_OBJECT_FILE_PATH, "-o", CPP_EXECUTABLE_FROM_PYTHON_PATH] #original
    subprocess.run(compile_cpp_command, check=True)
    
    # Run the C++ application as a subprocess
    cpp_process = subprocess.Popen([CPP_EXECUTABLE_FROM_PYTHON_PATH], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    # this request variable below communicates with cpp menu on what function to run
    request = '1'
    
    dev_menu_response = str(dev_menu_response)
    
    # Send inputs to the C++ application
    inputs = [
        request, "\n",
        dev_menu_response, "\n"
    ]
    
    for input_data in inputs:
        cpp_process.stdin.write(input_data.encode())

    cpp_process.stdin.close()

    # Read the output and error streams from the C++ application
    output = cpp_process.stdout.read().decode()
    errors = cpp_process.stderr.read().decode()

    cpp_process.stdout.close()
    cpp_process.stderr.close()

    # Wait for the C++ application to finish
    cpp_process.wait()
    
    print("output: ", output, "\n")
    print("Errors for debugging: ", errors, "\n")


def generate_data (num_data_to_generate):
        
    fake = Faker()

    loan_data_header = ['Name', "credit score", 'monthly income', 'financial reserves', 'debt to income ratio', 'Duration in months', 'loan amount requested']
    loan_data = []
    
    valid_inputs = False
    
    while (valid_inputs == False):
        
        
        
        min_options = 0
        max_options = 20000000
        
        valid_inputs = validate_string_input_for_num_value(num_data_to_generate, max_options, min_options)
        
        if (valid_inputs is False):
            print(" Data entered is in invalid format. \n")

    num_data_to_generate = int(num_data_to_generate)

    # Generate user data
    for i in range(num_data_to_generate):
        credit_score = random.randint(300, 850)
        user_name = fake.name()
        user_monthly_income = round(random.uniform(900, 12000), 2)
        user_debt_to_income_ratio = round(random.uniform(0.00, 1.00), 2)
        financial_reserves = round(random.uniform(500.00, 200000.00), 2)
        loan_duration_in_months = random.randint(2, 240)
        loan_amonut_requested = random.randint(500, 200000)
            
        loan_data.append([user_name, credit_score, user_monthly_income, financial_reserves, user_debt_to_income_ratio, loan_duration_in_months, loan_amonut_requested])
        
    if os.path.exists("allGeneratedLoanData.csv"):
        with open("allGeneratedLoanData.csv", "a", newline = '') as file:
            writer = csv.writer(file)
            writer.writerows(loan_data)    
    else:
        with open("allGeneratedLoanData.csv", "w", newline = '') as file:
            writer = csv.writer(file)
            writer.writerow(loan_data_header)
            writer.writerows(loan_data)
    
    with open("tempGeneratedLoanDataForDbStorage.csv", "w", newline = '') as file:  # This is used to store newly generated data to be used
        writer = csv.writer(file)
        writer.writerow(loan_data_header)
        writer.writerows(loan_data)
    
    # print(" Loan data has been written successfully.")


def menu_to_search_for_loan_from_server():
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
    
    if (user_response == 1):
        user_has_loan_id = True
        loan_id = input("Enter Loan ID: ")
        
    elif (user_response == 2):
        user_has_loan_id = False
        loan_id = None
        
    search_menu_response_data = {"user_has_loan_id" : user_has_loan_id, 
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
   
        
def search_for_loan_data_given_loan_id(single_loan_detils):
    loan_id = input("Enter Loan ID: ")

    try:
        # Connect to the SQLite database
        conn = sqlite3.connect(SQLITE3_DATABASE_PATH)
        cursor = conn.cursor()

        # Replace 'your_table' with the name of your table and 'primary_key_column' with the name of the primary key column
        cursor.execute("SELECT * FROM users WHERE Loan_id = ?", (loan_id,))

        # Fetch the result (should be a single row if primary key is unique)
        row = cursor.fetchone()

        # If the row is not None, print or process the data
        if row:
            print("Row found:")
            print(row, "\n")
            (loan_id, user_name, credit_score, monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rates, yearly_interst_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_payments_to_satisfy_loan, default_risk_score, loan_viability_score, adjusted_loan_viability_score) = row
            # print(loan_id, user_name, credit_score, monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rates, yearly_interst_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_payments_to_satisfy_loan, default_risk_score, loan_viability_score, adjusted_loan_viability_score)
            
            single_loan_detils = Loan(loan_id, user_name, credit_score, monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rates, yearly_interst_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_payments_to_satisfy_loan, default_risk_score, loan_viability_score, adjusted_loan_viability_score)
            single_loan_detils.display_loan_data_to_console()
        else:
            print("Row not found.")
    except sqlite3.Error as e:
        print("Error:", e)
    finally:
        # Close the cursor and the connection
        cursor.close()
        conn.close()
        
        return single_loan_detils
    
    
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
            (loan_id, user_name, credit_score, monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rates, yearly_interst_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_payments_to_satisfy_loan, default_risk_score, loan_viability_score, adjusted_loan_viability_score) = row
            # print(loan_id, user_name, credit_score, monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rates, yearly_interst_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_payments_to_satisfy_loan, default_risk_score, loan_viability_score, adjusted_loan_viability_score)
            
            retrieved_user_data = {
                "loan_id" : loan_id,
                "user_name" : user_name,
                "credit_score" : credit_score,
                "monthly_income" : monthly_income,
                "financial_reserves" : financial_reserves,
                "debt_to_income_ratio" : debt_to_income_ratio,
                "loan_duration_left" : loan_duration,
                "requested_loan_amount" : requested_loan_amount,
                "monthly_interest_rates" : monthly_interest_rates,
                "yearly_interst_rate" : yearly_interst_rate
                
                # "loss_given_default" : loss_given_default,
                # "recovery_rate" : recovery_rate,
                # "outstanding_monthly_debt_payments_to_satisfy_loan" : outstanding_monthly_debt_payments_to_satisfy_loan,
                # "default_risk_score" : default_risk_score,
                # "loan_viability_score" : loan_viability_score,
                # "adjusted_loan_viability_score" : adjusted_loan_viability_score
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


def search_for_loan_data_without_loan_id(loan_objects):
    user_first_name = input("Enter your first name: ")
    user_last_name = input("Enter your last name: ")
    user_name = user_first_name + " " + user_last_name
    print(" This is name: ", user_name, " \n")

    try:
        # Connect to the SQLite database
        conn = sqlite3.connect(SQLITE3_DATABASE_PATH)
        cursor = conn.cursor()

        # Replace 'your_table' with the name of your table and 'primary_key_column' with the name of the primary key column
        cursor.execute("SELECT * FROM users WHERE name = ?", (user_name,))

        # Fetch the result (should be a single row if primary key is unique)
        rows = cursor.fetchall()
        
        # If the row is not None, print or process the data
        if rows:
            print("Data found:")
            # print(rows, "\n")
            num_rows = len(rows)
            # print("Num rows = ", num_rows)
            
            for i in range(0, num_rows):
                temp_tuple_list = rows[i:(i+1)];
                temp_tuple = temp_tuple_list[0]
                # print(temp_tuple_list, "\n")
                # print(len(temp_tuple_list))
                (loan_id, user_name, credit_score, monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rates, yearly_interst_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_payments_to_satisfy_loan, default_risk_score, loan_viability_score, adjusted_loan_viability_score) = temp_tuple
                # print(loan_id, user_name, credit_score, monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rates, yearly_interst_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_payments_to_satisfy_loan, default_risk_score, loan_viability_score, adjusted_loan_viability_score)
            
                loan_id_for_objects = loan_id
                
                loan_id_for_objects = Loan(loan_id, user_name, credit_score, monthly_income, financial_reserves, debt_to_income_ratio, loan_duration, requested_loan_amount, monthly_interest_rates, yearly_interst_rate, loss_given_default, recovery_rate, outstanding_monthly_debt_payments_to_satisfy_loan, default_risk_score, loan_viability_score, adjusted_loan_viability_score)
                loan_id_for_objects.display_loan_data_to_console() #Fix this we need each loan objec to be unique and stord on a list
                
                loan_objects.append(loan_id_for_objects)
                
                
                # temp_tuple_list.clear()
                
        else:
            print("Row not found.")
    except sqlite3.Error as e:
        print("Error:", e)
    finally:
        # Close the cursor and the connection
        cursor.close()
        conn.close()
        
        
def compile_cpp_alone():
    try:
        # Compile the C++ program with sqlite object file (if needed) mostly for debugging
        compile_cpp_command = ["g++", MAIN_CPP_FILE, SQLITE3_OBJECT_FILE_PATH, "-o", STAND_ALONE_CPP_EXECUTABLE] 
        subprocess.run(compile_cpp_command, check=True)
    except:
        print(" Error compiling program. \n")
        
        
def run_program_using_dll():
    compile_commands = "g++ -fPIC -shared -o"
    
    complete_command_instruction = compile_commands + " " + OUTPUT_DLL_FILE_PATH + " " + LIBRARY_CPP_FILE_PATH + " " + SQLITE3_OBJECT_FILE_PATH
    subprocess.run(complete_command_instruction, check=True)
    
    cppLibrary = ctypes.CDLL(OUTPUT_DLL_FILE_PATH)
    initialMenuResponse = cppLibrary.setInitialMenuResponse()
    
    if (initialMenuResponse == 1):
        devMenuResponse = cppLibrary.showDevMenuFromCpp()
    else:
        devMenuResponse = 0
        
    
    if (devMenuResponse == 1):
        generate_data()
            
    cppLibrary.getValuesFromPython(initialMenuResponse, devMenuResponse)
    
    
def compile_dll_for_server():
    compile_commands = "g++ -fPIC -shared -o"
    
    complete_command_instruction = compile_commands + " " + OUTPUT_DLL_FILE_FOR_SERVER_PATH + " " + LIBRARY_CPP_FILE_PATH_FOR_SERVER + " " + SQLITE3_OBJECT_FILE_PATH
    subprocess.run(complete_command_instruction, check=True)
    
    
def display_single_retreved_data(retrieved_user_data):
    print("Loan id: ", retrieved_user_data['loan_id'])
    print("Your Fullname: ", retrieved_user_data['user_name'])
    print("Your Credit Score: ", retrieved_user_data['credit_score'])
    print("Your Stated Monhtly Income: $", retrieved_user_data['monthly_income'])
    print("Your stated Financial Reserves Valuation: $", retrieved_user_data['financial_reserves'])
    print("Your provided debt to income ratio:", retrieved_user_data['debt_to_income_ratio'])
    print("Your requested Loan Duration is", retrieved_user_data['loan_duration_left'], "months")
    print("Your requested Loan Amount: $", retrieved_user_data['requested_loan_amount'])
    print("Your monthly interest rate:", retrieved_user_data['monthly_interest_rate'], "%")
    print("Your Monthly Interest over a year:", retrieved_user_data['yearly_interst_rate'], "% \n")
 

def dev_menu_response(instructions, operation_state):
    if (instructions["dev_menu_response"] == 1):
        if (operation_state["error_opening_file_to_store_generated_data"] is False):
            print(Fore.Green + " Generated Data Successfully")
        else:
            print(Fore.RED + " Failed to generate data.")
        # instructions["num_data_to_generate"] = num_data_to_generate
    elif (instructions["dev_menu_response"] == 2):
        if (instructions["error_opening_file_to_store_analyzed_data"] is False):
                print(Fore.Green + " Analyzed Data Successfully")
        else:
            print(Fore.RED + " Failed to analyze data.")
                
    elif (instructions["dev_menu_response"] == 3):
        
        if (operation_state["error_getting_data_from_db_to_analyxe"] is False):
                print(Fore.Green + " Analyzed Data Successfully")
        else:
            print(Fore.RED + " Failed to analyze data.")
    
    
def use_cpp_from_server(recieved_data, cpp_library):
    user_data = recieved_data["customer_data"]
    recieved_instructions = recieved_data["instructions"]
    
    operation_state_to_return = {
        "added_user_data_successfully" : False,
        "error_opening_file_to_store_generated_data" : False,
        "successful_search" : False,
        "found_user_data" : False,
        "error_searching_db" : False,
        "sqlite_error_value" : None,
        "error_opening_file_to_store_analyzed_data" : False,
        "error_getting_data_from_db_to_analyxe" : False
    }
    
    retrieved_user_data_to_return = {
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
    
    
    # print(user_data)
    print(" On cpp server side")
    
    # print(f" User Monthly income type = {type(user_data['user_monthly_income'])}")
    
    menu_response = recieved_instructions["menu_response"]
    dev_menu_response= recieved_instructions["dev_menu_response"]
    search_menu_response = recieved_instructions["search_menu_response"]
    
    if (menu_response == 1): # Add individualized loan using data
        print(" In server backend")
        print(f" Thi is user data before db {user_data['user_name']}")
        
        data_to_cpp = UserData(user_data['user_name'].encode(FORMAT), int(user_data['user_credit_score']), float(user_data['user_monthly_income']), float(user_data['user_financial_reserves']), 
                    float(user_data['user_debt_to_income_ratio']), float(user_data['user_loan_amoumnt_requested']), int(user_data['user_loan_duration']))
        
        cpp_library.addIndividualizedDataToDb(data_to_cpp)
        
        operation_state_to_return["added_user_data_successfully"] = True    # Edit to add validation to the cppLibrary  function above
        
        
    elif (menu_response == 2):
        
        if (user_data["user_has_loan_id"] == True):
            search_for_loan_operation_state, recovered_db_data = search_for_loan_data_given_loan_id_from_server(int(user_data["user_loan_id"]))
            # print(f"recovered data = {recovered_db_data}")
            
            retrieved_user_data_to_return.update(recovered_db_data)
            operation_state_to_return.update(search_for_loan_operation_state)
        else:
            pass
            # search_for_loan_data_given_loan_id_from_server(user["user_loan_id"])
            
    elif (menu_response == 3):
    
        if (recieved_instructions["generate_data_for_db"] == True):
            generate_data(recieved_instructions["num_data_to_generate"])
            operation_state_to_return["error_opening_file_to_store_generated_data"] = cpp_library.readAndStoreGeneratedDataInDb(recieved_instructions["dev_menu_response"])
            
        elif (dev_menu_response == 2):
            recieved_instructions["perform_data_analysis_on_all_generated_csv_data"] = True
            operation_state_to_return["error_opening_file_to_store_analyzed_data"] = cpp_library.readAndStoreGeneratedDataForAnalysis(recieved_instructions["dev_menu_response"])
        elif (dev_menu_response == 3):
            # recieved_instructions["store_all_db_data_for_external_analysis"] = True
            operation_state_to_return["error_getting_data_from_db_to_analyxe"] = True # Place holder for cpp program baseed response
            
            
    data_to_send_Back_to_client = {
        "operation_state_to_return" : operation_state_to_return,
        "retrieved_user_data_to_return" : retrieved_user_data_to_return
    }
    

        
    print("Done")
    return data_to_send_Back_to_client
    