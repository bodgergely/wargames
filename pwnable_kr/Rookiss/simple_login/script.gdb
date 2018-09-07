source ~/pwndbg/gdbinit.py
set disassembly-flavor intel
set detach-on-fork off
set follow-fork-mode child
b main
b *0x8049397
b *0x8049407
b *0x8049240
run < input.txt
