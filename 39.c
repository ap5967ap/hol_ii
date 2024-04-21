#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#define pr perror
#define pt(a) printf("%s\n",a)
#define pt1(a) printf("%d\n",a)

int main()
{
    char buf[BUFSIZ];
    int fd=open("myFifo",O_WRONLY,0666);
    pt("Enter the message to send to fifo");
    scanf("%[^\n]", buf);
    if(fd==-1)
    {
        pr("open");
        return 1;
    }
    if(write(fd,buf,BUFSIZ)==-1)
    {
        pr("write");
        return 1;
    }
}