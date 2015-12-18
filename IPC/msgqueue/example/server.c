/**
* @author wjc
* @content 创建一个父进程负责写,子进程负责读的服务器
**/
#include "sys/types.h"
#include "sys/msg.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
struct msgbuf
{
  long type;
  char voltage[124];
  char ID[4];
};

int main(){
  int msgid;
  int readret;
  int key;
  int pid;
  struct msgbuf sendbuf,recvbuf;
  //创建一个共享内存
  key=ftok("./b.c",'c');
  if (key<0) {
    printf("create key fail\n");
    return -2;
  }
  msgid = msgget(key,IPC_CREAT|0777);
  // msgid = msgget(IPC_PRIVATE,0777);   //create msg queue
  if(msgid<0){
    printf("create message queue failure\n");
    return -1;
  }
  printf("create message queue success, msgid=%d\n", msgid);
  system("ipcs -q");

  //创建一个子进程
  pid=fork();
  if(pid>0){   //parent process   负责写信息到消息队列类型为100的队列中
    // start write msg to msg queue
    //init sendbuf
    sendbuf.type=100;
    while (1) {
      //step1 清理
      memset(recvbuf.voltage,0,124);
      printf("please input mesage:\n");
      fgets(sendbuf.voltage,124,stdin);
      //start write msg to mesg queue
      msgsnd(msgid,(void *)&sendbuf, strlen(sendbuf.voltage),0);
    }
  }

  if (pid==0) {   //child process  负责从消息队列类型为200的队列中读取数据
    while(1){
      memset(recvbuf.voltage,0,124);
      msgrcv(msgid,(void *)&recvbuf, 124, 200, 0);
      printf("receive from msg queue of type 200 : %s\n", recvbuf.voltage);
    }
  }

  //delete msg queue
  msgctl(msgid,IPC_RMID,NULL);
  //再次查看
  system("ipcs -q");
  return 0;
}
