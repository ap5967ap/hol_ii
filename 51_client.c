#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){
    struct sockaddr_in serv;
    int sd = socket(AF_INET,SOCK_STREAM,0);

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(5041);

    int a=connect(sd,(struct sockaddr *)&serv,sizeof(serv));
    if(a<0)
    {
        perror("connect");
        exit(1);
    }
    char buf[100];
    write(sd,"message from client side\n",sizeof("message from client side\n"));
    read(sd,buf,sizeof(buf));
    printf("%s\n",buf);

    close(sd);
}