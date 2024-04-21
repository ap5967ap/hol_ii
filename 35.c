#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#define pr perror
#define pt(a) printf("%s\n",a)
#define pt1(a) printf("%d\n",a)

int main()
{
    int fd1[2],fd2[2];
    if(pipe(fd1)==-1||pipe(fd2)==-1)
    {
        pr("pipe");
        return 1;
    }
    int a;
    if(a=fork())
    {
        dup2(fd1[1],1);
        close(fd1[0]);
        close(fd2[0]);
        close(fd2[1]);
        execlp("ls", "ls", "-l","/", NULL);
    }
    else
    {
        wait(&a);
        if(a=fork())
        {
            close(fd1[1]);
            close(fd2[0]);
            dup2(fd1[0],0);
            dup2(fd2[1],1);
            execlp("grep", "grep", "^d", NULL);
        }
        else
        {
            wait(&a);
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[1]);
            dup2(fd2[0],0);
            execlp("wc", "wc", NULL);
        }
    }
}