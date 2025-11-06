/*
========================================================================================================
Name : 21b.c
Author : Prasanna Kumar M
Description :Write two programs so that both can communicate by FIFO -Use two way communications.
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
    int fd_req = 0, fd_resp = 0; 
    char request_buffer[MAX_MSG_SIZE];
    char response_buffer[MAX_MSG_SIZE];
    ssize_t bytes_written, bytes_read;

    printf("Two-Way FIFO Client \n");

    if ((mkfifo(FIFO_REQ, 0666) == -1 && errno != EEXIST) ||  (mkfifo(FIFO_RESP, 0666) == -1 && errno != EEXIST)) {
        perror("mkfifo failed");
        return EXIT_FAILURE;
    }
    
    printf("Created/Ensured both request and response FIFOs exist.\n");
    
    printf("\nWaiting for Server to open channels...\n");
    fd_req = open(FIFO_REQ, O_WRONLY);
    
    if (fd_req == -1) { 
        perror("open WRITE failed"); 
        return EXIT_FAILURE;
    }
  
    fd_resp = open(FIFO_RESP, O_RDONLY);
    if (fd_resp == -1) { 
        perror("open READ failed");
        return EXIT_FAILURE;
    }
    
    printf("Successfully opened both channels. Ready to communicate.\n");

    printf("\nEnter message to send to Server :\n ");
    if (fgets(request_buffer, MAX_MSG_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
    }
    
    size_t len = strlen(request_buffer);
    
    if (len > 0 && request_buffer[len - 1] == '\n') {
        request_buffer[len - 1] = '\0';
        len--;
    }

    bytes_written = write(fd_req, request_buffer, len + 1);
    if (bytes_written == -1) { 
        perror("write failed"); 
        return EXIT_FAILURE;
    }
    
    printf("Sent %zd bytes to Server via %s.\n", bytes_written, FIFO_REQ);

    printf("Waiting for Server's response.\n");
    bytes_read = read(fd_resp, response_buffer, sizeof(response_buffer) - 1);
    
    if (bytes_read > 0) {
        response_buffer[bytes_read] = '\0';
        printf("\n----------------------------------------\n");
        printf("RECEIVED RESPONSE: %s\n", response_buffer);
        printf("Bytes Read: %zd\n", bytes_read);
        printf("----------------------------------------\n");
    } 
    else if (bytes_read == 0) {
        printf("Server closed the pipe (End of File). Nothing to read.\n");
    } 
    else {
        perror("read failed");
        return EXIT_FAILURE;
    }

    if (fd_req > 0) close(fd_req);
    if (fd_resp > 0) close(fd_resp);
    
    if (unlink(FIFO_REQ) == -1) {
        perror("unlink FIFO_REQ failed");
    }
    
    if (unlink(FIFO_RESP) == -1) {
        perror("unlink FIFO_RESP failed");
    }
    printf("\nFIFOs removed. Client finished.\n");

    return EXIT_SUCCESS;

}

/*

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 21b.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out

Two-Way FIFO Client 
Created/Ensured both request and response FIFOs exist.

Waiting for Server to open channels...
Successfully opened both channels. Ready to communicate.

Enter message to send to Server :
 Hello
Sent 6 bytes to Server via fifo_req_21.
Waiting for Server's response.

----------------------------------------
RECEIVED RESPONSE: Hello
Bytes Read: 6
----------------------------------------

FIFOs removed. Client finished.



*/
