/*
============================================================================
Name : 1b.c
Author : Prasanna Kumar M
Description : Program to create a hard link file using the `link` system call
Date: 30th Aug, 2025.
============================================================================
*/

#include<unistd.h>	
#include<stdio.h>	

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Enter target and source file Name\n");
		return 0;
	}
	const char *source = argv[1];
	const char *target = argv[2];
	
	int status = link(source,target);

	if(status == -1){
		perror("Error while creating head link\n");	
	}else{
		printf("Hard Link created successfully\n");
	}
}

/*
./a.out source.txt hardLink 
Hard Link created successfully


*/
