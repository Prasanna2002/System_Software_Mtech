/*
============================================================================
Name : 26.c
Author : Prasanna Kumar M
Description :Write a program to execute an executable program.
             a. use some executable program
             b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 3rd Sep, 2025.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
int main()
{  
    char* arg[] = {"cat", "26_sample.txt"};
    execv("/bin/cat", arg);
    return 0;
}
/*
Output:
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/Handsonlist1$ gcc 26.c -o 26
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/Handsonlist1$ ./26
This is Me Who is Typing this Line !!!


*/
