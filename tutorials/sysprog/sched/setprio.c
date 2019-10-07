#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int prio = getpriority(PRIO_PROCESS, 0);
    printf("%d\n", prio);
    setpriority(PRIO_PROCESS, 0, 19);
    prio = getpriority(PRIO_PROCESS, 0);
    printf("%d\n", prio);
    return 0;
}
