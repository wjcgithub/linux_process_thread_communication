#include "sys/types.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main(){
  int i;
  i=0;
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
