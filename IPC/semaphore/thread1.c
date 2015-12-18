/**
*  使用信号量做线程的通信。 主线程先执行，子线程后执行
**/
#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"
//声明信号量
sem_t sem;
void *fun(void *var){           //child thread code
  int j;
  //p wait
  sem_wait(&sem);               //sleep
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
  sem_init(&sem,0,0); // sem=0;
  ret=pthread_create(&tid,NULL,fun,(void *)str);
  if (ret<0) {
    printf("create thread failure\n");
    return -1;
  }
  for (i = 0; i < 10; i++) {     //first
    usleep(100);
    printf("this is main fun i=%d\n", i);
  }
  sem_post(&sem);
  while(1);
  return 0;
}
