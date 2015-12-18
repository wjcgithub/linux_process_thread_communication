/*************************************************************************
	> File Name: fork.c
	> Author:
	> Mail:
	> Created Time: Fri 27 Nov 2015 01:05:06 PM CST
  > 简单的创建父子进程
 ************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int main(){
    pid_t pid;
    //创建一个进程
    pid = fork();

    if(pid==0){ //child process code
        int i=0;
        for(i=0; i<5; i++){
          printf("this is child process i=%d\n", i);
          usleep(100);
        }
    }
    if (pid > 0) { //parent process code
      int i=0;
      for(i=0; i<5; i++){
        printf("this is parent process i=%d\n", i);
        usleep(100);
      }
    }
    return 0;
}
