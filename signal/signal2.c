#include "sys/types.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
void myfun(int signum){
  int i;
  i=0;
  while (i<5) {
    printf("receive signum=%d, i=%d\n", signum,i);
    sleep(1);
    i++;
  }
  return;
}

void myfun1(int signum){
  printf("receive signum=%d\n", signum);
  //现在回收就不会阻塞进程了
  wait(NULL);
  return;
}

int main(){
  pid_t pid;
  pid = fork();
  if(pid>0){
    int i;
    i=0;
    // 处理信号
    signal(10,myfun);
    signal(17,myfun1);
    //回收子进程资源，因为wait函数是阻塞的，必须等待子进程执行完才行，所以，这里我们使用子进程的exit函数执行，然后捕获在处理，exit实际上执行的是kill(getppid(),17)
    // wait(NULL);
    while (1) {
      printf("parent process things , i=%d\n", i);
      sleep(1);
      i++;
    }
  }
  if(pid==0){
    sleep(10);
    //发送10号信号，发给父进程
    kill(getppid(),10);
    sleep(10);
    exit(0);  // == kill(getppid(),17)
  }
  return 0;
}
