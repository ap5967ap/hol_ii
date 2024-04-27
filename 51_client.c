
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
    struct sockaddr_in serv;
    int sd;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(8200);
    connect(sd, (struct sockaddr *)&serv, sizeof(serv));
    char buf[BUFSIZ];
    int ret;
    write(1, "Sending message to server...\n", sizeof("Sending message to server...\n"));
    write(sd, "Message From client\n", sizeof("Message From client\n"));
    ret = read(sd, buf, sizeof(buf));
    printf("Got from server: %s\n", buf);
    close(sd);

    return (0);
}