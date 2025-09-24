/*
============================================================================
Name : 2.c
Author : Prasanna Kumar M
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date: 16th Sep, 2025.
============================================================================
*/
#include <stdio.h> 
#include <sys/resource.h>
#include<unistd.h>
#include <stdlib.h>
#include <errno.h>

void printlimits(struct rlimit *ptr)
{
        if (ptr->rlim_cur == RLIM_INFINITY){ 
                printf("The Soft Limit is : Unlimited\n");
        }else{
                printf("The Soft Limit is :%lu\n",ptr->rlim_cur); 
        }
        
        if (ptr->rlim_max == RLIM_INFINITY){
                printf("The Hard Limit is : Unlimited\n"); 
        }else
        {
	        printf("The Hard Limit is : %lu\n",ptr->rlim_max);
        }
}
 

int main()
{
	struct rlimit limit_data;
   	if(getrlimit(RLIMIT_CPU,&limit_data)== -1) 
	{
		perror("Error:"); 
		return EXIT_FAILURE; 
	}
	printf("\nCPU Limits  \n");
	printlimits(&limit_data);
 
        if(getrlimit(RLIMIT_FSIZE,&limit_data)== -1) 
        {
                perror("Error:"); 
                return EXIT_FAILURE; 
        }
	printf("\nFile Size Limits are\n"); 
	printlimits(&limit_data);

	if(getrlimit(RLIMIT_NOFILE,&limit_data)== -1) 
        {
                perror("Error:"); 
                return EXIT_FAILURE; 
        }
	printf("\nFile Descriptors Limits \n");
	printlimits(&limit_data);

	if(getrlimit(RLIMIT_STACK,&limit_data)== -1) 
        {
                perror("Error:"); 
                return EXIT_FAILURE; 
        }
	printf("\nStack Limits \n");
	printlimits(&limit_data);

	if(getrlimit(RLIMIT_DATA,&limit_data)== -1) 
        {
                perror("Error:"); 
                return EXIT_FAILURE; 
        }
	printf("\nData Segment Limits \n");
	printlimits(&limit_data);

	if(getrlimit(RLIMIT_CORE,&limit_data)== -1) 
        {
                perror("Error:"); 
                return EXIT_FAILURE; 
        } 
	printf("\nCore Dump File Limits  \n"); 
	printlimits(&limit_data);

	if (getrlimit(RLIMIT_AS, &limit_data) == -1)
	{
		perror("Error:");
		return EXIT_FAILURE;
	} 
	printf("\nVirtual Memory Limits \n"); 
	printlimits(&limit_data);
	
	if(getrlimit(RLIMIT_RSS,&limit_data)== -1) 
	{
		perror("Error:"); 
		return EXIT_FAILURE; 
	}
	printf("\nThe RSS Limits \n"); 
	printlimits(&limit_data);
	
	if(getrlimit(RLIMIT_MEMLOCK,&limit_data)== -1) 
	{
		perror("Error:"); 
		return EXIT_FAILURE; 
	}
	printf("\nThe Memory area size which Process can Lock  \n");
	printlimits(&limit_data); 
	
	if(getrlimit(RLIMIT_NPROC,&limit_data)== -1) 
	{
		perror("Error:"); 
		return EXIT_FAILURE; 
	}
	printf("\nThe Number of Processes that are allowed to create  \n");
	printlimits(&limit_data); 
	
	if(getrlimit(RLIMIT_MSGQUEUE,&limit_data)== -1) 
	{
		perror("Error:"); 
		return EXIT_FAILURE; 
	}
	printf("\nThe Message Queue Limits are  \n");
	printlimits(&limit_data); 
	
	if(getrlimit(RLIMIT_NICE,&limit_data)== -1) 
	{
		perror("Error:"); 
		return EXIT_FAILURE; 
	}
	printf("\nThe Nice Value are  \n");
	printlimits(&limit_data); 
	return 0;
}

/*
        OUTPUT 
      
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 2.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out

CPU Limits  
The Soft Limit is : Unlimited
The Hard Limit is : Unlimited

File Size Limits are
The Soft Limit is : Unlimited
The Hard Limit is : Unlimited

File Descriptors Limits 
The Soft Limit is :1024
The Hard Limit is : 1073741816

Stack Limits 
The Soft Limit is :8388608
The Hard Limit is : Unlimited

Data Segment Limits 
The Soft Limit is : Unlimited
The Hard Limit is : Unlimited

Core Dump File Limits  
The Soft Limit is :0
The Hard Limit is : Unlimited

Virtual Memory Limits 
The Soft Limit is : Unlimited
The Hard Limit is : Unlimited

The RSS Limits 
The Soft Limit is : Unlimited
The Hard Limit is : Unlimited

The Memory area size which Process can Lock  
The Soft Limit is :954032128
The Hard Limit is : 954032128

The Number of Processes that are allowed to create  
The Soft Limit is :28286
The Hard Limit is : 28286

The Message Queue Limits are  
The Soft Limit is :819200
The Hard Limit is : 819200

The Nice Value are  
The Soft Limit is :0
The Hard Limit is : 0

*/
