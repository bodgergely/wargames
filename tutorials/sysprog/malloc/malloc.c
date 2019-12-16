#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PAGE_SIZE 4096

/*
   If mallocing 32 or greater page count mmap is used
   if less than 32 then brk
*/


int main(int argc, char *argv[])
{
    char* mem;
    printf("Stack is at: %p\n", &mem);
    printf("Code section (main) is at: %p\n", &main);
    sleep(3);
   
    int pc = 32;
    int pages = 0;
    for(int i=1;i<=20;i++) {
        if (i % 2)
            pc = 38;
        else
            pc = 31;
        mem = (char*)malloc(pc * PAGE_SIZE);
        printf("mem at: %p\n", mem);
        pages += pc;
        printf("Pages so far:%d\n", pages);
    }


    return 0;
}
