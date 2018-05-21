#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    char* filepath;
    int ret;
    char command[512];
    
    //printf("REAL user id:      %d\n", getuid());
    //printf("EFFECTIVE user id: %d\n", geteuid());
    
    if(argc <=1 ) {
        printf("usage: ./printfile <filepath>\n");
        return -1;
    }

    filepath = argv[1];
    if((ret = access(filepath, R_OK))) {
        printf("You cant have that file...\n");
        return -1;
    }

    setreuid(geteuid(), geteuid());  //we should check return value!

    snprintf(command, sizeof(command) - 1, "/bin/cat %s", filepath);
    system(command);

    return 0;
}

