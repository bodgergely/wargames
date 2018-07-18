#include <stdio.h>
#include <stdlib.h>

int main(){
	unsigned int random;
    srand(1);
	random = rand();	// random value!
    printf("%u\n", random);
//    printf("RAND_MAX: %d\n", RAND_MAX);

	unsigned int key=0;
    printf("%d\n", 3039230856);
	scanf("%d", &key);

	if( (key ^ random) == 0xdeadbeef ){
		printf("Good!\n");
		system("/bin/cat flag");
		return 0;
	}

	printf("Wrong, maybe you should try 2^32 cases.\n");
	return 0;
}

