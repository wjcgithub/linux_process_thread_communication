#include "sys/types.h"
#include "sys/msg.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main(){
  int msgid;
  msgid = msgget(IPC_PRIVATE,0777);   //create msg queue
  if(msgid<0){
    printf("create message queue failure\n");
    return -1;
  }
  printf("create message queue success, msgid=%d\n", msgid);
  system("ipcs -q");

  //delete msg queue
  msgctl(msgid,IPC_RMID,NULL);

  //再次查看
  system("ipcs -q");
  return 0;
}
