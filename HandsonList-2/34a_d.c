/*
========================================================================================================
Name : 34a.c
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
#include <sys/wait.h> 

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 1 

void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_received;

    printf("\nHandling new client connection.\n");

    bytes_received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Received message: '%s'\n", buffer);
        
        const char *response = "Server received your message!";
        send(client_sock, response, strlen(response), 0);
    } else if (bytes_received == 0) {
        printf("Client disconnected.\n");
    } else {
        perror("recv failed");
    }

    close(client_sock);
    printf("Connection closed and child process exiting.\n");
    exit(EXIT_SUCCESS);
}

void reap_children() {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    pid_t child_pid;

    printf("Concurrent Fork Server Initializing \n");
    printf("Listening on port %d\n", PORT);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening for connections...\n");
    while (1) {
        if ((client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue; 
        }

        char *client_ip = inet_ntoa(address.sin_addr);
        printf("\nConnection accepted from %s.\n",client_ip);

        child_pid = fork();

        if (child_pid == -1) {
            perror("fork failed");
            close(client_sock);
        } 
        else if (child_pid == 0) {
            close(server_fd); 
            handle_client(client_sock);
        } 
        else {
            close(client_sock); 
            printf("Forked child %d to handle request.\n",child_pid);
            reap_children();
        }
    }
    
    close(server_fd);
    return 0;
}

/*

Client  Request

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ gcc 34b.c -o client
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./client
Client Initializing 
Attempting to connect to 127.0.0.1:8080...
Successfully connected.
Message sent: 'Hello, Concurrent Server! This is Client Process.'
Waiting for server response...
Server response: Server received your message!
Connection closed. Client exiting.

========================================================================================================

Server Response

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ gcc 34a.c -o server
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./server
Concurrent Fork Server Initializing 
Listening on port 8080
Server listening for connections...

Connection accepted from 127.0.0.1.
Forked child 12272 to handle request.

Handling new client connection.
Received message: 'Hello, Concurrent Server! This is Client Process.'
Connection closed and child process exiting.

*/
