import socket
from binascii import hexlify
from utilsMsg import message_handler, get_message


# Get local host name and ip-address
def get_machine_info():
    host_name = socket.gethostname()
    ip_address = socket.gethostbyname(host_name)
    return ip_address


def handle_connection(conn_socket, remote_host, server_handle):
    try:
        print "Connection from: %s" % socket.gethostbyname(remote_host[0])
        client_handle = get_message(conn_socket)
        conn_socket.send("Connection Established to: " + server_handle)
        connected = True
        print "Connection established: %s" % client_handle
        while connected:
            connected = message_handler(conn_socket, server_handle, client_handle)
    except socket.error, err_msg:
        print "%s: %s" %(remote_host, err_msg)


def open_socket(host, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((host, port))
    s.listen(1)
    return s


def server_create(port):
    host = get_machine_info()
    s = open_socket(host, port)
    return s


def server_listen(s, server_handle):
    connected = False
    while 1:
        print "Server is ready to receive"
        conn_socket, address = s.accept()
        handle_connection(conn_socket, address, server_handle)


def convert_ip4_addr(addr):
    for ip_addr in addr:
        packed_ip_addr = socket.inet_aton(ip_addr)
        unpacked_ip_addr = socket.inet_ntoa(packed_ip_addr)
        print "IP address: %s => packed: %s, unpacked: %s"\
         % (ip_addr, hexlify(packed_ip_addr), unpacked_ip_addr)
