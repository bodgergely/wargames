#include <thread>
#include <vector>
//#include <sys/types.h>
//#include <unistd.h>

using namespace std;


void counter()
{
    volatile unsigned long long i = 0;
    while(1) {
        i++;
        //if (i % 1000000000 == 0) {
            //printf("My pid: %u, my parent: %u\n", getpid(), getppid());
        //}
    }
}


int main(int argc, char *argv[])
{
    vector<thread> threads;

    //printf("Main process, pid: %u\n", getpid());

    for(int i=0;i<atoi(argv[1]);i++) {
        threads.push_back(thread(counter));
    }

    for(auto& t :  threads) {
        t.join();
    }

    return 0;
}
