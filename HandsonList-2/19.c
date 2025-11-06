/*
========================================================================================================
Name : 19.c
Author : Prasanna Kumar M
Description : Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function
Date: 21 Sept, 2025.
========================================================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
    char name[100];
    printf("Enter the name of fifo file: ");
    scanf("%s", name);

    int choice;
    printf("Choose an option:\n1.) mknod system call\n2.) mkfifo system call\n=> ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("Using mknod system call...\n");
        mknod(name, S_IFIFO | 0744, 0);
        printf("FIFO file created using mknod\n");
        break;
    case 2:
        printf("Using mkfifo system call...\n");
        mkfifo(name, 0744);
        printf("FIFO file created using mkfifo\n");
        break;

    default:
        printf("Invalid choice\n");
        break;
    }

    return (0);
}
/*
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 19.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Enter the name of fifo file: fifofile
Choose an option:
1.) mknod system call
2.) mkfifo system call
=> 1
Using mknod system call...
FIFO file created using mknod

---------------------------------------------------------------------------------------------

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Enter the name of fifo file: fifofile2
Choose an option:
1.) mknod system call
2.) mkfifo system call
=> 2
Using mkfifo system call...
FIFO file created using mkfifo

----------------------------------------------------------------------------------------------
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Enter the name of fifo file: fifofile3
Choose an option:
1.) mknod system call
2.) mkfifo system call
=> 3
Invalid choice

*/
