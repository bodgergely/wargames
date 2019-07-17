#include <stdlib.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    for(int i=0;i<1000;i++)
        rand();

    printf("%d\n", rand());
    return 0;
}
