import socket
import sys

if len(sys.argv) < 2:
    print("Please pass port number as command line argument 1")
    exit(0)

print("argument 1 is ", sys.argv[1])
serverHost = 'localhost' #is this right?
serverPort = int(sys.argv[1])

While True:
	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as serverSocket: 
	    serverSocket.bind((serverHost, serverPort))
	    serverSocket.listen()
	    conn, addr = serverSocket.accept()
	    with conn:
	        print('Connected by', addr)
		isDone = 0
	        while !isDone:
	            data = conn.recv(2048)
	            #print(data)
	            if not data:
	                break
	            print('client: ' + data.decode("utf-8"))
	            reply = input('>')
	            conn.sendall(reply.encode("utf-8"))
	
