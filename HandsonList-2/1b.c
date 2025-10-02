/*
========================================================================================================
Name : 1b.c
Author : Prasanna Kumar M
Description : 1. Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
              a. ITIMER_REAL    
              b. ITIMER_VIRTUAL
              c. ITIMER_PROF
Date: 12 Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

void timer_handler(int signum) {
    static int count = 0;
    printf("\nSignal %d received. Timer expired %d times.\n", signum, ++count);
}


int main() {
    struct itimerval it_val;

    printf("ITIMER_VIRTUAL\n");


    if (signal(SIGVTALRM, timer_handler) == SIG_ERR) {
        perror("signal error");
        return EXIT_FAILURE;
    }

    it_val.it_interval.tv_sec = 10;
    it_val.it_interval.tv_usec = 10;

    it_val.it_value.tv_sec = 10;
    it_val.it_value.tv_usec = 10;

    if (setitimer(ITIMER_VIRTUAL, &it_val, NULL) == -1) {
        perror("setitimer error");
        return EXIT_FAILURE;
    }

    printf("Timer set for %d seconds and %d microseconds of user CPU time.\n", 10, 10);

    while (1) {
        for (long i = 0; i < 10000000; i++) {
        }
        usleep(1000); 
    }

    return EXIT_SUCCESS;
}

/*

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 1b.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
ITIMER_VIRTUAL 
Timer set for 10 seconds and 10 microseconds of user CPU time.

Signal 26 received. Timer expired 1 times.

Signal 26 received. Timer expired 2 times.

Signal 26 received. Timer expired 3 times.

Signal 26 received. Timer expired 4 times.

*/
