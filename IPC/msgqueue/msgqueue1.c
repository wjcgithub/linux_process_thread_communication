#include "sys/types.h"
#include "sys/msg.h"
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
  //define msg object
  struct msgbuf sendbuf,recvbuf;
  msgid = msgget(IPC_PRIVATE,0777);   //create msg queue
  if(msgid<0){
    printf("create message queue failure\n");
    return -1;
  }
  printf("create message queue success, msgid=%d\n", msgid);
  system("ipcs -q");

  //init sendbuf
  sendbuf.type=100;
  printf("please input msg: \n");
  fgets(sendbuf.voltage,124,stdin);
  //start write msg to msg queue use wait method
  msgsnd(msgid,(void *)&sendbuf,strlen(sendbuf.voltage),0);

  //read msg from msg queue
  memset(recvbuf.voltage,0,124);
  readret=msgrcv(msgid,(void *)&recvbuf.voltage,124,100,0);
  printf("recv: %s", recvbuf.voltage);
  printf("readret%d\n", readret);

  //second read msg queue
  msgrcv(msgid,(void *)&recvbuf,124,100,0);
  //如果没有独到数据进程会结束到这里
  printf("second read after\n");

  //delete msg queue
  msgctl(msgid,IPC_RMID,NULL);
  //再次查看
  system("ipcs -q");
  return 0;
}
