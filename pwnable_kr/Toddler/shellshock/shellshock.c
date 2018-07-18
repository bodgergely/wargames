#include <stdio.h>
int main(){
	setresuid(getegid(), getegid(), getegid());
	setresgid(getegid(), getegid(), getegid());
	system("/home/remnux/workspace/hacking/wargames/pwnable_kr/shellshock/bash -c 'echo shock_me'");
	return 0;
}

