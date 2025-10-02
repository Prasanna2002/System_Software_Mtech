/*
========================================================================================================
Name : 9.c
Author : Prasanna Kumar M
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - Use signal system call.
Date: 19 Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigintHandler(int signal) {
    printf("SIGINT is ignored for now...\n");
}

int main() {
    signal(SIGINT, SIG_IGN);
    printf("SIGINT is ignored. Please wait for 10 seconds \n");
    sleep(5);
    printf("Now resetting SIGINT. Press Ctrl+C to terminate.\n");
    signal(SIGINT, SIG_DFL);

    sleep(5);

} 

/*
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 9.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
SIGINT is ignored. Please wait for 10 seconds 
Now resetting SIGINT. Press Ctrl+C to terminate.
^C
*/

