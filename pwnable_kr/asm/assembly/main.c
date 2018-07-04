#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void read_write_file();

int main(int argc, char* argv[])
{
    /*
    if(setreuid(1001, 1001)) {
        printf("Setreuid failed!, errno: %u\n", errno);
        getchar();
        return 1;
    }
    */
    read_write_file();
    return 0;
}

