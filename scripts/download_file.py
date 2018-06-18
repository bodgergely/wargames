
from pwn import *
import sys
import argparse

def parse_args():
    parser = argparse.ArgumentParser(prog='download_file',description="Download file from ssh server")
    parser.add_argument('-s', '--server',required=True)
    parser.add_argument('-p', '--port',required=True, type=int)
    parser.add_argument('-u', '--user', required=True)
    parser.add_argument('--password', required=True)
    parser.add_argument('-f', '--file', required=True)
    parser.add_argument('-l', '--local', required=True)
    return vars(parser.parse_args())



if __name__ == "__main__":
    pargs = parse_args()
    shell = ssh(pargs['user'], pargs['server'], password=pargs['password'], port=pargs['port'])
    shell.download_file(pargs['file'], pargs['local'])
