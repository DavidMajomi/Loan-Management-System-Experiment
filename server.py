import json
import ctypes
import socket
import threading
from header_file import use_cpp_from_server, compile_dll_for_server
# from header_file import run_program_using_dll

COMPILE_FOR_DEBUGGING = True

HEADER = 64
PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)
DISCONNECT_MESSAGE = "!!!DISCONNECT"
FORMAT = 'utf-8'

OUTPUT_DLL_FILE_FOR_SERVER_PATH = "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\loanManagementSeverLibrary.dll"  

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
                connected = False
                # print("\n")
            else:
                data_to_send = json.loads(msg)
                use_cpp_from_server(data_to_send, cpp_library)
            
            print(f'[{addr}] {msg}')
            conn.send("Message Recieved".encode(FORMAT))
        
        
    conn.close()
        

def start():
    server.listen()
    print(f"Server is listening on {SERVER}")
    
    if COMPILE_FOR_DEBUGGING is True:
        compile_dll_for_server()
        
    cpp_library = ctypes.CDLL(OUTPUT_DLL_FILE_FOR_SERVER_PATH)
    
    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target = handle_client, args = (conn, addr, cpp_library))
        thread.start()
        
        print(f"Num Connections: {threading.active_count() - 1} \n")

print("Starting Server...... \n")
start()
