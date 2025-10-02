/*
========================================================================================================
Name : 4.c
Author : Prasanna Kumar M
Description : Write a program to measure how much time is taken to execute 100 getppid() system call. Use time stamp counter.
Date: 17 Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned long long rdtsc(void) {
    unsigned long long dst;
    __asm__ __volatile__ ("rdtsc" : "=A" (dst));
    return dst;
}

int main() {
    unsigned long long start, end, total;
    
    int num  = 100;
    int i;
    
    printf("Measuring time for %d getppid() system calls\n", num);
    start = rdtsc();

    for (i = 0; i < num; i++) {
        getppid(); 
    }

    end = rdtsc();

    total = end - start;

    printf("Total cycles for %d calls: %llu\n", num, total);
    return 0;
}

/*

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 4.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Measuring time for 100 getppid() system calls
Total cycles for 100 calls: 439694

*/
