.intel_syntax noprefix

#https://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linu://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linux 

.global jozsi_setreuid

jozsi_setreuid:
mov eax, 70
mov ebx, 1001
mov ecx, 1001
int  0x80
