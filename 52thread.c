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
    int nsfsd;
    struct sockaddr_in client_address;
};
void *conn(void *args)
{
    struct sockaddr_in client_address;
    int nsfd = ((struct arg *)args)->nsfsd;
    client_address = ((struct arg *)args)->client_address;
    printf("Handling client from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
    char buf[BUFSIZ];
    write(nsfd, "Message From server\n", sizeof("Message From server\n"));
}

int main()
{
    struct sockaddr_in server, client;
    int sd, nsd, clientLen;
    pthread_t threads;
    bool result;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(5555);
    bind(sd, (struct sockaddr *)&server, sizeof(server));
    listen(sd, 5);
    while (1)
    {
        clientLen = sizeof(client);
        nsd = accept(sd, (struct sockaddr *)&client, &clientLen);
        write(1, "Connected to the client.....\n", sizeof("Connected to the client.....\n"));
        struct arg nsds={nsd, client};
        if (pthread_create(&threads, NULL, (void *)conn, (void *)&nsds) < 0)
        {
            perror("could not create thread");
            return 1;
        }
    }
    pthread_exit(NULL);
    close(sd);
    return 0;
}