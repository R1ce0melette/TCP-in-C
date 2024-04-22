#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(){
    int sockfd, new_socket;
    struct sockaddr_in server_address;

    // Initialize socket file descriptor which is like a handler and also, the socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) <0) {
        perror("Sockfd init failed.\n");
        exit(EXIT_FAILURE);
    }
    printf("socket created");
    //Define server address
    server_address.sin_family = AF_INET; //IPv4
    server_address.sin_addr.s_addr = INADDR_ANY; //any interface
    server_address.sin_port = htons(6969); //htons convert 6969 from host byte order to network byte order
    //Bind socket to defined port
    if (bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
        perror("Binding failed.\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    //Listen on binded socket
    if ((listen(sockfd, 5)) < 0){
        perror("Listening setup failed.\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    //Accept incoming traffic
    struct sockaddr_in client_address;
    int clientsoc;
    char *motd = "Welcome";
    char buffer[1024] = {0};
    printf("Server listening on port %d...\n", 6969);
    int server_address_len = sizeof(server_address);
    while (1) {
        if ((new_socket = accept(sockfd, (struct sockaddr *)&server_address, (socklen_t *)&server_address_len)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("New connection accepted\n");

        // Send welcome message
        send(new_socket, motd, strlen(motd), 0);
        read(new_socket, buffer, 1024);
        close(new_socket);
    }
    //clean up socket
    close(sockfd);
    return 0;
}