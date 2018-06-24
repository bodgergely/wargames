// -- andrewg, original author was zen-parse :)
#include <stdlib.h>


int main(int argc, char **argv)
{
        *(unsigned int*)(0x08048326) = 0xdeadbeef;
        getchar();
        printf(argv[1]);
        exit(EXIT_FAILURE);
}
