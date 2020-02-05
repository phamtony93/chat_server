import socket
import sys

if len(sys.argv) < 2:
    print("Please pass port number as command line argument 1")
    exit(0)

print("argument 1 is ", sys.argv[1])
serverHost = 'localhost' #is this right?
serverPort = int(sys.argv[1])

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as serverSocket: 
    serverSocket.bind((serverHost, serverPort))
    serverSocket.listen()
    conn, addr = serverSocket.accept()
    with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(2048)
            if not data:
                break
            conn.sendall(data)
# serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# serverSocket.bind(('', serverPort))
# print ("the server is ready to receive")
# while 1:
#     message, clientAddress = serverSocket.recvfrom(2048)
#     modifiedMessage = message.upper()
#     print (message)