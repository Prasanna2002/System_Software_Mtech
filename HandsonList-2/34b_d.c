/*
========================================================================================================
Name : 34b.c
Author : Prasanna Kumar M
Description : Write a program to create a concurrent server.
              a. use fork
              b. use pthread_create
Date: 25 Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" 
#define PORT 8080

int main(int argc, char *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char *message = "Hello, Concurrent Server! This is Client Process.";
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        close(sock);
        return -1;
    }

    printf("Client Initializing \n");
    printf("Attempting to connect to %s:%d...\n", SERVER_IP, PORT);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return -1;
    }

    printf("Successfully connected.\n");

    send(sock, message, strlen(message), 0);
    printf("Message sent: '%s'\n", message);

    printf("Waiting for server response...\n");
    if (recv(sock, buffer, 1024, 0) > 0) {
        printf("Server response: %s\n", buffer);
    } else {
        printf("Did not receive a response from the server.\n");
    }

    close(sock);
    printf("Connection closed. Client exiting.\n");

    return 0;
}



