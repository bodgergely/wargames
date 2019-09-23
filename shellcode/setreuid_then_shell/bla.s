.intel_syntax noprefix

.global _start

_start:
push 	ebp
mov 	ebp, esp
sub 	esp, 0x10

mov 	eax, 72
mov 	ecx, 0
loop:
mov 	dword ptr [esp], eax
inc 	eax
inc 	ecx
cmp 	ecx, 8
jnz		loop

push 	esp
call 	printf

mov 	esp, ebp
pop 	ebp
ret



