#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <stdint.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char** argv){
  if(argc != 3){
    errx(1, "invalid number of args!");
  }
  char N = argv[1][0] - '0';
  char D = argv[2][0] - '0';
  int childFinished[2];
  int parentFinished[2];
  if(pipe(childFinished) == -1){
    err(2, "couldnt pipe");
  }
  if(pipe(parentFinished) == -1){
    err(3, "couldnt pipe");
  }
  char dummy = 'd';
  pid_t s = fork();
  if(s==-1){
    err(4, "couldnt fork");
  }
  if(s == 0){
    close(parentFinished[1]);
    close(childFinished[0]);
  }
  else{
    close(parentFinished[0]);
    close(childFinished[1]);
  }
  for(int i=0;i<N;++i){
   if(s==0){
    if(read(parentFinished[0], &dummy, 1) == -1){
      err(10, "couldnt read");
    }
    if(write(1, "DONG", 4) == -1){
      err(15, "couldnt write");
     }
    if(write(childFinished[1], &dummy, 1) == -1){
      err(11, "couldnt write!");
    }
    if(i == N-1){
      close(parentFinished[0]);
      close(childFinished[1]);
      exit(0);
    }
   } 
   else{
     if(write(1, "DING", 4) == -1){
       err(8, "couldnt write");
     }
     if(write(parentFinished[1], &dummy, 1) == -1){
       err(9, "couldnt write");
     }
     if(read(childFinished[0], &dummy, 1) == -1){
       err(12, "couldnt read");
     }
     if(sleep(D) == -1){
       err(13, "couldnt sleep!");
     }
   }
  }
  int status;
  if(wait(&status) == -1){
    err(5, "couldnt wait");
  }
  if(!WIFEXITED(status)){
    err(6, "child did not finish");
  }
  if(WEXITSTATUS(status) != 0){
    err(7, "child did not exit with status 0!");
  }
  close()
}
