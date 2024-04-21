#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define pr perror
void pt(char *x){printf("%s\n",x);}
void pt1(int x){printf("%d\n",x);}

int main()
{
    int fd[2];
    if(pipe(fd) == -1)
    {
        pr("pipe");
        return 1;
    }
    if(fork())
    {
        pt("Enter message to send to child process");
        char buf[BUFSIZ];  
        scanf("%[^\n]", buf);
        close(fd[0]);
        if(write(fd[1], buf, BUFSIZ) == -1)
        {
            pr("write");
            return 1;
        }
        close(fd[1]);

    }
    else
    {
        char buf[BUFSIZ];
        close(fd[1]);
        if(read(fd[0], buf, BUFSIZ) == -1)
        {
            pr("read");
            return 1;
        }
        close(fd[0]);
        pt("Data read from parent:");
        pt(buf);
    }
}