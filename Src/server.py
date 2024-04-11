import json
import ctypes
import socket
import threading
from pathlib import Path
from header_file_for_server_and_cli import use_cpp_from_server, compile_dll_with_make, get_prime_rate_with_alpha_vantage_api, change_base_rate_for_server
from header_file_for_server_and_cli import validate_string_input_for_num_value

PATH = str(Path.cwd())

DEBUGGING = True
COMPILE_FOR_DEBUGGING = DEBUGGING

# Network related constants
HEADER = 64
PORT = 5056
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)
DISCONNECT_MESSAGE = "!!!DISCONNECT"
RECOMPILE_DLL_FILE = "RECOMPILE_CPP"
FORMAT = 'utf-8'

OUTPUT_DLL_FILE_FOR_SERVER_PATH = PATH + "\\loanManagementServerLibrary.dll"




DEFAULT_BASE_RATE = ctypes.c_double(5.33)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)

def handle_client(conn, addr, num_connections_to_server, use_api_for_economic_data):
    changed_base_rate_successfully = True
    
    
    print(f"New Conection {addr} connected")
    connected = True
    
    cpp_library = ctypes.CDLL(OUTPUT_DLL_FILE_FOR_SERVER_PATH, winmode = 0)
    
    # Set constant economic metrics for the day which is stored throughout the project
    if (num_connections_to_server == 1):
        
        if (use_api_for_economic_data is True):
            changed_base_rate_successfully, this_months_prime_rate = get_prime_rate_with_alpha_vantage_api()
            
            if (changed_base_rate_successfully == True):
                change_base_rate_for_server(cpp_library, this_months_prime_rate)
        else:
            pass
            # changed_base_rate_successfully, this_months_prime_rate = get_prime_rate_with_alpha_vantage_api()
            change_base_rate_for_server(cpp_library, DEFAULT_BASE_RATE)
        
            
    while connected:
        msg_length = conn.recv(HEADER).decode(FORMAT)
        if msg_length:
            msg_length = int(msg_length)
            msg = conn.recv(msg_length).decode(FORMAT)
            
            if msg == DISCONNECT_MESSAGE:
                conn.send(" Disconnected Successfully".encode(FORMAT))
                connected = False
                print("\n")
            # elif msg == RECOMPILE_DLL_FILE
                
            else:
                data_to_use = json.loads(msg)
                data_to_send_to_client = use_cpp_from_server(data_to_use, cpp_library)
                data_to_return = json.dumps(data_to_send_to_client, indent = 2)
                data_to_return_size = str(len(data_to_return.encode(FORMAT)))
                # print(data_to_return_size)
                # print(data_to_return)
                conn.send(data_to_return_size.encode(FORMAT))
                conn.send(data_to_return.encode(FORMAT))
                conn.send("Message Recieved".encode(FORMAT))
            
            # print(f'[{addr}] {msg}')
        
        
    conn.close()
        

def start():
    print("Setting up server...")
    
    if COMPILE_FOR_DEBUGGING is True:
        compile_dll_with_make()
        
    valid_inputs = False
    
    while(valid_inputs == False):
        user_menu_response = input("Do you want to make api calls to get economic values Enter 1 for yes or 0 for default economic values: ")
        print(f"This is your response: {user_menu_response}")
        
        max_options = 1
        min_options = 0
        
        valid_inputs = validate_string_input_for_num_value(user_menu_response, max_options, min_options)
        
        if (valid_inputs is False):
            print(" Data entered is in invalid format. \n")
        
    use_api_for_economic_data = bool(int(user_menu_response))
    
    print(f"This is a use api for economic data: {use_api_for_economic_data}")
    
    if (use_api_for_economic_data == True):
        print("You have chosen to use api for economic data")
    else:
        print("You have chosen to use default values for economic data")
        
        
    server.listen()
    print(f"Server is listening on {SERVER}")
    
    num_connections_to_server = 0
    while True:
        num_connections_to_server = num_connections_to_server + 1
        
        conn, addr = server.accept()
        thread = threading.Thread(target = handle_client, args = (conn, addr, num_connections_to_server, use_api_for_economic_data))
        thread.start()
        
        print(f"Number of Connections: {threading.active_count() - 1} \n")


print("Starting Server...... \n")
start()
    
