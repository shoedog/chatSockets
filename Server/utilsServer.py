import socket
from utilsMsg import message_handler, get_message


# Get local host name and ip-address
def get_machine_info():
    """Prints IP Address and Host Name to Console

    :return: IP Address

    Purpose: To let the user know the IP Address and Host for creating connections
        where the IP address and host name may vary
    """
    host_name = socket.gethostname()
    ip_address = socket.gethostbyname(host_name)
    print "\t** Current IP: %s **\n\t** Current Host: %s **" % (ip_address, host_name)
    # DEV NOTE: flip3.engr.oregonstate.edu = 128.193.36.41
    return ip_address


def server_listen(s, server_handle):
    """Listens for incoming connections

    :param s: Socket to listen on
    :param server_handle: Server name
    :return: null

    Purpose: Listens on socket for connection, on receiving connection passes
        control to handle_connection method, until connection terminates
    """
    while 1:
        print "\nServer is ready to receive\n"
        conn_socket, address = s.accept()
        handle_connection(conn_socket, address, server_handle)


def handle_connection(conn_socket, remote_host, server_handle):
    """Handles establishing incoming connections including messages

    :param conn_socket: External connected socket
    :param remote_host: Remote connected address
    :param server_handle: Server name
    :return: null

    Purpose: Prints and sends establishment messages on successful connection,
        passes control for messages to message_handler while connected.
    """
    try:
        print "Connection from: %s" % socket.gethostbyname(remote_host[0])
        client_handle = get_message(conn_socket)
        conn_socket.send("Connection Established to: " + server_handle)
        connected = True
        print "Connection established: %s" % client_handle
        while connected:
            connected = message_handler(conn_socket, server_handle, client_handle)
    except socket.error, err_msg:
        print "%s: %s" % (remote_host, err_msg)


def open_socket(host, port):
    """Opens and binds a socket for TCP connections

    :param host: Host address to bind socket
    :param port: Host port to bind socket
    :return: TCP Socket, bound to host and port, open for listening

    Purpose: Initialize socket for listening for incoming connections
    """
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((host, port))
    s.listen(1)
    return s
