#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(){
    struct sockaddr_in serv,cli;
    char buf[1000];

    int sd = socket(AF_INET,SOCK_STREAM,0);

    serv.sin_addr.s_addr = INADDR_ANY;
    // serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_family = AF_INET;
    serv.sin_port = htons(5041);
    bind(sd,(struct sockaddr *)&serv,sizeof(serv));
    listen(sd,5);
    // printf("Server listening on port 5000\n");
    // printf("\n");
    // write(1,"Server listening on port 5000\n",sizeof("Server listening on port 5000\n"));
    while(1){
        int len = sizeof(cli);
        int nsd = accept(sd,(struct sockaddr *)&cli,&len);
        int pid = fork();
        if(pid==0){ 
            printf("Handling client %s from child process with pid %d\n",inet_ntoa(cli.sin_addr),getpid());
            read(nsd,buf,100);
            printf("Message from client: %s",buf);
            write(nsd,"Hello, from server\n",sizeof("Hello, from server\n"));
            close(nsd);
        }
        else{
            close(nsd);
        }
    }
}