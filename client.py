import socket
import json
from header_file import menu_for_server_client, get_customer_data_from_cli_for_server, menu_to_search_for_loan, display_dev_menu


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
    
    
# send("Hello world")
# send("DBANJ 3 sdfghj")


def get_customer_data_from_cli():
    menu_response = 0
    dev_menu_response = 0
    search_menu_response = 0

    menu_response = menu_for_server_client()

    customer_data = {}
    customer_data = get_customer_data_from_cli_for_server(customer_data)

    if (menu_response == 1):
        pass
        
    elif (menu_response == 2):
        search_menu_response = menu_to_search_for_loan()
        
        
    elif menu_response == 3:
        dev_menu_response = display_dev_menu()
        
    customer_data['menu_response'] = menu_response
    customer_data['dev_menu_response'] = dev_menu_response
    customer_data['search_menu_response'] = search_menu_response

    print(customer_data)
    
    return customer_data


customer_data = get_customer_data_from_cli()


json_data = json.dumps(customer_data)

print("After function call")
print(customer_data)

send(json_data)
send(DISCONNECT_MESSAGE)