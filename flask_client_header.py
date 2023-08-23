import socket
import json

HEADER = 64
PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)
DISCONNECT_MESSAGE = "!!!DISCONNECT"
FORMAT = 'utf-8'

# client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# client.connect(ADDR)

def disconnect_from_server(client):
    
    message = DISCONNECT_MESSAGE.encode(FORMAT)
    msg_length = len(message)
    send_length = str(msg_length).encode(FORMAT)
    send_length += b' ' * (HEADER - len(send_length))    
    
    client.send(send_length)
    client.send(message)

    recieved_disconnect_message = client.recv(2048).decode(FORMAT)
    print(recieved_disconnect_message)


def send_data_to_server(msg, client):

    message = msg.encode(FORMAT)
    msg_length = len(message)
    send_length = str(msg_length).encode(FORMAT)
    send_length += b' ' * (HEADER - len(send_length))    
    
    client.send(send_length)
    client.send(message)
    
    # if (msg != DISCONNECT_MESSAGE):
    recieved_data = client.recv(2048).decode(FORMAT)
    
    recieved_data = json.loads(recieved_data)
    
    operation_state = recieved_data["operation_state_to_return"]
    retrieved_user_data = recieved_data["retrieved_user_data_to_return"]
        
        
    return  operation_state, retrieved_user_data
        
