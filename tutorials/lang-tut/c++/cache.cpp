#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

#define PAGE_SIZE 4096
#define COUNT 8

int main(int argc, char *argv[])
{
    char* mem;
    srand(time(NULL));

    for(int j=0;j<10000000;j++) {
        mem = (char*)malloc(PAGE_SIZE * 1024 * 32);
        for(int i=0;i<1000;i++) {
            if(!mem) {
                exit(111);
            }
            int r = rand() % (PAGE_SIZE * 1024 * 32);
            mem[r] = 0;
        }
        free(mem);
    }

    return 0;
}
