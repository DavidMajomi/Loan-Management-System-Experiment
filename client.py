import socket
import json
from header_file import menu_for_server_client, get_customer_data_from_cli_for_server, display_dev_menu_for_server_client, menu_to_search_for_loan_from_server


HEADER = 64
PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)
DISCONNECT_MESSAGE = "!!!DISCONNECT"
FORMAT = 'utf-8'


client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(ADDR)
print(ADDR)

def send(msg):
    message = msg.encode(FORMAT)
    msg_length = len(message)
    send_lengh = str(msg_length).encode(FORMAT)
    send_lengh += b' ' * (HEADER - len(send_lengh))    
    
    client.send(send_lengh)
    client.send(message)
    print(client.recv(2048).decode(FORMAT))
    
    
def get_customer_data_from_cli():
    # Instrucions
    menu_response = None
    dev_menu_response = None
    search_menu_response = None
    generate_data_for_db = False
    num_data_to_generate = None
    perform_data_analysis_on_all_generated_csv_data = False
    store_all_db_data_for_external_analysis = False
    
    
    
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
    
    if (menu_response != 1):
        pass
        # temp_user_data_when_no_cli = no_cli_data_for_server(customer_data)
        # customer_data = customer_data | temp_user_data_when_no_cli
        
        
    data_to_send = {
        "customer_data" : customer_data,
        "instructions" : instructions
    }
        

    print(data_to_send)
    
    return data_to_send


data_to_send = get_customer_data_from_cli()

json_data = json.dumps(data_to_send)

print(json_data)

# # print("After function call")
# # print(customer_data)

send(json_data)
send(DISCONNECT_MESSAGE)