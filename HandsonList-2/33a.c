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
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    ssize_t valread;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello_message = "Message Received Sending Response";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return EXIT_FAILURE;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT); 

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        return EXIT_FAILURE;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        return EXIT_FAILURE;
    }

    printf("Server listening on port %d.\n", PORT);

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
        perror("accept failed");
        close(server_fd);
        return EXIT_FAILURE;
    }

    printf("Connection accepted. Communicating with client.\n");

    valread = read(new_socket, buffer, BUFFER_SIZE - 1);
    if (valread > 0) {
        buffer[valread] = '\0';
        printf("Client message received: %s\n", buffer);
    } else if (valread == 0) {
        printf("Client disconnected gracefully.\n");
    } else {
        perror("read failed");
    }

    printf("Sending reply: %s\n", hello_message);
    send(new_socket, hello_message, strlen(hello_message), 0);
    
    close(new_socket);
    close(server_fd);
    printf("Connection closed. Server finished.\n");

    return EXIT_SUCCESS;
}

/*

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 33a.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Server listening on port 8080.
Connection accepted. Communicating with client.
Client message received: Hello from the client! 
Sending reply: Message Received Sending Response
Connection closed. Server finished.

*/
