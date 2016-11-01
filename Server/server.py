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
