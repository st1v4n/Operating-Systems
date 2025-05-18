#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv){
  if(argc != 2){
    errx(1, "invalid number of files!");
  }
  int fd[2];
  if(pipe(fd) == -1){
    err(1, "pipe fail");
  }
  pid_t s = fork();
  if(s == -1){
    err(2, "could not fork!");
  }
  if(s == 0){
    close(fd[0])
    if(dup2(fd[1], 1) == -1){
      err(3, "dup2 fail");
    }
    if(execlp("cat", "cat", argv[1], (char*)NULL) == -1){
      err(4, "exec fail");
    }
    close(fd[1]);
  }
  else{
    close(fd[1]);
    if(dup2(fd[0], 0) == -1){
      err(5, "dup2 fail");
    }
    if(execlp("sort", "sort", (char*)NULL) == -1){
      err(6, "exec fail");
    }
    close(fd[0]);
  }
}
