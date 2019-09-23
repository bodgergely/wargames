#include <stdio.h>
#include <stdlib.h>
//#include <sys/capability.h>

void printFile(char* filename){
    FILE *fileptr;
    char ch;
    fileptr = fopen(filename, "r");
    if (fileptr == NULL){
        printf("Cannot open file \n");
                exit(0);
    }
    ch = fgetc(fileptr);
    while (ch != EOF){
        printf ("%c", ch);
        ch = fgetc(fileptr);
    }
    fclose(fileptr);
}


int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("provide a file to open!\n");
        exit(1);
    }

    printFile(argv[1]);

    return 0;
}

