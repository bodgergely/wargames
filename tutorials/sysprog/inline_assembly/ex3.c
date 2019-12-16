#include <stdio.h>

unsigned foo(int a, int b, int c)
{
    unsigned sum; 
    asm
    (
        ".intel_syntax;"
        "mov %%eax, %1;"
        "mov %%ebx, %2;"
        "add %%eax, %%ebx;"
        "mov %%ebx, %3;"
        "add %%eax, %%ebx;"
        "mov %0, %%eax;"
        ".att_syntax;"
        : "=r"(sum)
        : "r"(a), "r"(b), "r"(c)
        : "eax", "ebx"
    ); 
    
    printf("sum: %d\n", sum);
    return sum;
}

int main(int argc, char* argv[])
{
    foo(3,4,5);
    return 0;
}

