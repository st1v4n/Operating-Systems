#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv){
  if(argc != 2){
    errx(1, "invalid number of args!");
  }
  pid_t s = fork();
  if(s == -1){
    err(2, "could not fork!");
  }
  if(s == 0){
    if(execlp(argv[1], argv[1], (char*)NULL) == -1){
      err(3, "could not exec!");
    }
  }
  int status;
  if(wait(&status) == -1){
    err(4, "could not wait!");
  }
  if(WIFEXITED(status)){
    if(WEXITEDSTATUS(status) != 0){
      err(5, "invalid exit status!");
    }
  }
  else{
    err(6, "child did not exit successfully!");
  }
  if(write(1, argv[1], strlen(argv[1])) == -1){
    err(7, "could not write!");
  }
  exit(0);
}
