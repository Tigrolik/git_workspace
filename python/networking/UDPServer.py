# include Python's socket library
from socket import *

serverPort = 12000

# create UDP socket
serverSocket = socket(AF_INET, SOCK_DGRAM)

# bind socket to local port
serverSocket.bind(('', serverPort))
print "The server is ready to receive..."

while 1:
	# read from UDP socket into message, getting client's
	# address (client IP and port)
	msg, clientAddress = serverSocket.recvfrom(2048)
	newMsg = msg.upper()
	# send upper case string back to the client
	serverSocket.sendto(newMsg, clientAddress)
