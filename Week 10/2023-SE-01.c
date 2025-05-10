#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <err.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

int safeOpen(char* fileName, int flags){
      int fd;
      if((fd = open(fileName, flags)) == -1){
          err(50, "error while opening!");
      }
      return fd;
  }
 
  int safeOpenCreate(char* fileName, int flags, mode_t mode){
    int fd;
    if((fd = open(fileName, flags, mode)) == -1){
      errx(100, "Error while opening the file!");
    }
    return fd;
  }
 
  int safeRead(int fd, void* buff, size_t count){
    int res;
    if((res = read(fd, buff, count)) == -1){
      err(200, "Error while reading!");
    }
    return res;
  }
 
  int safeWrite(int fd, void* buff, size_t count){
    int res;
    if((res = write(fd, buff, count)) == -1){
      err(300, "Error while writing!");
    }
    return res;
  }
 
    off_t safeLseek(int fd, off_t offset, int whence){
    off_t res;
    if((res = lseek(fd, offset, whence)) == -1){
      err(400, "Errow while lseeking");
    }
    return res;
  }

int main(int argc, char** argv){
  if(argc != 3){
    errx(1, "invalid number of args!");
  }
  int stream, message;
  stream = safeOpen(argv[1], O_RDONLY);
  message = safeOpenCreate(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0666);

  uint8_t read_byte;
  off_t currPos = 0;
  while(safeRead(stream, &read_byte, 1)){
    if(read_byte == 0x55){
      uint8_t check_sum;
      check_sum = read_byte;
      uint8_t n;
      safeRead(stream, &n, 1);
      check_sum ^= n;
      for(int i=0;i<n-1;++i){
        safeRead(stream, &read_byte, 1);
        check_sum ^= read_byte;
      }
      safeRead(stream, &read_byte, 1);
      if(check_sum == read_byte){
        safeLseek(stream, currPos, SEEK_SET);
        for(int i=0;i<n+3;++i){
          safeRead(stream, &read_byte, 1);
          safeWrite(message, &read_byte, 1);
        }
      }
    }
    currPos++;
  }
  
  close(message);
  close(stream);
  return 0;
}
