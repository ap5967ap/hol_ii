#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pid;
    printf("Enter the process pid to send signal: ");
    scanf("%d", &pid);
    if(kill(pid, SIGSTOP) == -1)
    {
        perror("kill");
        exit(1);
    }
    printf("Sent SIGSTOP signal to process with PID %d\n", pid);
}