/*
============================================================================
Name : 30.c
Author : Prasanna Kumar M
Description :Write a program to run a script at a specific time using a Daemon process.
Date: 6th Sep, 2025.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>

int main() {
    
    pid_t process_id;
    process_id = fork();
    if (process_id < 0) {
        exit(EXIT_FAILURE);
    }
    if (process_id> 0) {
        exit(EXIT_SUCCESS);
    }
    umask(0);
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    openlog("daemon-log", LOG_PID, LOG_DAEMON);
    while (1) {
        syslog(LOG_NOTICE, "Daemon is running...");
        sleep(5);
    }
    closelog();

    return EXIT_SUCCESS;
}
