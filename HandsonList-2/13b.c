/*
========================================================================================================
Name : 13b.c
Author : Prasanna Kumar M
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.
Date: 19 Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    int pid;
    printf("Enter pid of process to stop\n");
    scanf("%d", &pid);

    printf("Sending SIGSTOP signal to process: %d\n", pid);
    kill(pid, SIGSTOP);

    printf("SIGSTOP signal sent\n");
 
    return (0);
}
/*
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 13b.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Enter pid of process to stop
6866
Sending SIGSTOP signal to process: 6866
SIGSTOP signal sent

*/
