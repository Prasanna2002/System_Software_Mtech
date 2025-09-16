/*
============================================================================
Name : 1c.c
Author : Prasanna Kumar M
Description : Program to create a FIFO file using the `mkfifo` library function or `mknod` system call
Date: 30th Aug, 2025.
============================================================================
*/

#include<sys/types.h> 
#include<sys/stat.h>  
#include<stdio.h>     

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Enter 2 file names to create FIFO with mkfifo and mknod\n");
		return 0;
	}	
	const char *mkfifoName = argv[1];
	const char *mknodName = argv[2];

	int mkfifo_status = mkfifo(mkfifoName, S_IRWXU);
	
	if(mkfifo_status == -1){
		perror("Error while creating FIFO file with mkfifo\n");
	}else{
		printf("Created FIFO file with mkfifo successfully\n");
	}

	int mknod_status =  mknod(mknodName, S_IFIFO | S_IRWXU ,0); 

	if(mknod_status == -1){
		perror("Error while creating FIFO file with mknod\n");
	}else{
		printf("Created FIFO file with mknod successfully\n");
	}
}

/*
./a.out mkfifo mknod
Created FIFO file with mkfifo successfully
Created FIFO file with mknod successfully


mkfifo : creates a FIFO File, which inturn creates a buffer in the kernel which is managed by the Kernel .....
mkfifo(FILENAME,MODE) S_IRWXU ----> Read Write Xecute for the USer(OWner) and for the rest read-only.

TYPE: This is a single letter that specifies the type of file to create.

p: Creates a named pipe (FIFO). This is used for communication between processes.

c: Creates a character device file. This is used for devices that transfer data character by character (e.g., a serial port or a terminal).

b: Creates a block device file. This is for devices that transfer data in blocks (e.g., a hard disk drive or a CD-ROM).
mknod : This Command is used to create file it can be char device files / block device files / FIFO Files with the specific Commands 

Syntax 
mknod(file_name,type,MAJOR,MINOR) 

MAJOR and MINOR --->  Useful to indicate the major device or the minor device only when the file is Device Files
IF FILE TYPE IS FIFO ,this option  is set to 0 by Default :
MAJOR and MINOR: These are used for character and block device files. They are numbers that identify the specific device driver and device instance in the kernel.

Major number: Identifies the device driver.

Minor number: Identifies the specific device instance managed by that driver.

Example: 
mknod /dev/smpte_tape c 10 1

*/
