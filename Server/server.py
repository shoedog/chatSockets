from utilsIO import *
from utilsServer import *


def main():
    port = get_arg(parse_cmdline(), 1)
    server_handle = input_handler("Input Handle: ")
    server_socket = server_create(port)
    server_listen(server_socket, server_handle)


main()
