#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char** argv)
{
    unsigned long long counter;
    pid_t pid = fork();
    if(!pid) {
        while(1) {
            counter++;
        }
    } else {
        printf("Parent (%d) exiting, child: %d\n",getpid(), pid);
        exit(0);
    }
    return 0;
}

