#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){

    char buf[100];

    int fd1 = open("myfifo1", O_WRONLY, 0666);
    write(fd1, "Hello from first program\n", sizeof("Hello from first program\n"));
    close(fd1);

    int fd2 = open("myfifo2", O_RDONLY, 0666);
    read(fd2, buf, sizeof(buf));
    printf("Message from second program: %s", buf);

    close(fd2);
    return (0);
}