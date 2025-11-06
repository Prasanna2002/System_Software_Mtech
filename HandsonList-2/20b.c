/*
========================================================================================================
Name : 20b.c
Author : Prasanna Kumar M
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 22 Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#define path "fifo_20"


extern int errno;

int main() {
    int fd;
    char buffer[256];
    ssize_t bytes_read;

    printf("Opening FIFO for reading\n");

    fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open failed: Make sure the FIFO writer program has run first.");
        return EXIT_FAILURE;
    }
    printf("FIFO opened successfully. Waiting for data...\n");

    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    
    if (bytes_read == -1) {
        perror("read failed");
        close(fd);
        return EXIT_FAILURE;
    }

    buffer[bytes_read] = '\0';

    printf("\nReceived Message: %s\n", buffer);
    printf("Bytes Read: %zd\n", bytes_read);
    close(fd);

    if (unlink(path) == -1) {
        perror("unlink failed (FIFO removal)");
    } else {
        printf("FIFO removed successfully. Communication complete.\n");
    }

    return EXIT_SUCCESS;
}

/*

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 20b.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Opening FIFO for reading
open failed: Make sure the FIFO writer program has run first.: No such file or directory
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 20b.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Opening FIFO for reading
FIFO opened successfully. Waiting for data.

Received Message: Hello This is Me
Bytes Read: 17

FIFO removed successfully. Communication complete.

*/
