#include "sys/types.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main(){
  printf("刚开始父进程睡眠状态(S+),子进程停止状态（T+），8秒钟后，父进程变成运行状态（R+），子进程变成僵尸进程（Z+），因为父进程没有为子进程回收资源\n");
  pid_t pid;
  pid = fork();
  if(pid>0){
    sleep(8);
    if(waitpid(pid,NULL,WNOHANG) == 0){
      kill(pid,9);
    }
    while(1);
  }
  if(pid==0){
    printf("raise function before\n");
    raise(SIGTSTP);
    printf("raise function after\n");
    exit(0);
  }
  return 0;
}
