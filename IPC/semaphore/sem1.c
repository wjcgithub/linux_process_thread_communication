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
void *fun(void *var){           //child thread code
  int j;
  //p wait
  // sem_wait(&sem);               //sleep
  mysembuf.sem_op=-1;
  semop(semid,&mysembuf,1);
  for (j = 0; j < 10; j++) { //second
    usleep(100);
    printf("this is child fun j=%d\n", j);
  }
}

int main(int argc, char const *argv[]) {   // main thread code
  int i;
  char str[]="Hello linux\n";
  pthread_t tid;
  int ret;
  semid=semget(IPC_PRIVATE,3,0777);
  if (semid < 0) {
    //创建信号灯失败
    printf("create semaphore failure!\n");
    return -1；
  }
  printf("create semaphore success, semid=%d\n", semid);
  system("ipcs -s");
  mysemun.val=0;
  // sem_init(&sem,0,0); // sem=0;
  //设置信号灯中某个信号量的值
  semctl(semid,0,SETVAL,mysemun);
  mysembuf.sem_num=0;
  mysembuf.sem_flg=0;

  ret=pthread_create(&tid,NULL,fun,(void *)str);
  if (ret<0) {
    printf("create thread failure\n");
    return -1;
  }
  for (i = 0; i < 10; i++) {     //first
    usleep(100);
    printf("this is main fun i=%d\n", i);
  }
  // v operation
  //执行信号量初始化之后的赋值操作
  // sem_post(&sem);
  mysembuf.sem_op=1;
  semop(semid,&mysembuf,1);
  while(1);
  return 0;
}
