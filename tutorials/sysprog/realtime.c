#define _GNU_SOURCE
#include <unistd.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void print_prio_limits()
{
    //int minprio = sched_get_priority_min(SCHED_FIFO);
    //int maxprio = sched_get_priority_max(SCHED_FIFO);
    //printf("Min prio: %d\n", minprio);
    //printf("Max prio: %d\n", maxprio);
}

int main(int argc, char *argv[])
{
    struct sched_param param; 
    cpu_set_t set;

    CPU_ZERO(&set); // init the data struct
    CPU_SET(atoi(argv[2]), &set); // pin to CPU specified on cmd line arg 2

    if(sched_setaffinity(0, sizeof(cpu_set_t), &set) != 0) {
        /*printf("Error sched_setaffinity: %d\n", errno);*/
        perror("sched_setaffinity");
        exit(errno);
    }

    param.sched_priority = atoi(argv[1]);  // prio is set on cmd line 1 
    if(sched_setscheduler(0, SCHED_FIFO, &param) != 0 ) {
        perror("sched_setscheduler");
        exit(errno);
    }

    const char* msg = "I am here\n";

    for(int r=0;r<10;r++) {
        for(int i=0;i<1000;i++) {
            for (int j = 0; j < 1000; ++j) {
               for (int k = 0; k < 1000; ++k) {
                   
               } 
            }
        }
        write(1, msg, 10);
    }

    return 0;
}



