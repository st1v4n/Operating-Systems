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
    errx(1, "invalid number of args");
  }
  int fd[2];
  if(pipe(fd) == -1){
    err(2, "could not create pipe!");
  }
  pid_t s = fork();
  if(s == -1){
    err(3, "could not fork!");
  }
  if(s == 0){
    close(fd[1]);
    int res;
    char sym;
    while((res = read(fd[0], &sym, 1)) > 0){
      if(write(1, &sym, 1) == -1){
        err(4, " error while writing!");
      }
    }
    if(res == -1){
      err(5, "error while reading!");
    }
    close(fd[0]);
  }
  else{
    close(fd[0]);
    if(write(fd[1], argv[1], strlen(argv[1])) == -1){
      err(6, "error while writing!");
    }
    close(fd[1]);
  }
  int status;
  if(wait(&status) == -1){
    err(7, "error while waiting!");
  }
  if(WIFEXITED(status)){
    if(WEXITSTATUS(status) != 0){
      err(8, "invalid exit status from child!");
    }
  }
  else{
    err(9, "child did not finish!");
  }
}
