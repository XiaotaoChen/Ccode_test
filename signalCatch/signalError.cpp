#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

void ctrlC(int sig) {
    std::cout << "OUCH! - I got signal " << sig << std::endl;
}

void triggleCtrlC() {
    struct sigaction act;
    act.sa_handler = ctrlC;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);
    int count = 5;
    while(count-- > 0) {
        std::cout << "Hello World!\n";
        sleep(1);
    }
}

int count=0;

void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    std::cout << "Caught segfault signal: " << signal << ", signal code: " << si->si_code << ", addr: " << si->si_addr  << " count: " << count++ << std::endl;
}

void triggleSegfault(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags   = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);

    std::cout << "dstase\n";
    int *foo = NULL;
    /* Cause a seg fault */
    *foo = 1;

    std::cout << "***************dstase\n";
}

void SigBusSigaction(int signal, siginfo_t *si, void* arg) {
    std::cout << "Signal Bus, signal: " << signal << ", signal code: " << si->si_code << ", addr: " << si->si_addr << std::endl;
}

void triggleSigBus() {

    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = SigBusSigaction;
    sa.sa_flags = SA_SIGINFO;
    // sigaction(SIGBUS, &sa, NULL);

    sigaction(SIGSEGV, &sa, NULL);

    int *pi = (int*)0x00001111;
    std::cout << "pi addres: " << pi  << std::endl;
    *pi = 17;
    
}

int main()
{
    // triggleCtrlC();
    triggleSegfault();
    // triggleSigBus();


    return 0;
}