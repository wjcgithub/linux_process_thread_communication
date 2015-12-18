/*************************************************************************
	> File Name: fork.c
	> Author:
	> Mail:
	> Created Time: Fri 27 Nov 2015 01:05:06 PM CST
  > 测试父子进程能不能使用一个全局变量的方式实现,先执行父进程在执行子进程
 ************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int main(){
    pid_t pid;
    int process_inter=0;
    //创建一个进程
    pid = fork();

    if(pid==0){ //child process code
        int i=0;
        while(process_inter == 0);
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
      process_inter = 1;
    }
    return 0;
}
