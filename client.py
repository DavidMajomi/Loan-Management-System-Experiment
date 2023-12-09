import socket
import json
from colorama import Fore
from header_file_for_server_and_cli import menu_for_server_client, get_customer_data_from_cli_for_server, display_dev_menu_for_server_client, menu_to_search_for_loan_from_server
from header_file_for_server_and_cli import display_single_retrieved_data, dev_menu_response, display_multiple_retrieved_data
# from header_file_for_server_and_cliz display_single_retrieved_data, dev_menu_response, display_multiple_retrieved_data

HEADER = 64
PORT = 5056
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)
DISCONNECT_MESSAGE = "!!!DISCONNECT"
RECOMPILE_DLL_FILE = "RECOMPILE_CPP"
FORMAT = 'utf-8'


client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(ADDR)
print(ADDR)

def send(msg, instructions):
    message = msg.encode(FORMAT)
    msg_length = len(message)
    send_length = str(msg_length).encode(FORMAT)
    send_length += b' ' * (HEADER - len(send_length))    
    
    client.send(send_length)
    client.send(message)
    
    if (msg != DISCONNECT_MESSAGE):
        recieve_data_length = int(client.recv(2048).decode(FORMAT))
        
        recieved_json_data = client.recv(recieve_data_length).decode(FORMAT)
        # print(recieved_json_data)
        
        recieved_data = json.loads(recieved_json_data)
        
        operation_state = recieved_data["operation_state_to_return"]
        retrieved_user_data = recieved_data["retrieved_user_data_to_return"]
        list_of_retrieved_user_data = recieved_data["list_of_retrieved_user_data"]
        
        if (instructions["menu_response"] == 1):
            if (operation_state["added_user_data_successfully"]) == True:
                print("\n")
                print(Fore.GREEN + " Loan data added successfully")
            else:
                print(Fore.RED + " Loan data could not be added")
                
                
        elif (instructions["menu_response"] == 2):
            if (operation_state["successful_search"] is True):
                if (operation_state["found_user_data"] is True):
                    print(Fore.GREEN + " Retrieved data successfully \n")
                    
                    if (instructions["search_menu_response"] == 1):
                        display_single_retrieved_data(retrieved_user_data)
                        
                    elif(instructions["search_menu_response"] == 2):
                        display_multiple_retrieved_data(list_of_retrieved_user_data)
                        
                else:
                    print("\n")
                    print(Fore.RED + " User data not found \n")
                        
            else:
                print("\n")
                print(Fore.RED + " Error searchng for user data \n")
            
        elif (instructions["menu_response"] == 3):
            dev_menu_response(instructions, operation_state)

    else:
        recieved_disconnect_message = client.recv(2048).decode(FORMAT)
        print(" Disconnect Message Sent.")
        print(recieved_disconnect_message)
    
    
def get_customer_data_from_cli():
    # Instrucions
    menu_response = None
    dev_menu_response = None
    search_menu_response = None
    num_data_to_generate = None
    
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
    
    instructions = {
        "menu_response" : menu_response,
        "dev_menu_response" : dev_menu_response,
        "search_menu_response" : None,
        "generate_data_for_db" : False,
        "num_data_to_generate" : None,
        "perform_data_analysis_on_all_generated_csv_data" : False,
        "store_all_db_data_for_external_analysis" : False
    }

    menu_response = menu_for_server_client()


    if (menu_response == 1):
        menu_response_data = get_customer_data_from_cli_for_server()
        customer_data.update(menu_response_data)
        
    elif (menu_response == 2):
        search_menu_response, search_menu_response_data = menu_to_search_for_loan_from_server()
        customer_data.update(search_menu_response_data)
        
    elif (menu_response == 3):
        dev_menu_response, num_data_to_generate = display_dev_menu_for_server_client() ##
        
        if (dev_menu_response == 1):
            instructions["generate_data_for_db"] = True
            instructions["num_data_to_generate"] = num_data_to_generate
        elif (dev_menu_response == 2):
            instructions["perform_data_analysis_on_all_generated_csv_data"] = True
        elif (dev_menu_response == 3):
            instructions["store_all_db_data_for_external_analysis"] = True
    
    instructions['menu_response'] = menu_response  ##
    instructions['dev_menu_response'] = dev_menu_response  ##
    instructions['search_menu_response'] = search_menu_response    ##
        
    data_to_send = {
        "customer_data" : customer_data,
        "instructions" : instructions
    }
        

    # print(data_to_send)
    
    return data_to_send, instructions


data_to_send, instructions = get_customer_data_from_cli()

json_data = json.dumps(data_to_send)

send(json_data, instructions)
# send(RECOMPILE_DLL_FILE, instructions)
send(DISCONNECT_MESSAGE, instructions)