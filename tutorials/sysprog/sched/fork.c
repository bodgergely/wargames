#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    if(pid = fork()) {
        // parent
        printf("(%u) created child: %u\n", getpid(), pid);
    }    
    else {
        // child
        printf("(%u) My parent is: %u\n", getpid(), getppid());
    }
    return 0;
}
