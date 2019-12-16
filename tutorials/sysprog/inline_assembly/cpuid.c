#include <stdio.h>

unsigned cpuid(int eax)
{
    unsigned ebx = 0XDEADBEEF; 
    unsigned eaxr = 0XDEADBEEF; 
    asm
    (
        ".intel_syntax;"
        "xor %%ebx, %%ebx;"
        "xor %%ecx, %%ecx;"
        "xor %%edx, %%edx;"
        "mov %%eax, %1;"
        "cpuid;"
        "mov %0, %%ebx;"
        ".att_syntax;"
        : "=r"(ebx)
        : "r"(eax)
        : "eax", "ebx", "ecx", "edx"
    ); 
    
    printf("result: %X\n", ebx);
    printf("result: %X\n", eaxr);
    return ebx;
}

int main(int argc, char* argv[])
{
    cpuid(0x1);
    return 0;
}

