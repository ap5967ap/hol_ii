#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#define pr perror
#define pt(a) printf("%s\n",a)
#define pt1(a) printf("%d\n",a)

int main()
{
    char buf[BUFSIZ];
    pt("Enter the message to send to fifo");
    scanf("%[^\n]",buf);
    if(mkfifo("tempfifo",0666|__S_IFIFO)==-1)
    {
        pr("mkfifo");
        return 1;
    }
    int fd;
    if((fd=open("tempfifo",O_WRONLY))==-1)
    {
        pr("open");
        return 1;
    }
    if(write(fd,buf,BUFSIZ)==-1)
    {
        pr("write");
        return 1;
    }
    close(fd);
}