#include <stdio.h>

struct doo {
    char       sh[5];
    unsigned    big;
};

struct boo {
    int         a;
    struct doo  je;
    int         b;
    char        c;
};

struct boo do_some(int a, int b)
{
    int i;
    struct boo kefir;
    kefir.a = a;
    kefir.b = b;
    kefir.c = a + b;
    kefir.je.big = a * b;
    for(i=0;i<4;i++)
        kefir.je.sh[i] = 0x42;
    kefir.je.sh[4] = 0x0;
    return kefir;
}

struct boo do_more(struct boo ajaj)
{
    ajaj.b = 0xa;
    ajaj.c = 0xb;
    ajaj.je.big = 0xdeadbeef;
    return ajaj;
}


int main(int argc, char* argv[])
{
    struct boo bam;
    bam = do_more(bam);
    //printf("%d %d %d\n", bam.a, bam.b, (int)bam.c);
    //printf("%s %d\n", bam.je.sh, bam.je.big);
    // printf("sizeof(struct boo): %u\n", sizeof(struct boo));
    //printf("sizeof(struct doo): %u\n", sizeof(struct doo));
    return 0;
}

