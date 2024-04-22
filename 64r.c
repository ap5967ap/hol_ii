#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <bits/sigaction.h>

void handler (int sig){
    printf("Signal %d has been caught\n", sig);
    exit(0);
}

int main(){

    printf("Process pid id %d\n", getpid());
    printf("waiting for signal SIGSTOP\n");
    signal(SIGSTOP, handler);
    getchar();
    return (0);
}