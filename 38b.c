#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){

        char buf[100];

        int fd2 = open("myfifo1", O_RDONLY, 0666);
        read(fd2, buf, sizeof(buf));
        printf("Message from first program: %s", buf);
        close(fd2);

        int fd1 = open("myfifo2", O_WRONLY, 0666);
        write(fd1, "Hello from second program\n", sizeof("Hello from second program\n"));
        close(fd1);

    return (0);
}