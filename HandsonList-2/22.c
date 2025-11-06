/*
==========================================================================================================================
Name : 23.c
Author : Prasanna Kumar M
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 23 Sept, 2025.
=========================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define path "/tmp/myfifo"

int main() {
    if (mkfifo(path, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo failed");
        exit(EXIT_FAILURE);
    }

    int fd = open(path, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);

    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for data in FIFO for 10 seconds.\n");
    int result = select(fd + 1, &read_fds, NULL, NULL, &timeout);

    if (result == -1) {
        perror("select failed");
        close(fd);
        exit(EXIT_FAILURE);
    } 
    
    else if (result == 0) {
        printf("Timeout: No data received within 10 seconds\n");
    } 
    else if (FD_ISSET(fd, &read_fds)) {
        char buffer[256];
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("Received data: %s\n", buffer);
        } 
        else if (bytes_read == 0) {
            printf("FIFO closed by writer\n");
        }
        else {
            perror("read failed");
        }
    }

    close(fd);
    unlink(path);
    return 0;
} 

/*
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 22.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Waiting for data in FIFO for 10 seconds.
Timeout: No data received within 10 seconds
---------------------------------------------------------------------------------------------------------------------
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ echo "Hello,World" > /tmp/myfifo
--------------------------------------------------------------------------------------------------------------------- 
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 22.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Waiting for data in FIFO for 10 seconds.
Received data: Hello,World



*/


