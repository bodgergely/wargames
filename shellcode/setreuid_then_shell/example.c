#include <stdio.h>
#include <unistd.h>

void setreuid_shell();

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
    setreuid_shell();
    return 0;
}

