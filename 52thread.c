#define _DECLARE_GETTID
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <arpa/inet.h>
struct arg
{
    int nsd;
    struct sockaddr_in cli;
};

void *handleconnect(void* ag){
    int sd = ((struct arg *)ag)->nsd;
    struct sockaddr_in cli = ((struct arg *)ag)->cli;
    char buf[1000];
    read(sd,buf,1000);
    printf("Message from client: %s",buf);
    printf("Handling client %s from child process with tid %d\n",inet_ntoa(cli.sin_addr),gettid());
    
    write(sd,"Hello, from server\n",sizeof("Hello, from server\n"));
    close(sd);
}

int main(){
    struct sockaddr_in serv,cli;
    pthread_t threads;
    int sd = socket(AF_INET,SOCK_STREAM,0);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_family = AF_INET;
    serv.sin_port = htons(5041);
    bind(sd,(struct sockaddr *) &serv,sizeof(serv));
    listen(sd,5);
    while(1){
        int len = sizeof(cli);
        int nsd = accept(sd,(struct sockaddr *) &cli,&len);
        struct arg ad;
        ad.nsd = nsd;
        ad.cli = cli;
        pthread_create(&threads,NULL,(void *)handleconnect,(void*)&ad);
    }
    pthread_exit(NULL);
    close(sd);
}