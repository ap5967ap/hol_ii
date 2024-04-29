#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>

int main(){

    struct sockaddr_in serv, cli;
    int sd;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(5041);
    bind(sd, (struct sockaddr *)&serv, sizeof(serv));
    listen(sd, 0);
    int nsd;
    int len = sizeof(cli);
    nsd = accept(sd, (struct sockaddr *)&cli, (unsigned int *)&len);
    char buf[100];
    memset(buf, 0, sizeof(buf));
    read(nsd, buf, sizeof(buf));
    write(1, buf, sizeof(buf));
    write(nsd, "Message From server\n", sizeof("Message From server\n"));
    close(sd);
    return(0);
}