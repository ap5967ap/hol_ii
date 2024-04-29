#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>

int main(){
    fd_set rfds;
    struct timeval tv;

    int fd = open("myfifo", O_RDWR, 0666);
    printf("Timer started for 10 seconds.\n");

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    tv.tv_sec = 10;
    tv.tv_usec = 0;

    int stat = select(fd + 1, &rfds, NULL, NULL, &tv);

    if (stat){
        char buf[100];
        read(fd, buf, sizeof(buf));
        printf("Data from fifo: %s", buf);
    }
    else{
        printf("No data got in 10 seconds.\n");
    }
    close(fd);
    return (0);
}