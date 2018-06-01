#!/usr/bin/python3
import sys
import os
import tempfile


def parse(objdump, tmpdir):
    lines = []
    for line in open(objdump, "r"):
        lines.append(line)
    lines = lines[7:]
    opcodes = []
    for line in lines:
        opcodes+=line.split("\t")[1].strip().split(' ')
    shellcode = r"\x".join(opcodes)
    shellcode = "\\x" + shellcode
    output = open(f"{tmpdir}/" + "shellcode", "w")
    output.flush()
    output.close()
    print(shellcode)

def main():
    if len(sys.argv) < 2:
            print("Usage: " + sys.argv[0] + " <code.s>")
            return
    tmpdir = tempfile.mkdtemp()
    print("# Created temp dir: " + tmpdir)
    inf = sys.argv[1]
    objf = os.path.basename(inf)[:-2] + '.o'
    os.system(f"gcc -m32 -c {inf} -o {tmpdir}/{objf}")
    os.system(f"objdump -M intel -d {tmpdir}/{objf} > {tmpdir}/" + "objdump")

    parse(f"{tmpdir}/" + "objdump", tmpdir)

if __name__ == "__main__":
    main() 
