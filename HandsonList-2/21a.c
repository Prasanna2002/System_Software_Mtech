/*
========================================================================================================
Name : 21a.c
Author : Prasanna Kumar M
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 23 Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define FIFO_REQ "fifo_req_21" 
#define FIFO_RESP "fifo_resp_21" 
#define MAX_MSG_SIZE 256

int main() {
    int fd_req, fd_resp;
    char request_buffer[MAX_MSG_SIZE];
    ssize_t bytes_read, bytes_written;

    printf("--- Two-Way FIFO Server (Processing Unit) -\n");
    printf("Waiting for Client to open Request channel (%s).\n", FIFO_REQ);
    fd_req = open(FIFO_REQ, O_RDONLY);
    if (fd_req == -1) { 
        perror("Read Failed:"); 
        return EXIT_FAILURE; 
    }
    
    printf("Request channel opened. Waiting for Client to open Response channel (%s).\n", FIFO_RESP);
    fd_resp = open(FIFO_RESP, O_WRONLY);
    
    if (fd_resp == -1) { 
        perror("open WRITE failed"); 
        close(fd_req); 
        return EXIT_FAILURE; 
    }
    printf("Both channels successfully opened. Waiting for request.\n");

    bytes_read = read(fd_req, request_buffer, sizeof(request_buffer) - 1);
    
    if (bytes_read > 0) 
    {
        request_buffer[bytes_read] = '\0';
        printf("\nREQUEST RECEIVED %zd bytes: '%s'\n", bytes_read, request_buffer);

        bytes_written = write(fd_resp, request_buffer, bytes_read);
        
        if (bytes_written == -1) {
            perror("write response failed");
        } 
        else {
            printf("[RESPONSE SENT] %zd bytes: '%s' via %s.\n", bytes_written, request_buffer, FIFO_RESP);
        }

    } 
    else if (bytes_read == 0) {
        printf("Client closed the pipe (End of File). Nothing to read.\n");
    } 
    else 
    {
        perror("read failed");
    }

    close(fd_req);
    close(fd_resp);
    printf("\nServer finished and closed both FIFOs.\n");

    return EXIT_SUCCESS;
}

/*

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 21a.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
--- Two-Way FIFO Server (Processing Unit) -
Waiting for Client to open Request channel (fifo_req_21).
Request channel opened. Waiting for Client to open Response channel (fifo_resp_21).
Both channels successfully opened. Waiting for request.

REQUEST RECEIVED 6 bytes: 'Hello'
[RESPONSE SENT] 6 bytes: 'Hello' via fifo_resp_21.

Server finished and closed both FIFOs.



*/
