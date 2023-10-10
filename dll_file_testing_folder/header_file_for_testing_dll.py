import os
import csv
import ctypes
import random
from faker import Faker

FORMAT = 'utf-8'

class UserData(ctypes.Structure):
    _fields_ = [("user_name", ctypes.c_char_p),
                ("user_credit_score", ctypes.c_short),
                ("user_monthly_income", ctypes.c_double),
                ("user_financial_reserves", ctypes.c_double),
                ("user_debt_to_income_ratio", ctypes.c_double),
                ("user_loan_amoumnt_requested", ctypes.c_double),
                ("user_loan_duration", ctypes.c_int)]


def generate_data (num_data_to_generate):
        
    fake = Faker()

    loan_data_header = ['Name', "credit score", 'monthly income', 'financial reserves', 'debt to income ratio', 'Duration in months', 'loan amount requested']
    loan_data = []
    
    min_options = 0
    max_options = 10000
    
    if ((num_data_to_generate < min_options) or (num_data_to_generate > max_options)):
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
        
        print(" Loan data has been written successfully.")


def test_changing_base_rate(cpp_library):
    this_months_prime_rate_from_cpp = cpp_library.getThisMonthsPrimeRate
    this_months_prime_rate_from_cpp.restype = ctypes.c_double
    this_months_spread_from_cpp = cpp_library.getSpread
    this_months_spread_from_cpp.restype = ctypes.c_double
    
    
    this_months_federal_funds_rate_double = ctypes.c_double(6.00)
    this_months_federal_funds_rate = 6.00
        
    cpp_library.changeBaseRate(this_months_federal_funds_rate_double)
    
    if(this_months_prime_rate_from_cpp() == ((this_months_federal_funds_rate) + this_months_spread_from_cpp())):
        print(f" This months prime rate set successfully. This is its value: {this_months_spread_from_cpp()}")
    else:
        # test = cpp_library.getThisMonthsPrimeRate
        # test.restype = ctypes.c_double
        
        print(f" Not accurate, failed test. This months prime rate is: {this_months_prime_rate_from_cpp()}")
        print(f" This is this months spread {cpp_library.getSpread()}")


def test_adding_and_computing_for_single_user_data(customer_data, cpp_library):
    user_data = customer_data
    
    data_to_cpp = UserData(user_data['user_name'].encode(FORMAT), int(user_data['user_credit_score']), float(user_data['user_monthly_income']), float(user_data['user_financial_reserves']), 
        float(user_data['user_debt_to_income_ratio']), float(user_data['user_loan_amoumnt_requested']), int(user_data['user_loan_duration']))


def test_storing_all_db_values_in_csv_for_analysis(cpp_library):
    pass


def test_storing_generated_data_in_db_from_csv(cpp_library):
    print(" Test stroing generated data")
    required_dev_menu_response = 3
    
    generate_data(100)
    
    error_storing_generated_data = bool(cpp_library.readAndStoreGeneratedDataInDb(required_dev_menu_response))

    return error_storing_generated_data
    

def test_coputing_loan_related_values_from_generated_data_without_storing_data():
    pass