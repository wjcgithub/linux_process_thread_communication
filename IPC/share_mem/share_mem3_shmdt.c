#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int main(){
  int shmid;
  int key;
  char *p;
  key = ftok("./a.c",'a');
  if (key<0) {
    printf("create key failure\n");
    return -2;
  }
  printf("create key success key=%X\n", key);

  //创建一段共享内存
  shmid = shmget(key,128,IPC_CREAT | 0777);
  if(shmid<0){
    printf("create share memory failure\n");
    return -1;
  }else{
    printf("create share memory success, shmid=%d\n", shmid);
    system("ipcs -m");
    //映射共享内存,
    p=(char *)shmat(shmid,NULL,0);
    if(p==NULL){
      printf("shmat function failure\n");
      return -3;
    }

    //write share memory
    fgets(p,128,stdin);

    //start read share memory
    printf("first share memory data%s\n", p);
    printf("second share memory data%s\n", p);

    //删除映射地址
    shmdt(p);

    //测试该用户态的映射地址是否被删除了
    memcpy(p,"abcd",4);

    // system("ipcrm -m shmid");
  }
  return 0;
}
