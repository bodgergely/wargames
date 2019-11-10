#include <unistd.h>
#include <stdio.h>

//char *ttyname(int fd);

//int ttyname_r(int fd, char *buf, size_t buflen);

int main(int argc, char *argv[])
{
    printf("%s\n", ttyname(0));
    printf("%s\n", ttyname(1));
    printf("%s\n", ttyname(2));
    return 0;
}

