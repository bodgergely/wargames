#include <stdio.h>

int foo()
{
    int temp; 
    asm
    (
        ".intel_syntax;"
        "mov %%eax, %1;"
        "mov %0, %%eax;"
        ".att_syntax;"
        : "=r"(temp)
        : "r"(1)
        : "eax"
    ); 
    
    printf("temp: %d\n", temp);
    return temp;
}

int main(int argc, char* argv[])
{
    foo();
    return 0;
}

