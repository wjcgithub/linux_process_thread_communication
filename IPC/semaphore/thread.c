#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
int thread_inter=0;
void *fun(void *var){   //child thread code
  int j;
  while (thread_inter == 0) {
    for (j = 0; j < 10; j++) { //second
      usleep(100);
      printf("this is child fun j=%d\n", j);
    }
  }
}

int main(int argc, char const *argv[]) {   // main thread code
  int i;
  char str[]="Hello linux\n";
  pthread_t tid;
  int ret;
  ret=pthread_create(&tid,NULL,fun,(void *)str);
  if (ret<0) {
    printf("create thread failure\n");
    return -1;
  }
  for (i = 0; i < 10; i++) {     //first
    usleep(100);
    printf("this is main fun i=%d\n", i);
  }
  while(1);
  return 0;
}
