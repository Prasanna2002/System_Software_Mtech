/*
============================================================================
Name : 22.c
Author : Prasanna Kumar M
Description :Program, open a file, call fork, and then write to the file by both the child as well as the
             parent processes. Check output of the file.
Date: 3rd Sep, 2025.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
    int fd = open("out.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    fork();
    char buf[64];
    int n = sprintf(buf, "written by process %d\n", getpid());
    write(fd, buf, n);
    close(fd);
    return 0;
}
/*
written by process 16509
written by process 16510
*/
