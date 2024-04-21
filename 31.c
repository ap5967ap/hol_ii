#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main()
{
    int fd[2];
    if(pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }
    char buf[BUFSIZ];
    scanf("%[^\n]", buf);
    if(write(fd[1], buf, BUFSIZ) == -1)
    {
        perror("write");
        return 1;
    }
    printf("Data written to pipe\n");
    memset(buf, 0, BUFSIZ); // clearing buffer
    if(read(fd[0], buf, BUFSIZ) == -1)
    {
        perror("read");
        return 1;
    }
    printf("Data read from pipe: %s\n", buf);
    close(fd[0]);
    close(fd[1]);
    return 0;
}