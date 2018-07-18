
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv, char** envp)
{
    char tart[1024];
    char* buff = tart;
    memset(buff, 0 , sizeof(tart));
    *buff++ = 'H';
    *buff++ = 'e';
    *buff++ = 'l';
    printf("%c%c%c\n", tart[0], tart[1], tart[2]);
    *(buff+2) = 'v';
    if(!strcmp(buff, "\x00")) {
        printf("Good!\n");
    }
    unsigned int pid;
    pid = fork();
    int* c = malloc(4);
    *c = 5;
    if(!pid) {
        printf("I am child, pid: %u, ppid: %u, c: %d.\n", getpid(), getppid(), *c);
    }
    else {
        printf("I am parent! pid: %u, childpid: %u, c: %d\n", getpid(), pid, *c);
        wait(NULL);
    }
    return 0;
}
