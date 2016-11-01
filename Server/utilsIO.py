import sys, getopt

#These are functions related to handling command-line and keyboard input

def get_arg(args, pos):
    """Get a specific command line argument

    :param args: Command line arguments
    :param pos: The position in the array of arguments
    :return: The argument specified in pos cast as an int


    Purpose: This is used to get the port number from the command line
    """
    try:
        assert (len(sys.argv) == 2), "Argument length must be 2"
        assert (pos == 1), "PORT must be argument 2"
    except AssertionError, Argument:
        print "Invalid Argument length\n", Argument
    else:
        return int(args[pos])


def parse_cmdline():
    """This parses the the command line arguments

    :return: The command line arguments

    Purpose: read and return arguments from command line
    """
    try:
        opts, args = getopt.getopt(sys.argv, "", ["port="])
    except getopt.GetoptError:
        print 'server.py <PORT>'
        sys.exit(2)
    else:
        return args


def input_handler(prompt):
    """Provides a prompt for input, returns input

    :param prompt: The prompt to display
    :return: User input

    Purpose: To provide a reusable way to provide a prompt and read input
    """
    s = raw_input(prompt)
    return s


def signal_handler(signal, frame):
    """Shutdown program on CTRL-C

    :param signal: Signal Number
    :param frame: Current Stack Frame
    :return: Print Message, Exit Program
    """
    print('You Pressed Ctrl+C, shutting down server\n')
    sys.exit(0)



