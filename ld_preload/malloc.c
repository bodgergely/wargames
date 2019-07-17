#include <stdint.h>

void *malloc(__ssize_t size)
{
    return (void*)0xdaedbeef;
}

void free(void* ptr)
{
    printf("Freeing ptr at: %p\n", ptr);
}
