#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#define pr perror
#define pt(a) printf("%s\n",a)
#define pt1(a) printf("%d\n",a)

int main()
{
    fd_set rfds;
    struct timeval tv;
    int retval;
    int fd=open("myFifo",O_RDONLY,0666);
    if(fd==-1)
    {
        pr("open");
        exit(1);
    }
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);  
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    retval = select(fd+1, &rfds, NULL, NULL, &tv);
    if (retval == -1)
        pr("select()");
    else if (retval)
        
        {
            pt("Data is available now.\n");
            char buf[BUFSIZ];
            if(read(fd,buf,BUFSIZ)==-1)
            {
                pr("read");
                return 1;
            }
            printf("Data read from fifo is %s\n",buf);
        }

    else
        printf("No data within ten seconds.\n");
}