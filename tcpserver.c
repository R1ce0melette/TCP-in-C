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
    char *msgUsername = "enter username";
    char *msgPassword = "enter password";
    const char username[] = "placeholder";
    const char password[] = "placeholder";
    //char *data = "";
    char *pass = "congratz";
    char buffer[1024] = {0};
    printf("\nServer listening on port %d...\n", 6969);
    int server_address_len = sizeof(server_address);
    while (1) {
        if ((new_socket = accept(sockfd, (struct sockaddr *)&server_address, (socklen_t *)&server_address_len)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("New connection accepted\n");
        send(new_socket, msgUsername, strlen(msgUsername), 0);
        read(new_socket, buffer, 1024);
        //data = buffer;
        printf("%s", buffer);
        printf("%d", strcmp(buffer, username));
        while(strcmp(buffer, username) == 0){
            send(new_socket, msgPassword, strlen(msgPassword), 0);
            read(new_socket, buffer, 1024);
            //data = buffer;
            if (strcmp(buffer,password) == 0){
                printf("%s", pass);
                send(new_socket, pass, strlen(pass), 0);
                break;
            } else {
                continue;
            }
            printf("%s", buffer);
        } 
        close(new_socket);
    }
    //clean up socket
    close(sockfd);
}
