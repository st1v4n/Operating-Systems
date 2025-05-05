#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int safeOpen(char* fileName, int flags, mode_t mode){
  int fd;
  if(fd = open(fileName, flags, mode) == -1){
    errx(100, "Error while opening the file!");
  }
  return fd;
}

int safeRead(int fd, void* buff, size_t count){
  int res;
  if(res = read(fd, buff, count) == -1){
    err(200, "Error while reading!");
  }
  return res;
}

int safeWrite(int fd, void* buff, size_t count){
  int res;
  if(res = write(fd, buff, count) == -1){
    err(300, "Error while writing!");
  }
  return res;
}

off_t safeLseek(int fd, off_t offset, int whence){
  off_t res;
  if(res = lseek(fd, offset, whence) == -1){
    err(400, "Errow hile lseeking");
  }
  return res;
}

int main(void){
  exit(0);
}
