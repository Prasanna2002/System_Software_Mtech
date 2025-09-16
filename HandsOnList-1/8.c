
/*
============================================================================
Name : 8.c
Author : Prasanna Kumar M
Description : Write a program to open a file in read only mode, read line by line and display each line as it is read.
              Close the file when end of file is reached.
Date: 31st Aug, 2025.
============================================================================
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    int fd;
    char array[200];
    int x;
    const char *st = "this is question 8 of hands on list 1";

    fd = creat("8_sample.txt", 0644);
    write(fd, st, strlen(st));
    close(fd);
    fd = open("8_sample.txt", O_RDONLY);
    while ((x = read(fd, array, sizeof(array) - 1)) > 0) {
        array[x] = '\0';
        printf("%s",array);
    }

    close(fd);
    return 0;
}
/*
Output:this is question 8 of hands on list 1
*/
