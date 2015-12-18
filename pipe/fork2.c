/*************************************************************************
	> File Name: fork.c
	> Author:
	> Mail:
	> Created Time: Fri 27 Nov 2015 01:05:06 PM CST
  > 测试无名管道的容量,写阻塞
 ************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int main(){
    pid_t pid;
    int process_inter=0;
    //创建文件描述符
    int fd[2];
    //保存 pipe 的返回值
    int ret;
    //创建读缓存区
    char readbuffer[128]={0};
    //创建写缓存区
    char writebuffer[]="hello linux";
    //创建一个管道[无名的]
    ret = pipe(fd);
    if (ret<0) {
      printf("create pipe failure\n\n\n");
      return -1;
    }
    printf("create pipe success fd[0]=%d,fd[1]=%d\n\n\n",fd[0],fd[1]);
    int i=0;
    while(i<5456){  //5456 就会阻塞
      write(fd[1],writebuffer,sizeof(writebuffer));
      i++;
    }
    close(fd[0]);
    close(fd[1]);
    printf("write pipe end----%lu\n",sizeof(writebuffer));

    //创建一个进程
    pid = fork();

    //判断进程创建的逻辑
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
