#!/usr/bin/python2

"""
Example:

    binary_to_shellcode.py /bin/ls /tmp/lscopy

You can copy the content of the resulted shellcode to the clipboard using xclip
cat shellcode | cs

then

cat /tmp/lscopy | cs
echo -ne '\x34\xef...' > /tmp/executable
chmod u+x /tmp/executable

"""

import sys

def to_hex(num):
    h = hex(num)
    if len(h) == 3:
        return '\\x0' + h[2]
    else:
        return '\\' + h[1:]

def write_shellcode(code, outfile):
    buf = []
    for c in code:
        buf.append(to_hex(ord(c)))
    outfile.write("".join(buf))
        


def parse(input, output):
    with open(input, 'rb') as infile:
        with open(output, 'wb') as outfile:
            while True:
                arr = infile.read(4096)
                if len(arr) > 0:
                    write_shellcode(arr, outfile)
                else:
                    break
            outfile.flush()

def main():
    if len(sys.argv) < 3:
        print "Usage: ", __file__, " <source_file> <output_file>"
        return
    parse(sys.argv[1], sys.argv[2])


if __name__ == '__main__':
    main()

