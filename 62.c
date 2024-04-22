#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <bits/sigaction.h>

int main()
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler=SIG_IGN;
    sigaction(SIGINT, &sa, NULL);
    printf("Signal SIGINT ignored for 5 seconds\n");
    sleep(5);
    sa.sa_handler=SIG_DFL;
    sigaction(SIGINT, &sa, NULL);
    printf("Signal SIGINT set to default\n");
    while(1);

}