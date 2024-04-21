#include<signal.h>
#include<stdio.h>
#include<unistd.h>

#define pr printf

int main()
{
    signal(SIGINT,SIG_IGN);
    pr("Signal SIGINT ignored for 5 seconds\n");
    sleep(5);
    signal(SIGINT,SIG_DFL);
    pr("Signal SIGINT set to default\n");
    while(1);
    
}