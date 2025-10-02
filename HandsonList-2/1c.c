/*
========================================================================================================
Name : 1c.c
Author : Prasanna Kumar M
Description : 1. Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
              a. ITIMER_REAL    
              b. ITIMER_VIRTUAL
              c. ITIMER_PROF
Date: 27 Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

#define SECONDS 10
#define MICROSECONDS 10

void timer_handler(int signum) {
    static int count = 0;
    printf("\nSignal %d received. Timer expired %d times.\n", signum, ++count);
}

int main() {
    struct itimerval it_val;

    printf("--- ITIMER_PROF Demo---\n");

    if (signal(SIGPROF, timer_handler) == SIG_ERR) {
        perror("signal error");
        return EXIT_FAILURE;
    }

    it_val.it_interval.tv_sec = SECONDS;
    it_val.it_interval.tv_usec = MICROSECONDS;


    it_val.it_value.tv_sec = SECONDS;
    it_val.it_value.tv_usec = MICROSECONDS;

    if (setitimer(ITIMER_PROF, &it_val, NULL) == -1) {
        perror("setitimer error");
        return EXIT_FAILURE;
    }

    printf("Timer set for %d seconds and %d microseconds of total CPU time.\n", SECONDS, MICROSECONDS);

    while (1) {
        for (long i = 0; i < 10000000; i++) {
            
        }
        usleep(100); 
    }

    return EXIT_SUCCESS;
}

/*

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 1c.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
ITIMER_PROF
Timer set for 10 seconds and 10 microseconds of total CPU time.

Signal 27 received. Timer expired 1 times.

Signal 27 received. Timer expired 2 times.

Signal 27 received. Timer expired 3 times.

*/
