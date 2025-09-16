
/*
============================================================================
Name : 7.c
Author : Prasanna Kumar M
Description : Program to copy file1 into file2 ($cp file1 file2).
Date: 31st Aug, 2025.
============================================================================
*/
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int n, fd1, fd2;
    char array[100];
    fd1 = open("7_sample_1.txt", O_RDONLY);
    fd2 = open("7_sample_2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while ((n = read(fd1,array, sizeof(array))) > 0) {
        write(fd2,array,n);
    }
    close(fd1);
    close(fd2);
}

/*
Output:Copies data from 7_sample_1.txt to 7_sample_2.txt;
*/
