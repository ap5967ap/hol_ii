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
    int fd;
    if((fd=open("tempfifo",O_RDONLY))==-1)
    {
        pr("open");
        return 1;
    }
    if(read(fd,buf,BUFSIZ)==-1)
    {
        pr("write");
        return 1;
    }
    close(fd);
    pt("Data read from fifo:");
    pt(buf);
}