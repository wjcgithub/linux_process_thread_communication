/**
*  使用信号量做线程的通信。 主线程先执行，子线程后执行
**/
#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
// #include "semaphore.h"
#include "sys/ipc.h"
#include "sys/sem.h"
//声明信号量
// sem_t sem;
union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO
                               (Linux-specific) */
};

int semid;
union semun mysemun;
struct sembuf mysembuf;

int main(int argc, char const *argv[]) {   // main thread code
  int i;
  int key;
  key = ftok("./a.c",'a');
  if(key<0){
    printf("create key failure!\n");
    return -1;
  }
  printf("create key success, key=:%d\n",key);
  semid=semget(key,3,IPC_CREAT|0777);
  if (semid < 0) {
    //创建信号灯失败
    printf("create semaphore failure!\n");
    // return -1；
  }
  printf("create semaphore success, semid=%d\n", semid);
  system("ipcs -s");
  // init sem
  // mysemun.val=0;
  // semctl(semid,0,SETVAL,mysemun);
  mysembuf.sem_num=0;
  mysembuf.sem_flg=0;
  for (i = 0; i < 10; i++) {     //first
    usleep(100);
    printf("this is main fun i=%d\n", i);
  }
  // v operation   唤醒另外一个进程
  mysembuf.sem_op=1;
  semop(semid,&mysembuf,1);
  while(1);
  return 0;
}
