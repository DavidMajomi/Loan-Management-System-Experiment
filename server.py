import json
import ctypes
import socket
import threading
from pathlib import Path
from header_file_for_server_and_cli import use_cpp_from_server, compile_dll_with_make, get_prime_rate_with_alpha_vantage_api, change_base_rate_for_server

PATH = str(Path.cwd())

DEBUGGING = True
COMPILE_FOR_DEBUGGING = DEBUGGING

# Network related constants
HEADER = 64
PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)
DISCONNECT_MESSAGE = "!!!DISCONNECT"
FORMAT = 'utf-8'

OUTPUT_DLL_FILE_FOR_SERVER_PATH = PATH + "\\loanManagementServerLibrary.dll"

DEFAULT_BASE_RATE = 2

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)

def handle_client(conn, addr, cpp_library):
    
    print(f"New Conection {addr} connected")
    
    connected = True
    
    while connected:
        msg_length = conn.recv(HEADER).decode(FORMAT)
        if msg_length:
            msg_length = int(msg_length)
            msg = conn.recv(msg_length).decode(FORMAT)
            
            if msg == DISCONNECT_MESSAGE:
                conn.send(" Disconnected Successfully".encode(FORMAT))
                connected = False
                print("\n")
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
    
    change_base_rate, this_months_prime_rate = get_prime_rate_with_alpha_vantage_api()
    
    if COMPILE_FOR_DEBUGGING is True:
        compile_dll_with_make()
        
        
    cpp_library = ctypes.CDLL(OUTPUT_DLL_FILE_FOR_SERVER_PATH, winmode = 0)
    
    if (change_base_rate == True):
        change_base_rate_for_server(cpp_library, this_months_prime_rate)
    else:
        del this_months_prime_rate    
        change_base_rate_for_server(cpp_library, DEFAULT_BASE_RATE)
    
    
    server.listen()
    print(f"Server is listening on {SERVER}")
    
    
    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target = handle_client, args = (conn, addr, cpp_library))
        thread.start()
        
        print(f"Number of Connections: {threading.active_count() - 1} \n")


print("Starting Server...... \n")
start()
