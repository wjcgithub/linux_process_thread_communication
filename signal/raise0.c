#include "sys/types.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main(){
  pid_t pid;
  pid = fork();
  if(pid>0){
    printf("111111111111-parent-111111111111\n");
    sleep(8);
    if(waitpid(pid,NULL,WNOHANG) == 0){
      kill(pid,9);
    }
    //使用wait回收资源
    wait(NULL);
    while(1);
  }
  if(pid==0){
    printf("111111111111-child-111111111111\n");
    printf("raise function before\n");
    raise(SIGTSTP);
    printf("raise function after\n");
    exit(0);
  }
  return 0;
}
