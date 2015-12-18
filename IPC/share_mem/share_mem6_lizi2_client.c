#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct mybuf
{
  int pid;
  char buf[124];
};

void myfun(int signum){
  //这样就可以唤醒pause函数
  return;
}

int main(){
  int shmid;
  int key;
  struct mybuf *p;
  int pid;
  key=ftok("./a.c",'c'); //创建shmget的key值
  if(key<0){
    printf("ftok create failure\n");
    return -1;
  }
  printf("ftok create success\n");

  //创建一段共享内存
  shmid = shmget(key,128,IPC_CREAT | 0777);
  if(shmid<0){
    printf("create share memory failure\n");
    return -1;
  }
  printf("create share memory success, shmid=%d\n", shmid);

  //添加自定义信号处理，处理子进程发送的信号
  signal(SIGUSR1,myfun);
  //映射共享内存,
  p=(struct mybuf *)shmat(shmid,NULL,0);
  if(p==NULL){
    printf("parent process:shmat function failure\n");
    return -3;
  }

  pid = p->pid; //write share memory get server pid
  p->pid = getpid(); //write client pid to share memory
  kill(pid,SIGUSR2); //kill signal

  //client start read data from share memory
  while (1) {
    pause(); //wait server write data to share memory
    printf("client process receive data from share memory: %s\n", p->buf); //read data
    kill(pid,SIGUSR2); //server may write share memory
  }

  //删除用户态映射地址内存
  shmdt(p);
  //删除内核态映射地址内存
  shmctl(shmid,IPC_RMID,NULL);
  system("ipcs -m");
  return 0;
}
