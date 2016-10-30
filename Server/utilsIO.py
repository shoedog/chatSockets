import sys, getopt


def get_arg(args, pos):
    try:
        assert (len(sys.argv) == 2), "Argument length must be 2"
        assert (pos == 1), "PORT must be argument 2"
    except AssertionError, Argument:
        print "Invalid Argument length\n", Argument
    else:
        return int(args[pos])


def parse_cmdline():
    try:
        opts, args = getopt.getopt(sys.argv, "", ["port="])
    except getopt.GetoptError:
        print 'server.py <PORT>'
        sys.exit(2)
    else:
        return args


def input_handler(prompt):
    s = raw_input(prompt)
    return s



