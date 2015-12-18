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
  int key;
  struct msgbuf sendbuf,recvbuf;
  //创建一个共享内存
  key=ftok("./a.c",'c');
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

  // start read msg to msg queue
  while (1) {
    //step1 清理
    memset(recvbuf.voltage,0,124);
    //start read msg from mesg queue
    msgrcv(msgid, (void *)&recvbuf, 124, 100, 0);
    printf("receive data from msg queue: %s\n", recvbuf.voltage);
  }

  //delete msg queue
  msgctl(msgid,IPC_RMID,NULL);
  //再次查看
  system("ipcs -q");
  return 0;
}
