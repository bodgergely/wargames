#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#define NR_SYS_READ  3
#define NR_SYS_WRITE 4
#define NR_SYS_OPEN  5

const char* softmmu = "/proc/softmmu";
unsigned int virt_addr = 0x08200000;
unsigned int phys_addr = 0xdeadbeef;

int main(int argc, char** argv)
{
    char* text = mmap(virt_addr, 4096, PROT_EXEC|PROT_READ|PROT_WRITE,
            MAP_ANONYMOUS|MAP_SHARED|MAP_FIXED|MAP_POPULATE,
            -1, 0);

    int fd = syscall(NR_SYS_OPEN, softmmu, O_RDWR, 0);
    printf("Press Enter to write %p to %s\n", virt_addr, softmmu);
    getchar();
    syscall(NR_SYS_WRITE, fd, (void*)&virt_addr, 4);
    printf("Press Enter to read from %s\n", softmmu);
    getchar();
    syscall(NR_SYS_READ, fd, (void*)&phys_addr, 4);

    printf("Phys address: %p\n", phys_addr);
    
    return 0;
}
