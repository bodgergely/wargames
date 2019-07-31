#include <stdio.h>

int fib(int n)
{
    if(n == 1 || n == 0)
        return 1;
    return fib(n-1) + fib(n-2);
}

int calculate(int n)
{
    int j = 0;
    for(int i=0;i<n;i++) {
        j += fib(25) * i;
    }

    return j;
}

int main(int argc, char** argv)
{
    int iter = 600000;
    int res = calculate(iter);
    printf("%d\n", res);
    return 0;
}


