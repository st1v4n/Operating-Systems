#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <sys/wait.h>

int main(void){
  char prompt[4] = ">>";
  while(write(1, prompt, strlen(prompt)) > 0){
    char buff[256];
    if(read(0, buff, 256) == -1){
      err(2, "error while reading!");
    }
    buff[strlen(buff) - 1] = '\0';
    if(strcmp(buff, "exit")){
      exit(0);
    }
    pid_t s = fork();
    if(s == -1){
      err(4, "fork failed");
    }
    if(s == 0){
      if(execlp(buff, buff, (char*)NULL) == -1){
        err(5, "couldnt exec");
      }
    }
    int status;
    if(wait(&status) == -1){
      err(3, "waiting failed");
    }
    if(WIFEXITED(status)){
      if(WEXITSTATUS(status) != 0 ){
        err(7, "child did not exit successfully!");
      }
    }
    else{
      err(6, "child did not exit!");
    }
  }
  err(1, "error while writing prompt!");
}
