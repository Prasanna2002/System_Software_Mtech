/*
========================================================================================================
Name : 10.c
Author : Prasanna Kumar M
Description : Write a separate program using sigaction system call to catch the following signals.
		a. SIGSEGV
		b. SIGINT
		c. SIGFPE
Date: 18 Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int sig) {
    switch(sig) {
        case SIGSEGV:
            printf("\nCaught signal SIGSEGV (Segmentation Fault)\n");
            exit(1);
            break;
        case SIGINT:
            printf("\nCaught signal SIGINT (Interrupt from keyboard)\n");
            exit(0);
            break;
        case SIGFPE:
            printf("\nCaught signal SIGFPE (Floating-point exception)\n");
            exit(1);
            break;
        default:
            printf("\nCaught unexpected signal: %d\n", sig);
            exit(1);
    }
}

int main() {
    struct sigaction sa;

    sa.sa_handler = signal_handler;
    sa.sa_flags = 0; 
    sigemptyset(&sa.sa_mask);

    int a = sigaction(SIGSEGV, &sa, NULL);
    int b =  sigaction(SIGINT, &sa, NULL);
    int c = sigaction(SIGFPE, &sa, NULL);
   
    printf("%d",a);
    printf("%d",b);
    printf("%d\n",c);
   
    while (1) {
        printf("Press Ctrl + C to trigger SIGINT.\n");
        sleep(1);
    }

    return 0;
}


/*
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 10.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
000
Press Ctrl + C to trigger SIGINT.
Press Ctrl + C to trigger SIGINT.
Press Ctrl + C to trigger SIGINT.
Press Ctrl + C to trigger SIGINT.
^C
Caught signal SIGINT (Interrupt from keyboard)
*/
