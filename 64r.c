#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("handler %d\n", sig);
}

int main()
{
    printf("PID: %d\n", getpid());
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler=handler;
    printf("Waiting for SIGSTOP signal\n");
    while(1)
    {
        sigaction(SIGSTOP, &sa, NULL);
    }
}