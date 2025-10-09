/*
=====================================================================================================================================
Name : 12.c
Author : Prasanna Kumar M
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to the parent process from the child process.
Date: 19 Sept, 2025.
=====================================================================================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    
    if (!fork())
    {
        sleep(5);
        printf("Child process pid: %d\n", getpid());
        kill(getppid(), SIGKILL);
        printf("Parent process killed\n");
        sleep(10);
    }
    else
    {
        printf("Process id of Parent: %d\n", getpid());
        sleep(15);
    }

    return 0;
}
/*
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 12.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Process id of Parent: 6616
Child process pid: 6617
Parent process killed
Killed

*/
