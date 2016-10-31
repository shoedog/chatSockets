from utilsIO import *
from utilsServer import *
import signal
import sys

def signal_handler(signal, frame):
    print('You Pressed Ctrl+C, shutting down server\n')
    sys.exit(0)

def main():
    signal.signal(signal.SIGINT, signal_handler)
    print ('\n\n\n\n\n\t***Welcome to the Chat Server***\n\n')
    print ('Press Ctrl-C to shut down server and exit.\n\n')
    port = get_arg(parse_cmdline(), 1)
    server_handle = input_handler("Input Handle: ")
    server_socket = server_create(port)
    server_listen(server_socket, server_handle)


main()
