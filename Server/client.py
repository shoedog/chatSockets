import socket

from utilsIO import input_handler

from utilsMsg import message_handler

HOST = '128.193.36.41'    # The remote host
PORT = 5000              # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
handle = input_handler('Input Handle: ')
s.send(handle)

while 1:
    if 0 == message_handler(s, handle, 'server'):
        s.close()
        break

