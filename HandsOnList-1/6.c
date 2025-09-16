/*
============================================================================
Name : 6.c
Author : Prasanna Kumar M
Description : Program to take input from STDIN and display on STDOUT. Use only read/write system calls
Date: 31st Aug, 2025
============================================================================
*/

#include <unistd.h>	
#include <stdio.h>	

int main(){
	char *buffer[100];
	int readByte,writeByte;
	while(1){
		readByte = read(STDIN_FILENO,buffer,1);
		writeByte = write(STDOUT_FILENO,buffer,1);
		
		printf("\nreadByte : \n%d\n",readByte); 
		printf("\nWriteByte%d\n",writeByte);
		if(readByte == -1 || writeByte == -1){
			perror("Error while reading from STDIN / writing to STDOUT\n");
			return 0;
		}
	}	
	return 0;
}
/*
./a.out 
This
This
Me
Me
Working
Working
*/
