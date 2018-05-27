#include <stdio.h>
#include <unistd.h>

void jozsi_setreuid();

int juhee()
{
    int a = 1;
    int b = 2;
    a = printf("Doing this!\n");
    return a;
}

int main(int argc, char* argv[])
{
    int res;
    res = juhee(); 
    jozsi_setreuid();
    system("/bin/cat /home/jozsi/README.txt");
    return 0;
}

