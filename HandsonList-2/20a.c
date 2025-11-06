/*
========================================================================================================
Name : 20a.c
Author : Prasanna Kumar M
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 22 Sept, 2025.
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

#define path "fifo_20"
#define size 256


int main() {
    int fd;
    char buffer[size];
    ssize_t bytes;

    if (mkfifo(path, 0666) == -1) {
        if (errno != EEXIST) {
            perror("mkfifo failed");
            return EXIT_FAILURE;
        }
    } 
    else {
        printf("FIFO '%s' created successfully.\n", path);
    }

    printf("\nEnter the message \n ");
    if (fgets(buffer, size, stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    printf("\nOpening FIFO for writing.\n");
    fd = open(path, O_WRONLY);
    if (fd == -1) {
        perror("open failed");
        return EXIT_FAILURE;
    }
    printf("FIFO opened successfully. Writing data.\n");
    bytes = write(fd, buffer, len + 1); 
    
    if (bytes == -1) {
        perror("write failed");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Successfully wrote %zd bytes to the FIFO.\n", bytes);

    close(fd);
    printf("Writer finished and closed the FIFO.\n");

    return EXIT_SUCCESS;
}

/*

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 20a.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
FIFO 'fifo_20' created successfully.

Enter the message 
 Hello This is Me

Opening FIFO for writing.
FIFO opened successfully. Writing data.
Successfully wrote 17 bytes to the FIFO.
Writer finished and closed the FIFO.

*/
