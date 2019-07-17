#define _GNU_SOURCE
#include <dlfcn.h>

// our custom includes
#include <stdio.h>

 
typedef int (*orig_open_f_type)(const char *pathname, int flags);
 

void evil(const char *pathname, int flags)
{
    printf("Open called on: %s with flags: %x\n", pathname, flags);
}

int open(const char *pathname, int flags, ...)
{
    /* Some evil injected code goes here. */
    evil(pathname, flags);
    orig_open_f_type orig_open;
    orig_open = (orig_open_f_type)dlsym(RTLD_NEXT,"open");
    return orig_open(pathname,flags);
}

