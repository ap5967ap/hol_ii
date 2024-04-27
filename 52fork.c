#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    int socket_fd, new_socket_fd;
    struct sockaddr_in server_address, client_address;
    char buffer[BUFSIZ];
    memset(buffer, 0, sizeof(buffer));
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(5555);
    int tr=1;

// kill "Address already in use" error message
    if (setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&tr,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    if (bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(socket_fd, 5) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d\n", 5555);
    while (1)
    {
        int address_len = sizeof(client_address);
        if ((new_socket_fd = accept(socket_fd, (struct sockaddr *)&client_address, (socklen_t *)&address_len)) < 0)
        {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        int pid = fork();
        if (pid < 0)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            printf("Handling client from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
            char *message = "Hello from server";
            int write_size = write(new_socket_fd, message, strlen(message));
            if (write_size < 0)
            {
                perror("Write failed");
                exit(EXIT_FAILURE);
            }
            printf("Sent message to client: %s\n", message);
            close(new_socket_fd);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(new_socket_fd);
        }
    }
    close(socket_fd);

    return 0;
}