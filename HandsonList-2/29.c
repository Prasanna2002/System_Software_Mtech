
/*
========================================================================================================
Name : 29.c
Author : Prasanna Kumar M
Description : Write a program to remove the message queue.
Date: 26 Sept, 2025.
========================================================================================================
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main()
{
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, 0);

    int a = msgctl(msqid, IPC_RMID, NULL);
    if(a!=-1){
      printf("Deletion Successful\n");
    }
    
    return (0);
}
/*
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out  
Deletion Successful
*/
