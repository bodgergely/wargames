import sys

def add_carriage_returns(lines):
    lines = [l[:-1] + '\r\n' for l in lines]
    return "".join(lines[:-1])         # we need to exclude the last \r\n as that is redundant


if __name__ == '__main__':
    inputfile = sys.argv[1]
    lines = []
    with open(inputfile, 'r') as f:
        lines = f.readlines()
    output = add_carriage_returns(lines)
    sys.stdout.write(output)
