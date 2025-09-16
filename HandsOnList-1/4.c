/*
============================================================================
Name : 4.c
Author : Prasanna Kumar M
Description : Program to open an existing file with read write mode. Try O_EXCL flag also.
Date: 31st Aug, 2025.
============================================================================
*/

#include <sys/types.h>	
#include <sys/stat.h>	
#include <fcntl.h>	 //---> https://pubs.opengroup.org/onlinepubs/7908799/xsh/fcntl.h.html
#include <stdio.h>	

int main(int argc, char *argv[]){
	if(argc != 2){
		perror("File Name not found\n");
		return 0;
	}

	const char *fileName = argv[1];
	int fd = open(fileName,O_EXCL);

	if(fd == -1){
		perror("Error while opening the file!\n");
	}else{
		printf(" Opened file with Read and Write Mode\n");
	}
	return 0;
}

/*
./a.out 4.c 
Opened file with Read and Write Mode
*/
