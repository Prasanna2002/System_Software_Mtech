/*
============================================================================
Name : 23.c
Author : Prasanna Kumar M
Description :Program to create a Zombie state of the running program.
Date: 3rd Sep, 2025.
============================================================================
*/
#include <stdlib.h> 
#include<stdio.h>
#include <sys/types.h> 
#include <unistd.h>

int main() 
{ 
	
	pid_t pidChild = fork(); 

	 
	if (pidChild > 0) {
	   sleep(50);
	   printf("inside parent pid= %d\n", getpid());
           printf("child pid= %d\n", pidChild);
	}
	 
	else{	
	   printf("inside child pid= %d\n", getpid());
           printf("parent id= %d\n", getppid());
	   exit(0); 
            }       
	return 0; 
} 
/*
Output:
inside child pid= 8318
parent id= 8317
*/

