/*
============================================================================
Name : 27.c
Author : Prasanna Kumar M
Description :Write a program to execute ls -Rl by the following system calls
             a. execl
             b. execlp
             c. execle
             d. execv
             e. execvp
Date: 6th Sep, 2025.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
int main(int argc,char *env[])
{
    char *path = "/bin/ls";
    execl(path, path, "-Rl", NULL);//a
    char *path2 = "ls";
    execlp(path2, path2, "-Rl", NULL);//b
    execle(path, path, "-Rl" ,"27c_example/",NULL, env);//c
    char *argv[] = {path,"-Rl",NULL};
    execv(path, argv);//d
    char *buf[] = {path2, "-Rl", NULL};
    execvp(path2, buf);//e     
    return 0;
}
/*
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/Handsonlist1$ gcc 27.c -o 27
prasanna@prasanna-VivoBook-ASUSLaptop-X530FN-S530FN:~/Desktop/Handsonlist1$ ./27
.:
total 388
-rw-rw-rw- 1 prasanna prasanna   382 Sep  6 13:04 01_shell.sh
-rwxrwxr-x 1 prasanna prasanna 16208 Sep  6 12:36 10
-rw-rw-rw- 1 prasanna prasanna  1214 Sep  6 12:39 10.c
-rwxrwxr-x 1 prasanna prasanna    30 Sep  6 12:37 10_sample.txt
-rw-rw-rw- 1 prasanna prasanna   906 Sep  6 13:00 11.c
-rw-rw-rw- 1 prasanna prasanna   967 Sep  6 03:44 12.c
-rw-rw-rw- 1 prasanna prasanna   935 Sep  6 03:45 13.c
-rw-rw-rw- 1 prasanna prasanna  1574 Sep  6 03:46 14.c
-rwxrwxr-x 1 prasanna prasanna 16208 Sep  6 13:05 16a
-rw-rw-rw- 1 prasanna prasanna   917 Sep  6 13:07 16a.c
-rw-rw-rw- 1 prasanna prasanna   934 Sep  6 13:08 16b.c
-rw-rw-r-- 1 prasanna prasanna    39 Sep  6 13:04 16_sample.txt
-rw-rw-rw- 1 prasanna prasanna  1128 Sep  6 13:09 17a.c
-rw-rw-rw- 1 prasanna prasanna  1536 Sep  6 13:20 17b.c
-rw-rw-rw- 1 prasanna prasanna  1389 Sep  6 13:18 18a.c
-rw-rw-rw- 1 prasanna prasanna  1367 Sep  6 13:18 18b.c
-rw-rw-rw- 1 prasanna prasanna   973 Sep  6 03:47 18.c
-rw-rw-rw- 1 prasanna prasanna    90 Sep  6 23:26 18_sample.txt
-rw-rw-rw- 1 prasanna prasanna   772 Sep  6 13:20 19.c
-rw-rw-rw- 1 prasanna prasanna   791 Sep  6 11:33 1a.c
-rw-rw-rw- 1 prasanna prasanna   747 Sep  6 03:34 1b.c
-rw-rw-rw- 1 prasanna prasanna  1135 Sep  6 03:34 1c.c
-rw-rw-rw- 1 prasanna prasanna   871 Sep  6 13:20 20.c
-rw-rw-rw- 1 prasanna prasanna   604 Sep  6 13:21 21.c
-rwxrwxr-x 1 prasanna prasanna 16288 Sep  6 13:25 22
-rw-rw-rw- 1 prasanna prasanna   771 Sep  6 13:25 22.c
-rwxrwxr-x 1 prasanna prasanna 16240 Sep  6 13:26 23
-rw-rw-rw- 1 prasanna prasanna   769 Sep  6 13:27 23.c
-rwxrwxr-x 1 prasanna prasanna 16200 Sep  6 13:28 24
-rw-rw-rw- 1 prasanna prasanna   762 Sep  6 13:28 24.c
-rw-rw-rw- 1 prasanna prasanna   591 Sep  6 13:23 25.c
-rwxrwxr-x 1 prasanna prasanna 16080 Sep  6 13:33 26
-rw-rw-rw- 1 prasanna prasanna   807 Sep  6 13:33 26.c
-rw-rw-r-- 1 prasanna prasanna    39 Sep  6 13:32 26_sample.txt
-rwxrwxr-x 1 prasanna prasanna 16248 Sep  6 13:40 27
-rw-rw-rw- 1 prasanna prasanna  4358 Sep  6 13:33 27.c
-rwxrwxr-x 1 prasanna prasanna 16152 Sep  6 13:36 28
-rw-rw-rw- 1 prasanna prasanna  1074 Sep  6 13:36 28.c
-rwxrwxr-x 1 prasanna prasanna 16232 Sep  6 13:36 29
-rw-rw-rw- 1 prasanna prasanna  2490 Sep  6 13:37 29.c
-rw-rw-rw- 1 prasanna prasanna   436 Sep  6 03:36 2.c
-rw-rw-rw- 1 prasanna prasanna  1035 Sep  6 13:37 30.c
-rw-rw-rw- 1 prasanna prasanna   858 Sep  6 11:37 3.c
-rw-rw-rw- 1 prasanna prasanna   771 Sep  6 11:36 4.c
-rw-rw-rw- 1 prasanna prasanna   926 Sep  6 13:13 5.c
-rw-rw-rw- 1 prasanna prasanna     0 Sep  6 00:47 5_sample_1.txt
-rw-rw-rw- 1 prasanna prasanna     0 Sep  6 00:48 5_sample_2.txt
-rw-rw-rw- 1 prasanna prasanna     0 Sep  6 00:48 5_sample_3.txt
-rw-rw-rw- 1 prasanna prasanna     0 Sep  6 00:48 5_sample_4.txt
-rw-rw-rw- 1 prasanna prasanna     0 Sep  6 00:48 5_sample_5.txt
-rw-rw-rw- 1 prasanna prasanna   708 Sep  6 12:48 6.c
-rwxrwxr-x 1 prasanna prasanna 16200 Sep  6 12:51 7
-rw-rw-rw- 1 prasanna prasanna   682 Sep  6 12:51 7.c
-rw-rw-r-- 1 prasanna prasanna    39 Sep  6 12:51 7_sample_1.txt
-rw-r--r-- 1 prasanna prasanna    39 Sep  6 12:51 7_sample_2.txt
-rwxrwxr-x 1 prasanna prasanna 16328 Sep  6 12:45 8
-rw-rw-rw- 1 prasanna prasanna   921 Sep  6 12:47 8.c
-rw-r--r-- 1 prasanna prasanna    37 Sep  6 12:45 8_sample.txt
-rw-rw-rw- 1 prasanna prasanna  1617 Sep  6 12:40 9.c
-rwxrwxrwx 1 prasanna prasanna 16296 Sep  6 00:48 a.out
-rw-rw-rw- 1 prasanna prasanna     0 Sep  6 00:48 creatfile.txt
-rw-rw-rw- 1 prasanna prasanna     0 Sep  6 00:49 file1dup.txt
-rw-rw-rw- 1 prasanna prasanna    20 Sep  6 00:49 file2.txt
-rw-r--r-- 1 prasanna prasanna    48 Sep  6 13:25 out.txt
-rw-rw-rw- 1 prasanna prasanna    24 Sep  6 22:58 sample.txt
-rw-rw-rw- 1 prasanna prasanna    11 Sep  6 00:49 softlink.txt
-rw-rw-rw- 1 prasanna prasanna     4 Sep  6 00:49 ticket_sample.txt

*/
