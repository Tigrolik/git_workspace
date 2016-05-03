from socket import *

serverName = 'localhost'
serverPort = 12000

# create TCP socket for server, remote port 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
msg = raw_input('Input lowercase sentence: ')

# no need to attach server name, port
clientSocket.send(msg)
newMsg = clientSocket.recv(1024)
print 'From Server:',newMsg

clientSocket.close()
