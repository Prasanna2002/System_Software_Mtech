/*
============================================================================
Name : 21.c
Author : Prasanna Kumar M
Description :Program, call fork and print the parent and child process id.
Date: 3rd Sep, 2025.
============================================================================
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
int main()
{
    printf("Id of parent process is = %d\n", getpid());
    int a = fork();
    if(a) 
    {
      printf("Id of child process is = %d\n", a); 
    }
    return 0;
}
/*
Id of parent process is = 80756
Id of child process is = 80757
*/
