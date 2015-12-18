#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void myfun(int signum){
  //这样就可以唤醒pause函数
  return;
}

int main(){
  int shmid;
  int key;
  char *p;
  int pid;
  //创建一段共享内存
  shmid = shmget(IPC_PRIVATE,128,IPC_CREAT | 0777);
  if(shmid<0){
    printf("create share memory failure\n");
    return -1;
  }else{
    printf("create share memory success, shmid=%d\n", shmid);

    //fork一个进程
    pid = fork();
    if(pid>0){  //parent process
      //添加自定义信号处理，处理子进程发送的信号
      signal(SIGUSR2,myfun);
      //映射共享内存,
      p=(char *)shmat(shmid,NULL,0);
      if(p==NULL){
        printf("parent process:shmat function failure\n");
        return -3;
      }

      //父进程执行写操作
      while (1) {
        printf("parent process start write share memory!\n");
        //开始写
        fgets(p,128,stdin);
        //写好了之后告诉子进程
        kill(pid,SIGUSR1);
        pause(); //wait child process read
      }
    }

    if(pid==0){ //child process
      signal(SIGUSR1,myfun);   //添加自定义信号处理，处理父进程发送的信号
      p=(char *)shmat(shmid,NULL,0);
      if(p==NULL){
        printf("child process shmat failure\n");
        return -3;
      }
      while (1) {
        pause(); //wait parent process write
        printf("share memory data:%s\n", p);  //start read share memory
        kill(getppid(),SIGUSR2);
      }
    }

    //删除用户态映射地址内存
    shmdt(p);
    //删除内核态映射地址内存
    shmctl(shmid,IPC_RMID,NULL);
    system("ipcs -m");
    return 0;
  }
}
