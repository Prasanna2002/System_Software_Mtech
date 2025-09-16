/*
============================================================================
Name : 3.c
Author : Prasanna Kumar M
Description : Program to create a file and print the file descriptor value. Use creat() system call
Date: 30th Aug, 2025.
============================================================================
*/

//#include<sys/types.h>
#include<sys/stat.h>	
#include<fcntl.h> //---> Provides all definitions related to how the file can be accessed,managed and shared like O_RDONLY,O_CREAT,O_RDWD,O_TRUNC,O_APPEND etc...		
#include<stdio.h>		

int main(int argc, char *argv[]){
	if(argc != 2){
		perror("Enter File Name in argument\n");
		return 0;
	}
	
	const char *fileName = argv[1];
	int fd = creat(fileName,S_IRWXU);

	if(fd == -1){
		perror("Error while creating a file\n");
	}else{
		printf("The file have been successfully create and the file descriptor value is: %d\n",fd);
	}
	return 0;
}

/*
./a.out 3_sample
The file have been successfully create and the file descriptor value is: 3
*/
