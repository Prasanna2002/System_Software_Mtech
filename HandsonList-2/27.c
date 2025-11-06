

/*
========================================================================================================
Name : 27.c
Author : Prasanna Kumar M
Description : Write a program to receive messages from the message queue.
		a. With 0 as a flag
		b. with IPC_NOWAIT as a flag
Date: 25 Sept, 2025.
========================================================================================================
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

struct msgbuf {
    long mtype;
    char mtext[80];
};

int main() {
    key_t key = ftok(".", 'a');
    struct msgbuf message;
    int msqid = msgget(key, 0);

    int flag, mtype;
    printf("Choose flag:\n1. 0 (blocking)\n2. IPC_NOWAIT (non-blocking)\n=> ");
    scanf("%d", &flag);

    printf("Enter message type:\n");
    scanf("%d", &mtype);

    int recv_flag = (flag == 2) ? IPC_NOWAIT : 0;

    if (msgrcv(msqid, &message, sizeof(message.mtext), mtype, recv_flag) == -1) {
        perror("msgrcv");
    } else {
        printf("Message: %s\n", message.mtext);
    }

    return 0;
}
/* 
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 27.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Choose flag:
1. 0 (blocking)
2. IPC_NOWAIT (non-blocking)
=> 1
Enter message type:
10
Message: HelloThere
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Choose flag:
1. 0 (blocking)
2. IPC_NOWAIT (non-blocking)
=> 2
Enter message type:
10
Message: Bingo
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Choose flag:
1. 0 (blocking)
2. IPC_NOWAIT (non-blocking)
=> 2
Enter message type:
10
msgrcv: No message of desired type

*/
