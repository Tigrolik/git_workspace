# include Python's socket library
from socket import *

serverName = 'localhost'
serverPort = 12000

# create UPD socket for server
clientSocket = socket(AF_INET, SOCK_DGRAM)

msg = raw_input('Input lowercase sentence: ')

# attach server name, port to message, send into socket
clientSocket.sendto(msg, (serverName, serverPort))

# read reply characters from socket into string
newMsg, serverAddress = clientSocket.recvfrom(2048)

print newMsg

clientSocket.close()
