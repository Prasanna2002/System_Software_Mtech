/*
============================================================================
Name : 11.c
Author : Prasanna Kumar M
Description : Program to open a file, duplicate the file descriptor and append the file with both the
              descriptors and check whether the file is updated properly or not.
              a. use dup b. use dup2 c. use fcntl
Date: 1st Sep, 2025.
============================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(){
        int fd1 = open("sample.txt", O_WRONLY);
	int fd2 = dup(fd1);
	char f1[] = "dup()\n";
	write(fd2,&f1,sizeof(f1));
        int fd3 = dup2(fd1, 100);
        char f2[] = "dup2()\n";
	write(fd3,&f2,sizeof(f2));
        int fd4 = fcntl(fd1, F_DUPFD, 0);
        char f3[] = "fcntl()\n";
	write(fd4,&f3,sizeof(f3));
        

	
	return 0;
}
