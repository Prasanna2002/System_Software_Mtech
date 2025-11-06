
/*
========================================================================================================
Name : 26.c
Author : Prasanna Kumar M
Description : Write a program to send messages to the message queue. Check $ipcs -q.
Date: 25 Sept, 2025.
========================================================================================================
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

struct msgbuf {
    long mtype;
    char mtext[80];
};

int main()
{
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, IPC_CREAT | 0666);

    struct msgbuf message;
    message.mtype = 10;

    printf("Enter message:\n");
    fgets(message.mtext, sizeof(message.mtext), stdin);

    size_t len = strlen(message.mtext);
    if (len > 0 && message.mtext[len - 1] == '\n')
        message.mtext[len - 1] = '\0';

    msgsnd(msqid, &message, strlen(message.mtext) + 1, 0);
    printf("Message sent successfully\n");

    return 0;
}
/*
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ cc 26.c
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Enter message:
HelloThere
Message sent successfully
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61177384 0          prasanna   666        11           1           

prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ./a.out
Enter message:
Bingo
Message sent successfully
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/ssassign/Handsonlist2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61177384 0          prasanna   666        17           2 
*/
