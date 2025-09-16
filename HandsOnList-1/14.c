/*
============================================================================
Name : 14.c
Author : Prasanna Kumar M
Description : Write a program to find the type of a file.
              a. Input should be taken from command line.
              b. program should be able to identify any type of a file.
Date: 2nd Sep, 2025.
============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <fcntl.h>

int main(int argv, char *argc[])
{
    struct stat status;
    int i = lstat(argc[1], &status);
    printf("The file type is:");

    switch (status.st_mode & S_IFMT)
    {
    case S_IFBLK:
        printf("block device\n");
        break;
    case S_IFCHR:
        printf("character device\n");
        break;
    case S_IFDIR:
        printf("directory\n");
        break;
    case S_IFIFO:
        printf("FIFO/pipe\n");
        break;
    case S_IFLNK:
        printf("symlink\n");
        break;
    case S_IFREG:
        printf("regular file\n");
        break;
    case S_IFSOCK:
        printf("socket\n");
        break;
    default:
        printf("unknown?\n");
        break;
    }
}
/*
Output: 
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Hands-on-list-1$ gcc Q14.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Hands-on-list-1$ ./a.out
The file type is: unknown?
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Hands-on-list-1$ ./a.out newfile.txt
The file type is: regular file
*/
