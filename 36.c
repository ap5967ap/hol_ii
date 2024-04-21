#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define pr perror
#define pt(a) printf("%s\n",a)
#define pt1(a) printf("%d\n",a)

int main(int argc, char **argv)
{
    if(argc!=2)
    {
        pt("Usage: ./a.out mknod|mkfifo");
        return 1;
    }
    if (strcmp(argv[1],"mknod")==0)
    {
        if(mknod("fifo",__S_IFIFO|0666,0)==-1)
        {
            pr("mknod");
            return 1;
        }

    }
    else if (strcmp(argv[1],"mkfifo")==0)
    {
        if(mkfifo("fifo",0666)==-1)
        {
            pr("mkfifo");
            return 1;
        }
    }
    else
    {
        pt("Invalid option");
        return 1;
    }
    //mkfifo calls mknodat internally mknod is faster.
    
}