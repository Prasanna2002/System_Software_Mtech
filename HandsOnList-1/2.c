/*
============================================================================
Name : 2.c
Author : Prasanna Kumar M
Description : Program to execute in an infinite loop at the background. Go to /proc directory and identify all the process related information in the corresponding proc directory.
Date: 30th Aug, 2025.
============================================================================
*/
#include<stdio.h> 
#include<unistd.h> 

int main(){
printf("My Pid is : %d\n",getpid());
	while(1);
	return 0;
}

/* OUTPUT 
My Pid is : 12925

