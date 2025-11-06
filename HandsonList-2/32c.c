/*
========================================================================================================
Name : 32c.c
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
#include <unistd.h>
#include <time.h>

#define NUM_RESOURCES 2     
#define NUM_THREADS 5  
#define USE_TIME 2         

sem_t resource_semaphore;   
int resource_pool[NUM_RESOURCES] = {0}; 
pthread_mutex_t pool_mutex = PTHREAD_MUTEX_INITIALIZER; 
int acquire_resource(int thread_id) {
    pthread_mutex_lock(&pool_mutex);
    
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (resource_pool[i] == 0) {
            resource_pool[i] = thread_id; 
            pthread_mutex_unlock(&pool_mutex);
            return i;
        }
    }
    
    pthread_mutex_unlock(&pool_mutex);
    return -1; 
}

void release_resource(int index) {
    pthread_mutex_lock(&pool_mutex);
    resource_pool[index] = 0; 
    pthread_mutex_unlock(&pool_mutex);
}

void *worker_thread(void *arg) {
    int thread_id = *(int *)arg;
    int acquired_index = -1;

    printf("Thread %d Waiting to acquire a resource...\n", thread_id);
    if (sem_wait(&resource_semaphore) != 0) {
        perror("sem_wait failed");
        return NULL;
    }

   
    acquired_index = acquire_resource(thread_id);

    if (acquired_index != -1) {
        printf("Thread %d ACQUIRED Resource %d. Using for %d seconds.\n", 
               thread_id, acquired_index + 1, USE_TIME);

        sleep(USE_TIME); 
        release_resource(acquired_index);
        printf("Thread %d RELEASED Resource %d.\n", thread_id, acquired_index + 1);
    } 
    if (sem_post(&resource_semaphore) != 0) {
        perror("sem_post failed");
    }

    return NULL;
}


int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    printf("\nCounting Semaphore\n");
    printf("Resource Pool Size: %d | Worker Threads: %d\n\n", NUM_RESOURCES, NUM_THREADS);
    if (sem_init(&resource_semaphore, 0, NUM_RESOURCES) != 0) {
        perror("Semaphore initialization failed");
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, worker_thread, &thread_ids[i]) != 0) {
            perror("Thread creation failed");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    sem_destroy(&resource_semaphore);
    pthread_mutex_destroy(&pool_mutex);

    printf("\nAll threads finished. Program exiting.\n");
    return 0;
}
/*

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 32c.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out

Counting Semaphore
Resource Pool Size: 2 | Worker Threads: 5

Thread 1 Waiting to acquire a resource...
Thread 1 ACQUIRED Resource 1. Using for 2 seconds.
Thread 2 Waiting to acquire a resource...
Thread 2 ACQUIRED Resource 2. Using for 2 seconds.
Thread 3 Waiting to acquire a resource...
Thread 4 Waiting to acquire a resource...
Thread 5 Waiting to acquire a resource...
Thread 1 RELEASED Resource 1.
Thread 2 RELEASED Resource 2.
Thread 3 ACQUIRED Resource 1. Using for 2 seconds.
Thread 4 ACQUIRED Resource 2. Using for 2 seconds.
Thread 4 RELEASED Resource 2.
Thread 3 RELEASED Resource 1.
Thread 5 ACQUIRED Resource 1. Using for 2 seconds.
Thread 5 RELEASED Resource 1.

All threads finished. Program exiting.

*/
