/*
============================================================================
Name : 25.c
Author : Prasanna Kumar M
Description : Program to create three child processes. The parent should wait for a particular child (use
waitpid system call).
Date: 3rd Sep, 2025.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void){
   int i,j,k;
   
   if(!(i=fork())) sleep(1);
   
   else if(!(j=fork())){
	   sleep(3);
   }
   else if(!(k=fork())){
	   sleep(10);
   }
   else waitpid(j,NULL,0);
}
