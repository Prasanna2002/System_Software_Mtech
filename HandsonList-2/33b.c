/*
========================================================================================================
Name : 23.c
Author : Prasanna Kumar M
Description : Write a program to communicate between two machines using socket.
Date: 30 Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1" 
#define BUFFER_SIZE 1024


int main() {
    int sock = 0;
    ssize_t valread;
    struct sockaddr_in serv_addr;
    const char *client_message = "Hello from the client! ";
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return EXIT_FAILURE;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        close(sock);
        return EXIT_FAILURE;
    }

    printf("Attempting to connect to server at %s:%d.\n", SERVER_IP, PORT);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        close(sock);
        return EXIT_FAILURE;
    }
    printf("Connected successfully.\n");

    printf("Sending message: %s\n", client_message);
    send(sock, client_message, strlen(client_message), 0);

    printf("Waiting for server reply...\n");
    valread = read(sock, buffer, BUFFER_SIZE - 1);
    
    if (valread > 0) {
        buffer[valread] = '\0';
        printf("\nRESPONSE \n");
        printf("Server reply received: %s\n", buffer);
        printf("\n");
    } else if (valread == 0) {
        printf("Server closed connection.\n");
    } else {
        perror("read failed");
    }

    close(sock);
    printf("Client finished.\n");

    return EXIT_SUCCESS;
}

/*

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 33b.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Attempting to connect to server at 127.0.0.1:8080.
Connected successfully.
Sending message: Hello from the client! 
Waiting for server reply...

RESPONSE 
Server reply received: Message Received Sending Response

Client finished.


*/
