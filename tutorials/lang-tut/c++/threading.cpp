#include <thread>
#include <vector>

using namespace std;


void counter()
{
    volatile unsigned long long i = 0;
    while(1) {
        i++;
    }
}


int main(int argc, char *argv[])
{
    vector<thread> threads;

    for(int i=0;i<atoi(argv[1]);i++) {
        threads.push_back(thread(counter));
    }

    for(auto& t :  threads) {
        t.join();
    }

    return 0;
}
