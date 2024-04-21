#include<unistd.h>
#include<stdio.h>
#include <sys/types.h>
#include <signal.h>
int main()
{
    if(fork())
    {
        printf("parent looping\n");
        while(1);
    }
    else
    {
        printf("child process\n");
        printf("Enter to send kill to parent process\n");
        getchar();
        kill(getppid(),SIGKILL);
    }
}