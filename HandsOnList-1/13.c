/*
============================================================================
Name : 13.c
Author : Prasanna Kumar M
Description : Program to wait for a STDIN for 10 seconds using select. Write a proper print statement to
              verify whether the data is available within 10 seconds or not (check in $man 2 select)
Date: 1st Sep, 2025.
============================================================================
*/

#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
void main()
{
    struct timeval t;
    fd_set fd;
    FD_SET(0, &fd);
    t.tv_sec = 10;
    t.tv_usec = 0;
    int a = select(1, &fd, NULL, NULL, &t);
    if (a == -1)
    {
        printf("Can't show output");
    }
    else if (a == 0)
    {
        printf("Time out occured");
    }
    else
    {
        printf("Data entered");
    }
}
/*
Output: Time out occured (It was printed after 10 seconds.)
*/

