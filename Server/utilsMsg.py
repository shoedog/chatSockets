from utilsIO import input_handler


def message_handler(client_socket, local_handle, client_handle):
    if receipt_handler(client_socket, client_handle) == 0:
        client_socket.close()
        return False
    elif response_handler(client_socket, local_handle, client_handle) == 0:
        return False
    else:
        return True


def response_handler(client_socket, handle, client_handle):
    response = input_handler(">")
    response = handle + ": " + response
    client_socket.send(response)
    if "\quit" in response:
        print "Connection to %s terminated" % client_handle
        client_socket.close()
        return 0


def receipt_handler(client_socket, client_handle):
    message = client_socket.recv(1024)
    if "\quit" in message:
        print "%s left the chat." % client_handle
        return 0
    else:
        print message


def get_message(client_socket):
    data = client_socket.recv(1024)
    return data