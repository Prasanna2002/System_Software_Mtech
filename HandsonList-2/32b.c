/*
========================================================================================================
Name : 32b.c
Author : Prasanna Kumar M
Description : Write a program to implement semaphore to protect any critical section.
              a. rewrite the ticket number creation program using semaphore
              b. protect shared memory from concurrent write access
              c. protect multiple pseudo resources ( may be two) using counting semaphore
              d. remove the created semaphore
Date: 29 Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>

#define SHM_KEY 12345       
#define NUM_PROCESSES 5    
#define NUM_WRITES 10    

typedef struct {
    sem_t semaphore; 
    int counter;     
} SharedData;


void worker_process(SharedData *shm_ptr, int proc_id) {
    int i;
    printf("%d Worker started, attempting to perform %d writes...\n", proc_id, NUM_WRITES);

    for (i = 0; i < NUM_WRITES; i++) {
        if (sem_wait(&shm_ptr->semaphore) == -1) {
            perror("sem_wait failed");
            exit(EXIT_FAILURE);
        }

        int temp = shm_ptr->counter; 
        temp = temp + 1;
        shm_ptr->counter = temp;
        
        if (sem_post(&shm_ptr->semaphore) == -1) {
            perror("sem_post failed");
            exit(EXIT_FAILURE);
        }
    }

    printf("Process %d Finished %d writes. Final counter value: %d\n", proc_id, NUM_WRITES, shm_ptr->counter);
    
    if (shmdt(shm_ptr) == -1) {
        perror("[Process] shmdt failed");
    }
    exit(EXIT_SUCCESS);
}

int main() {
    int shm_id;
    SharedData *shm_ptr;
    pid_t pid;
    int expected_result = NUM_PROCESSES * NUM_WRITES;

    printf("Shared Memory/Semaphore Demonstration\n");
    printf("Expected final counter value: %d processes * %d writes = %d\n", NUM_PROCESSES, NUM_WRITES, expected_result);

    shm_id = shmget(SHM_KEY, sizeof(SharedData), 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    shm_ptr = (SharedData *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (void *)-1) {
        perror("shmat failed");
        if (shmctl(shm_id, IPC_RMID, NULL) == -1) perror("cleanup shmctl failed");
        exit(EXIT_FAILURE);
    }

    shm_ptr->counter = 0; 
    if (sem_init(&shm_ptr->semaphore, 1, 1) == -1) {
        perror("sem_init failed");
        if (shmdt(shm_ptr) == -1) perror("cleanup shmdt failed");
        if (shmctl(shm_id, IPC_RMID, NULL) == -1) perror("cleanup shmctl failed");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore and Shared Counter initialized.\n");

    for (int i = 1; i <= NUM_PROCESSES; i++) {
        pid = fork();
        
        if (pid < 0) {
            perror("fork failed");
            break; 
        } else if (pid == 0) {
            worker_process(shm_ptr, i);
        }
    }
    int status;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        wait(&status);
    }
    printf("\n All worker processes have finished.\n");
    
    printf("[Parent] Final result from shared counter: %d\n", shm_ptr->counter);
    if (shm_ptr->counter == expected_result) {
        printf("[Parent] SUCCESS: The final result matches the expected result (%d).\n", expected_result);
    } 
    else {
        printf("Race condition likely occurred despite protection (result was %d, expected %d).\n", shm_ptr->counter, expected_result);
    }


    if (sem_destroy(&shm_ptr->semaphore) == -1) {
        perror("[Parent] sem_destroy failed");
    }

    if (shmdt(shm_ptr) == -1) {
        perror("[Parent] shmdt failed");
    }

    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("[Parent] shmctl(IPC_RMID) failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/*

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 32b.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Shared Memory/Semaphore Demonstration
Expected final counter value: 5 processes * 10 writes = 50
Semaphore and Shared Counter initialized.
1 Worker started, attempting to perform 10 writes...
Process 1 Finished 10 writes. Final counter value: 10
2 Worker started, attempting to perform 10 writes...
Process 2 Finished 10 writes. Final counter value: 20
3 Worker started, attempting to perform 10 writes...
Process 3 Finished 10 writes. Final counter value: 30
4 Worker started, attempting to perform 10 writes...
Process 4 Finished 10 writes. Final counter value: 40
5 Worker started, attempting to perform 10 writes...
Process 5 Finished 10 writes. Final counter value: 50

 All worker processes have finished.
[Parent] Final result from shared counter: 50
[Parent] SUCCESS: The final result matches the expected result (50).

*/
