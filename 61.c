#include <signal.h>
#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>

void handler()
{
    printf("Signal caught\n");
    exit(1);
}

int main()
{
    int choice;
    printf("Choose an option:\n1.) SIGSEGV\n2.) SIGINT\n3.) SIGFPE\n");
    scanf("%d", &choice);
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    if(choice==1)
    {
        sa.sa_handler=handler;
        sigaction(SIGSEGV, &sa, NULL);
        int *x=(int *)5;
        printf("%d\n",*x);
    }
    else if(choice==2)
    {
        sa.sa_handler=handler;
        sigaction(SIGINT, &sa, NULL);
        while(1);
    }
    else if(choice==3)
    {
        sa.sa_handler=handler;
        sigaction(SIGFPE, &sa, NULL);
        int x=3;
        int z=x-x;
        x=x/z;
    }
    else
    {
        printf("Invalid choice\n");
    
    }
    
    
    while(1);
}