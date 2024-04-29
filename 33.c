#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define pr perror
void pt(char *x){printf("%s\n",x);}
void pt1(int x){printf("%d\n",x);}

int main()
{
    int fd1[2],fd2[2];
    if(pipe(fd1)==-1||pipe(fd2)==-1)
    {
        pr("pipe");
        return 1;
    }
    if(!fork())
    {
        pt("Child:Enter the message to send to parent");
        char buf[BUFSIZ];
        scanf("%[^\n]",buf);
        close(fd1[0]);
        if(write(fd1[1],buf,BUFSIZ)==-1)
        {
            pr("write");
            return 1;
        }
        close(fd1[1]);
        char buf2[BUFSIZ];
        close(fd2[1]);
        if(read(fd2[0],buf2,BUFSIZ)==-1)
        {
            pr("read");
            return 1;
        }
        close(fd2[0]);
        pt("Child:Data read from parent:");
        pt(buf2);
    }
    else
    {
        char buf[BUFSIZ];
        close(fd1[1]);
        if(read(fd1[0],buf,BUFSIZ)==-1)
        {
            pr("read");
            return 1;
        }
        close(fd1[0]);
        pt("Parent:Data read from child:");
        pt(buf);
        pt("Parent:Enter the message to send to child");
        char buf2[BUFSIZ];
        scanf("%[^\n]",buf2);
        close(fd2[0]);
        if(write(fd2[1],buf2,BUFSIZ)==-1)
        {
            pr("write");
            return 1;
        }
        close(fd2[1]);
    }
}