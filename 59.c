#include<stdio.h>
#include<signal.h>
#include <sys/time.h>
#include<stdlib.h>
 #include <unistd.h>
void sigsev()
{
    printf("Segmentation fault caught\n");
    exit(1);
}

void sigint()
{
    printf("Interrupt signal caught\n");
    exit(1);
}

void sigfpe()
{
    printf("Floating point exception caught\n");
    exit(1);
}

void handler(int sig)
{
    printf("signal caught\n");
    exit(1);
}

int main()
{
    int choice;
    printf("Choose an option:\n1.) SIGSEGV\n2.) SIGINT\n3.) SIGFPE\n4.) SIGALRM (alarm system call)\n5.) SIGALRM (setitimer system call)\n6.) SIGVTALRM (setitimer system call)\n7.) SIGPROF (setitimer system call)\n=> ");
    scanf("%d", &choice);
    if(choice==1)
    {
        signal(SIGSEGV,sigsev);
        int *x=(int *)5;
        printf("%d\n",*x);
    }
    else if(choice==2)
    {
        signal(SIGINT,sigint);
        while(1);
    }
    else if(choice==3)
    {
        signal(SIGFPE,sigfpe);
        int x=3;
        int z=x-x;
        x=x/z;
    }
    else if(choice==4)
    {
        signal(SIGALRM,handler);
        alarm(5);
        while(1);
    }
    else if(choice==5)
    {
        signal(SIGALRM,handler);
        struct itimerval it;
        it.it_value.tv_sec = 5;
        it.it_value.tv_usec = 0;
        it.it_interval.tv_sec = 5;
        it.it_interval.tv_usec = 0;
        setitimer(ITIMER_REAL, &it, NULL);
        while(1);
    }
    else if(choice==6)
    {
        signal(SIGVTALRM,handler);
        struct itimerval it;
        it.it_value.tv_sec = 5;
        it.it_value.tv_usec = 0;
        it.it_interval.tv_sec = 5;
        it.it_interval.tv_usec = 0;
        setitimer(ITIMER_VIRTUAL, &it, NULL);
        while(1);
    }
    else if(choice==7)
    {
        signal(SIGPROF,handler);
        struct itimerval it;
        it.it_value.tv_sec = 5;
        it.it_value.tv_usec = 0;
        it.it_interval.tv_sec = 5;
        it.it_interval.tv_usec = 0;
        setitimer(ITIMER_PROF, &it, NULL);
        while(1);
    }
    else
    {
        printf("Invalid choice\n");
    }
}