#include <stdio.h>

unsigned foo()
{
    unsigned esp; 
    __asm__
    (
        ".intel_syntax;"
        "mov %0, %%esp;"
        ".att_syntax;"
        : "=r"(esp)
        :
        : "esp"
    ); 
    
    printf("esp: 0x%x\n", esp);
    return esp;
}

int main(int argc, char* argv[])
{
    foo();
    return 0;
}

