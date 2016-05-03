from socket import *

serverPort = 12000

# create TCP welcoming socket
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
# server begins listening for incoming TCP requests
serverSocket.listen(1)
print 'The server is ready to receive'

while 1:
	# server waits on accept() for incoming requests,
	# new socket created on return
	connSocket, addr = serverSocket.accept()
	# read bytes from socket (but not address as in UDP)
	msg = connSocket.recv(1024)
	newMsg = msg.upper()
	connSocket.send(newMsg)
	connSocket.close()

