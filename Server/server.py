# Author: Wesley Jinks
# Date: 10/30/2016
# Last Mod: 10/31/2016
# File Name: server.py
# Associated Required Files: utilsIO.py, utilsMsg.py, utilsServer.py
# Test Client: client.py
# Production Client: ../Client/client.c
#
# Overview: Chat Server to recieve and send messages with chat-server over TCP
#
# Input: Usage: python ./server.py <Port to Listen On>
#   handle: a 10 character string identifier
#   messages: a message to send to the client
#   disconnect: \quit
#
# Output: Prompts for input, server listening message, messages from client,
#   connection initialized and connection terminated messages
#
# References:
#   Python Docs Socket: https://docs.python.org/2/library/socket.html
#   Python Docs Built-In Functions: https://docs.python.org/2/library/functions.html
#   Python Docs signal: https://docs.python.org/2/library/signal.html
#
import signal
from utilsIO import *
from utilsServer import *


def main():
    """Handles Server Program

    Initializes Signal for CTRL-C to Exit
    Prints Welcome Message
    Gets Port Number from Command Line Argument
    Requests Handle Name Input for Server
    Initializes Server Socket on Port
    Listens on Port for Incoming Requests

    :return: NULL
    """
    signal.signal(signal.SIGINT, signal_handler)
    print ('\n\n\n\n\n\t***Welcome to the Chat Server***\n\n')
    print ('Press Ctrl-C to shut down server and exit.\n\n')
    port = get_arg(parse_cmdline(), 1)
    server_handle = input_handler("Input Handle: ")
    server_socket = open_socket(get_machine_info(), port)
    server_listen(server_socket, server_handle)


main()
