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
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 5 

void *handle_client(void *vargp) {
    int client_sock = *(int *)vargp;
    free(vargp); 

    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_received;
    pthread_detach(pthread_self());

    printf("\nHandling new client connection...\n");
    bytes_received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0'; 
        
        printf("RECEIVED MESSAGE: '%s'\n",buffer);
        
        const char *response = "Server received your message successfully!";
        send(client_sock, response, strlen(response), 0);
        printf("Sent confirmation response back to client.\n");

    } else if (bytes_received == 0) {
        printf("Client disconnected without sending data.\n");
    } else {
        perror("Message RECV failed");
    }

    close(client_sock);
    printf("Connection closed and thread exiting.\n");
    
    return NULL;
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    printf("Threaded Server\n");
    printf("Listening on port %d.\n", PORT);


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

    if (listen(server_fd, MAX_CLIENTS) < 0) {
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

        int *new_sock = (int *)malloc(sizeof(int));
        if (new_sock == NULL) {
            perror("malloc failed");
            close(client_sock);
            continue;
        }
        *new_sock = client_sock;
        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, (void *)new_sock) != 0) {
            perror("pthread_create failed");
            free(new_sock); 
            close(client_sock);
        } else {
            printf("Thread %lu created to process request.\n", (unsigned long)tid);
        }
    }
    
    close(server_fd);
    return 0;
}

/*

Client Request

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ gcc 34b.c -o pthread_client
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./pthread_client 
Client Initializing 
Attempting to connect to 127.0.0.1:8080...
Successfully connected.
Message sent: 'Hello, Concurrent Server! This is Client Process.'
Waiting for server response...
Server response: Server received your message successfully!
Connection closed. Client exiting.

========================================================================================================

Server Response

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ gcc 34c.c -o pthread_server
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./pthread_server 
Threaded Server
Listening on port 8080.
Server listening for connections...

Connection accepted from 127.0.0.1.
Thread 135083285542592 created to process request.

Handling new client connection...
RECEIVED MESSAGE: 'Hello, Concurrent Server! This is Client Process.'
Sent confirmation response back to client.
Connection closed and thread exiting.



*/
