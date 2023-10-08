import os
import json
import ctypes
from pathlib import Path
from header_file_for_testing_dll import test_changing_base_rate



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



        