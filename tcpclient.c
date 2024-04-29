#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    int clientsoc;
    struct sockaddr_in server_address;
    //create a socket file desriptor
    if ((clientsoc = socket(AF_INET, SOCK_STREAM, 0)) <0){
        perror("Socket init failed");
        exit(EXIT_FAILURE);
    }
    //Define server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6969);
    //for client app, server IP addresses need to be translated into binary
    if ((inet_pton(AF_INET, "10.0.0.1", &server_address.sin_addr)) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }
    //connect socket to the server
    int server_address_len = sizeof(server_address);
    if((connect(clientsoc, (struct sockaddr *)&server_address, server_address_len)) <0){
        perror("Connection fail.\n");
    }
    char msg[buffer_size] = "";
    char buffer[1024] = {0};
    read(clientsoc, buffer, 1024); 
    printf("Server response: %s\n", buffer);
    while (buffer != "exit"){
        fgets(msg, buffer_size, stdin);
        send(clientsoc, msg, strlen(msg), 0);
        read(clientsoc, buffer, 1024); //read server response
        printf("Server response: %s\n", buffer);
    } 
    // Send message to server
    //const char *message = "Hello server";
    //send(clientsoc, message, strlen(message), 0);
    //printf("Message sent to server\n");
    //read
    //read(clientsoc, buffer, 1024); //read server response
    //printf("Server response: %s\n", buffer);
    //close socket
    close(clientsoc);
    return 0;
}
