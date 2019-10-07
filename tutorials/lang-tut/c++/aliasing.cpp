#include <thread>
#include <chrono>
#include <stdio.h>

using namespace std;

unsigned long gNum = 0;

void print()
{
    while(1) {
        printf("Val: %lu\n", gNum);
        this_thread::sleep_for(chrono::seconds(2));
    }    
}

int main(int argc, char *argv[])
{

    auto t = thread(print); 
    for(;;) {
        gNum++;
    }

    t.join();
    
    return 0;
}
