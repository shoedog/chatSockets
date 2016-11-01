from utilsIO import input_handler


def message_handler(client_socket, local_handle, client_handle):
    """Handles Recieving and Responding to Messages

    :param client_socket: The external client socket that is connected
    :param local_handle: The Handle of the local server
    :param client_handle: The Handle of the external client
    :return: False if Connection closed by either side, True if Connection remains open

    Purpose: Wraps handlers for recieving and responding to messages and returns
        connection status to caller
    """
    if receipt_handler(client_socket, client_handle) == 0:
        return False
    elif response_handler(client_socket, local_handle, client_handle) == 0:
        return False
    else:
        return True


def response_handler(client_socket, handle, client_handle):
    """Handles creating and sending outgoing messages

    :param client_socket: The socket to send to
    :param handle: The server handle to send with the message
    :param client_handle: Client handle to print if connection is terminated
    :return: 0 if server receives disconnect input

    Purpose: Prompts for input and sends to client, terminates connection on
        input command and returns 0 if disconnected
    """
    response = raw_input(">")
    response = handle + ": " + response
    client_socket.send(response)
    if "\quit" in response:
        client_socket.close()
        print "Connection to %s terminated" % client_handle
        return 0


def receipt_handler(client_socket, client_handle):
    """Handles receiving message from connected socket and closing socket

    :param client_socket: External socket connected with
    :param client_handle: Handle of client to output with message
    :return: 0 if message contains disconnect command

    Purpose: Receives external message, strips newline, closing socket on
        disconnect message and returns 0, otherwise prints message
    """
    message = client_socket.recv(1024)
    message = message.rstrip('\n')
    if "\quit" in message:
        client_socket.close()
        print "%s left the chat." % client_handle
        return 0
    else:
        print client_handle + ': ' + message


def get_message(client_socket):
    """Handles receiving message from connected socket

    :param client_socket: External connected socket
    :return: Data received from external socket
    """
    data = client_socket.recv(1024)
    data = data.rstrip('\n')
    #print "data from client: %s" % data
    return data
