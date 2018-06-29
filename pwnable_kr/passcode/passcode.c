#include <stdio.h>
#include <stdlib.h>

int main();
void login();

void login(){
	int passcode1;
	int passcode2;

    printf("STAGE 1 passcode1: %d, passcode2: %d\n", passcode1, passcode2);
	printf("enter passcode1 : ");
	scanf("%d", passcode1);
	fflush(stdin);

	// ha! mommy told me that 32bit is vulnerable to bruteforcing :)
	printf("enter passcode2 : ");
        scanf("%d", passcode2);

	printf("checking...\n");
    printf("STAGE 2 passcode1: %d, passcode2: %d\n", passcode1, passcode2);
    printf("exit at: %p, main at: %p, login at: %p\n", exit, main, login);
    if(passcode2==13371337) {
        printf("We got the match on passcode2!\n");
    }
	if(passcode1==338150 && passcode2==13371337){
                printf("Login OK!\n");
                system("/bin/cat flag");
        }
        else{
                printf("Login Failed!\n");
		exit(0);
        }
}

void welcome(){
	char name[100];
	printf("enter you name : ");
	scanf("%100s", name);
	printf("Welcome %s!\n", name);
}

int main(){
	printf("Toddler's Secure Login System 1.0 beta.\n");

	welcome();
	login();

	// something after login...
	printf("Now I can safely trust you that you have credential :)\n");
	return 0;	
}

