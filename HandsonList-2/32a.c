/*
========================================================================================================
Name : 32a.c
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
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>      
#include <sys/stat.h>   
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 5          
#define TICKETS_PER_THREAD 5    
#define FILE_NAME "ticket.txt"
#define SEMAPHORE_NAME "/ticket_lock_sem" 

sem_t *ticket_semaphore = NULL; 

int read_ticket_count() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) return -1;

    int count = 0;
    if (fscanf(fp, "%d", &count) != 1) {
        count = 0; 
    }
    fclose(fp);
    return count;
}

void write_ticket_count(int count) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (!fp) {
        perror("Error writing to ticket file");
        return;
    }
    fprintf(fp, "%d", count);
    fclose(fp);
}

void initialize_ticket_file() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Initializing %s with count 0.\n", FILE_NAME);
        write_ticket_count(0);
    } else {
        printf("Ticket file already exists. Starting from current count: %d\n", read_ticket_count());
        fclose(fp);
    }
}

void *generate_ticket(void *arg) {
    int thread_id = *(int *)arg;
    int issued_ticket;

    for (int i = 0; i < TICKETS_PER_THREAD; i++) {
        if (sem_wait(ticket_semaphore) != 0) {
            perror("Thread failed to acquire file lock (sem_wait)");
            return NULL;
        }
        int current_count = read_ticket_count();
        if (current_count == -1) {
             fprintf(stderr, "Thread %d: Failed to read ticket count.\n", thread_id);
             sem_post(ticket_semaphore);
             return NULL;
        }

        current_count++; 
        issued_ticket = current_count; 

        write_ticket_count(issued_ticket);

        if (sem_post(ticket_semaphore) != 0) {
            perror("Thread failed to release file lock ");
        }

        printf("Thread %d Issued Ticket #%d\n", thread_id, issued_ticket);
        
        usleep(500000); 
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    printf("Accessing file: %s\n", FILE_NAME);

    sem_unlink(SEMAPHORE_NAME);
    initialize_ticket_file();
    ticket_semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, 0644, 1);
    
    if (ticket_semaphore == SEM_FAILED) {
        perror("Failed to open/create named semaphore");
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, generate_ticket, &thread_ids[i]) != 0) {
            perror("Thread creation failed");
            sem_close(ticket_semaphore);
            sem_unlink(SEMAPHORE_NAME);
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Final ticket count recorded in file: %d\n", read_ticket_count());
    if (sem_close(ticket_semaphore) != 0) {
        perror("Failed to close named semaphore");
    }
    
    if (sem_unlink(SEMAPHORE_NAME) != 0) {
        perror("Failed to unlink named semaphore");
    }

    return 0;
}

/*
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 32a.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out

Accessing file: ticket.txt
Initializing ticket.txt with count 0.
Thread 1 Issued Ticket #1
Thread 2 Issued Ticket #2
Thread 3 Issued Ticket #3
Thread 4 Issued Ticket #4
Thread 5 Issued Ticket #5
Thread 1 Issued Ticket #6
Thread 2 Issued Ticket #7
Thread 3 Issued Ticket #8
Thread 4 Issued Ticket #9
Thread 5 Issued Ticket #10
Thread 1 Issued Ticket #11
Thread 2 Issued Ticket #12
Thread 3 Issued Ticket #13
Thread 4 Issued Ticket #14
Thread 5 Issued Ticket #15
Thread 1 Issued Ticket #16
Thread 2 Issued Ticket #17
Thread 3 Issued Ticket #18
Thread 4 Issued Ticket #19
Thread 5 Issued Ticket #20
Thread 1 Issued Ticket #21
Thread 3 Issued Ticket #22
Thread 5 Issued Ticket #23
Thread 4 Issued Ticket #24
Thread 2 Issued Ticket #25
Final ticket count recorded in file: 25

*/
