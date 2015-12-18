#include "sys/types.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
void myfun(int signum){
    int i;
    i=0;
    while(i<10){
      printf("process signal signum%d\n", signum);
      sleep(1);
      i++;
    }
    return; //return to main function
}

int main(){
  int i;
  i=0;
  signal(14,myfun);
  printf("alarm function before\n");
  alarm(9);
  printf("alarm function after\n");
  while(i<20){
    i++;
    sleep(1);
    printf("process things i=%d\n",i);
  }
  return 0;
}
