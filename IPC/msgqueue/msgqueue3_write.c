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

  //delete msg queue
  msgctl(msgid,IPC_RMID,NULL);
  //再次查看
  system("ipcs -q");
  return 0;
}
