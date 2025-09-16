/*
============================================================================
Name : 28.c
Author : Prasanna Kumar M
Description :Write a program to get maximum and minimum real time priority.
Date: 4th Sep, 2025.
============================================================================
*/
#include <stdio.h>
#include <sched.h>
int main()
{
    printf("Maximum priority for FIFO scheduling is %d and minimum priority is %d\n", sched_get_priority_max(SCHED_FIFO), sched_get_priority_min(SCHED_FIFO));
    printf("Maximum priority for RR scheduling is %d and minimum priority is %d\n", sched_get_priority_max(SCHED_RR), sched_get_priority_min(SCHED_RR));
    printf("Maximum priority for other scheduling priority is %d and minimum priority is %d\n", sched_get_priority_max(SCHED_OTHER), sched_get_priority_min(SCHED_OTHER));
    return 0;
}
/*
Output:
Maximum priority for FIFO scheduling is 99 and minimum priority is 1
Maximum priority for RR scheduling is 99 and minimum priority is 1
Maximum priority for other scheduling priority is 0 and minimum priority is 0

*/
