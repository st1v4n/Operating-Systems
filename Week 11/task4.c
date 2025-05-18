#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

int main(void){
  pid_t s = fork();
  if(s == -1){
    err(1, "could not fork!");
  }
  if(s == 0){
    for(int i = 0; i < 1000; ++i){
      if(write(1, "child", 5) == -1){
        err(2, "error while writing from child!");
      }
    }
  }
  else{
    for(int i = 0; i<1000; ++i){
      if(write(1, "parent", 6) == -1){
        err(3, "error while writing!");
      }
    }
  }
  int status;
  if(wait(&status) == -1){
    err(4, "error while waiting!");
  }
  if(WIFEXITED(status)){
    if(WEXITEDSTATUS(status) != 0){
      err(5, "not exited successfulyy!");
    }
    else{
      exit(0);
    }
  }
  else{
    err(6, "child process did not exit!");
  }
}
