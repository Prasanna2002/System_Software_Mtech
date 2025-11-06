
/*
========================================================================================================
Name : 31.c
Author : Prasanna Kumar M
Description : Write a program to create a semaphore and initialize value to the semaphore.
		a. Create a binary semaphore.
		b. Create a counting semaphore.
Date: 26 Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#ifndef __APPLE__
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
#endif

int main(void)
{
    union semun arg;
    key_t k = ftok(".", 'a');
    int semid = semget(k, 1, IPC_CREAT | 0666);

    int choice;
    printf("Choose an option:\n1.Binary Semaphore\n2.Counting Semaphore\n : ");
    scanf("%d", &choice);

    if (choice == 1) {
        arg.val = 1;
    } else if (choice == 2) {
        arg.val = 5;
    }

    semctl(semid, 0, SETVAL, arg);
    int val = semctl(semid, 0, GETVAL);

    printf("Semaphore created: id=%d, value=%d\n", semid, val);
    return 0;
}

/*
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 31.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Choose an option:
1.Binary Semaphore
2.Counting Semaphore
: 1
Semaphore created: id=0, value=1
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Choose an option:
1.Binary Semaphore
2.Counting Semaphore
: 2
Semaphore created: id=0, value=5

*/
