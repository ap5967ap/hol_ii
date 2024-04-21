#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

void handler()
{
    printf("Signal received\n");
}
int choice(int x)
{
    switch (x)
    {
    case 1:
        return ITIMER_REAL;
    case 2:
        return ITIMER_VIRTUAL;
    case 3:
        return ITIMER_PROF;
    default:
        return -1;
    }
}
int choice2(int x)
{
    switch (x)
    {
    case 1:
        return SIGALRM;
    case 2:
        return SIGVTALRM;
    case 3:
        return SIGPROF;
    default:
        return -1;
    }
}
int main()
{
    int x;
    printf("Choose an option:\n1.) ITIMER_REAL \n2.) ITIMER_VIRTUAL\n3.) ITIMER_PROF\n=> ");
    scanf("%d", &x);
    struct itimerval it;
    signal(choice2(x), handler);
    it.it_value.tv_sec = 10;
    it.it_value.tv_usec = 10;
    it.it_interval.tv_sec = 10;
    it.it_interval.tv_usec = 10;
    setitimer(choice(x), &it, NULL);
    while (1)
    {
    }
}
