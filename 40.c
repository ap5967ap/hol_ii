#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#define pr perror
#define pt(a) printf("%s\n",a)
#define pt1(a) printf("%lld\n",a)

int main()
{
    long long PIPE_BUF, OPEN_MAX;
    PIPE_BUF=pathconf(".",_PC_PIPE_BUF);
    OPEN_MAX=sysconf(_SC_OPEN_MAX);
    pt("Maximum number of open files in the system is");
    pt1(PIPE_BUF);
    pt("Maximum number of bytes that can be written atomically to a pipe is");
    pt1(OPEN_MAX);
}