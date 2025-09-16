/*
============================================================================
Name : 5.c
Author : Prasanna Kumar M
Description : Program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.
Date: 31st Aug, 2025.
============================================================================
*/

#include <sys/types.h>	
#include <sys/stat.h>	
#include <fcntl.h>	
#include <stdio.h>	
#include <unistd.h>

int main(){
	while(1){
		int fd1 = creat("5_sample_1.txt",S_IRWXU);
		int fd2 = creat("5_sample_2.txt",S_IRWXU);
		int fd3 = creat("5_sample_3.txt",S_IRWXU);
		int fd4 = creat("5_sample_4.txt",S_IRWXU);
		int fd5 = creat("5_sample_5.txt",S_IRWXU);

		printf("%d %d %d %d %d\n",fd1,fd2,fd3,fd4,fd5);
		close(fd1);
		close(fd2);
		close(fd3);
		close(fd4);
		close(fd5);
		sleep(5);
	}
}

/* Output
3 4 5 6 7
3 4 5 6 7
3 4 5 6 7
3 4 5 6 7
*/
