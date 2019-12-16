#include <unistd.h>
#include <stdio.h>
#include <thread>
#include <vector>
#include <sys/types.h>
#include <sys/syscall.h>

using namespace std;


void reportpid(long iter)
{
    volatile long p;
    printf("%lu\n", syscall(SYS_gettid));
    for(long i=0;i<iter;i++)
        p = i;
}


int main(int argc, char *argv[])
{
    vector<thread> threads;
    printf("PID: %d\n", getpid());
    for(int i=0;i<atoi(argv[1]);i++) {
        //this_thread::sleep_for(chrono::milliseconds(300));
        threads.push_back(thread(reportpid, atol(argv[2])));
    }

    for(auto& t :  threads) {
        if(t.joinable())
            t.join();
    }

    return 0;
}
