#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void _start();

int main(int argc, char * argv[]){
    char buf[128];

//    printf("main at: %p, _start at: %p\n", main, _start);
//    printf("SP: %p = 0x%08x\n", buf, *(unsigned int*)buf);
//    printf("buf + 128 is at %p\n", buf + 128);
//    argc = 8;
//    for(argc=4;argc>=-13;argc--) {
//        printf("[%p]: 0x%08x\n", buf + 128 + argc * 4, *(unsigned int*)(buf + 128 + argc * 4));
//    }
//    printf("\n");
//    argc = 1; 
    if(argc == 1){
        printf("Usage: %s argument\n", argv[0]);
        exit(1);
    }
    strcpy(buf,argv[1]);
    printf("%s", buf);

    return 0;
}
