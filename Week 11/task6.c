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
    errx(1, "invalid number of arguments!");
  }
  int fd;
  if( (fd = open(argv[1], O_WRONLY)) == -1){
    err(2, "could not open file!");
  }
  if(write(fd, "fo", 2) == -1){
    err(2, "error while writing!");
  }
  pid_t s = fork();
  if(s == -1){
    err(3, "could not fork!");
  }
  if(s == 0){
    if(write(fd, "bar", 3) == -1){
      err(4, "could not write!");
    }
    close(fd);
  }
  int status = 0;
  if(wait(&status) == -1){
    err(5, "could not wait!");
  }
  if(WIFEXITED(status)){
    if(WEXITSTATUS(status) != 0){
      err(6, "error in child process!");
    }
  }
  else{
    err(7, "child did not exit successfully!");
  }
  if(write(fd, "o", 1) == -1){
    err(8, "could not write!");
  }
  close(fd);
  exit(0);
}
