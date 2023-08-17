# Activate virtual environment
# Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process 
# venv\scripts\activate

from header_file import *
from faker import Faker


menu_response = menu()

if (menu_response == 1):
    customer_data = {}
    customer_data = get_customer_data_from_cli_for_server(customer_data) #Resume here
    add_loan_using_the_cpp_program(customer_data)
    
elif (menu_response == 2):
    search_menu_response = menu_to_search_for_loan()
    
    if (search_menu_response == 1):
        single_loan_detils = None
        single_loan_detils = search_for_loan_data_given_loan_id(single_loan_detils)
        single_loan_detils.display_loan_data_to_console()
    else:
        loan_objects = []
        print(" This is place holder for search for loan data without loan id. ")
        search_for_loan_data_without_loan_id(loan_objects)
    
elif menu_response == 3:
    dev_menu_response = display_dev_menu()
    
    if (dev_menu_response == 1):
        generate_data ()
    elif (dev_menu_response == 2):
        interact_cpp_dev_menu (dev_menu_response)
    elif (dev_menu_response == 3):
        print(" This is analyze database values. \n")
    elif (dev_menu_response == 4):
        print(" This is compile cpp alone")
        compile_cpp_alone()
    # elif (dev_menu_response == 5):
    #     print(" This is place holder to compile c++ to dll. \n")
        
elif (menu_response == 4):
    run_program_using_dll()
        
        
# loan_objects[1].display_loan_data_to_console()