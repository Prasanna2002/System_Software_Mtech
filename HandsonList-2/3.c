/*
============================================================================
Name : 1a.c
Author : Prasanna Kumar M
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 16th Sep, 2025.
============================================================================
*/

#include <stdio.h> 
#include<stdlib.h>
#include <sys/resource.h> 

int main() 
{
    struct rlimit limit_info;
    if (getrlimit(RLIMIT_NOFILE,&limit_info) == -1)
    {
        perror("Error in Accessing File Descriptor Limit Data :");
        return EXIT_FAILURE; 
    }else{
        printf("Befor Setrlimit, Number of File Descriptor Allowed are \n"); 
        printf("Soft Limit is : %lu\n",limit_info.rlim_cur); 
        printf("Hard Limit is : %lu\n",limit_info.rlim_max); 
    }
    
    limit_info.rlim_cur = 19576; 
    if (setrlimit(RLIMIT_NOFILE,&limit_info) == -1)
    {
        perror("Error in Setting File Descriptor Limit Data :");
        return EXIT_FAILURE; 
    }else{
        printf("After Setrlimit, Number of File Descriptor Allowed are \n"); 
        printf("Soft Limit is : %lu\n",limit_info.rlim_cur); 
        printf("Hard Limit is : %lu\n",limit_info.rlim_max); 
    }
    
    limit_info.rlim_max = 19576; 
    if (setrlimit(RLIMIT_NOFILE,&limit_info) == -1)
    {
        perror("Error in Setting File Descriptor Limit Data :");
        return EXIT_FAILURE; 
    }else{
        printf("After Setrlimit, Number of File Descriptor Allowed are \n"); 
        printf("Soft Limit is : %lu\n",limit_info.rlim_cur); 
        printf("Hard Limit is : %lu\n",limit_info.rlim_max); 
    }
    return 0;
}

/*
            OUTPUT
            
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 3.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Befor Setrlimit, Number of File Descriptor Allowed are 
Soft Limit is : 1024
Hard Limit is : 1073741816
After Setrlimit, Number of File Descriptor Allowed are 
Soft Limit is : 19576
Hard Limit is : 1073741816
After Setrlimit, Number of File Descriptor Allowed are 
Soft Limit is : 19576
Hard Limit is : 19576

----------------------------------------------------------
Befor Setrlimit, Number of File Descriptor Allowed are 
Soft Limit is : 1024
Hard Limit is : 1073741816
After Setrlimit, Number of File Descriptor Allowed are 
Soft Limit is : 19576
Hard Limit is : 1073741816
Error in Setting File Descriptor Limit Data :: Operation not permitted
------------------------------------------------------------

*/
