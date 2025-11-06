/*
========================================================================================================
Name : 30.c
Author : Prasanna Kumar M
Description :  32. Write a program to implement semaphore to protect any critical section.
                    a. write some data to the shared memory
                    b. attach with O_RDONLY and check whether you are able to overwrite.
                    c. detach the shared memory
                    d. remove the shared memory
Date: 27 Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

#define SHM_KEY 0x1234
#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shm_ptr_rw = NULL; 
    char *shm_ptr_ro = NULL; 
    const char *message = "Hello, This is Me Who is Typing This";

    printf("Creating Shared Memory Segment\n");
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        return EXIT_FAILURE;
    }
    printf("Shared Memory ID: %d created successfully.\n\n", shmid);

    printf("Attaching with Read/Write (default) and writing data \n");
    shm_ptr_rw = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr_rw == (char *)-1) {
        perror("shmat R/W failed");
        return EXIT_FAILURE;
    }
    strncpy(shm_ptr_rw, message, SHM_SIZE);
    printf("Wrote: '%s'\n", message);
    
    printf("\nDetaching the Read/Write segment \n");
    if (shmdt(shm_ptr_rw) == -1) {
        perror("shmdt (R/W) failed");
    } else {
        printf("Detached R/W segment successfully.\n");
    }

    printf("\nAttaching with Read-Only \n");
    shm_ptr_ro = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (shm_ptr_ro == (char *)-1) {
        perror("shmat (R/O) failed");
        return EXIT_FAILURE;
    }

    printf("Successfully read data: '%s'\n", shm_ptr_ro);
    
    printf("\nAttempting to overwrite data :\n");
    
    pid_t pid = fork();
    int status;
    const char *attempt_write_msg = "Hello, Overwriting the Shared Memory";

    if (pid < 0) {
        perror("fork failed during R/O test");
        return EXIT_FAILURE;
    } 
    
    if (pid == 0) {
    
        strncpy(shm_ptr_ro, attempt_write_msg, strlen(attempt_write_msg));
        shmdt(shm_ptr_ro);
        exit(EXIT_FAILURE); 
    }
    
    printf("Message After Trying to Overwrite.\n");
    printf("Wrote: '%s'\n", message);
    
    printf("\nDetaching the Read-Only segment \n");
    if (shmdt(shm_ptr_ro) == -1) {
        perror("shmdt (R/O) failed");
    } else {
        printf("Detached R/O segment successfully.\n");
    }

    printf("\n Removing Shared Memory Segment \n");
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl (IPC_RMID) failed");
        return EXIT_FAILURE;
    }
    printf("Shared Memory ID: %d successfully marked for removal.\n", shmid);

    return EXIT_SUCCESS;
}

/*

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 30.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Creating Shared Memory Segment
Shared Memory ID: 9 created successfully.

Attaching with Read/Write (default) and writing data 
Wrote: 'Hello, This is Me Who is Typing This'

Detaching the Read/Write segment 
Detached R/W segment successfully.

Attaching with Read-Only 
Successfully read data: 'Hello, This is Me Who is Typing This'

Attempting to overwrite data :
Message After Trying to Overwrite.
Wrote: 'Hello, This is Me Who is Typing This'

Detaching the Read-Only segment 
Detached R/O segment successfully.

 Removing Shared Memory Segment 
Shared Memory ID: 9 successfully marked for removal.

*/
