#include <unistd.h>
/*
========================================================================================================
Name : 13a.c
Author : Prasanna Kumar M
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.
Date: 19 Sept, 2025.
========================================================================================================
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void catch_signal(int sig) {
    const char msg[] = "Signal caught — exiting\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main(void) {
    printf("pid (receiver): %d\n", (int)getpid());

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = catch_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    for (;;) {
        pause();
    }

    return 0;
}
/*
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 13a.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
pid (receiver): 6697

*/
