#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdio.h>

struct pair{
    uint32_t x;
    uint32_t y;
};

int main(int argc, char** argv){
  if(argc != 4){
    err(1, "Invalid number of files!");
  }
  int fd1, fd2, fd3;
  if(fd1 = open(argv[1], O_RDONLY) == -1){
    err(2, "Cannot open first file!");
  }
  struct stat s;
  if(fstat(fd1, &s) == -1){
    err(1, "Fstat failed for the first file!");
  }
  if(s.st_size % 8 != 0){
    err(1, "Incorrect size of the first file!");
  }
  if(fd2 = open(argv[2], O_RDONLY) == -1){
    err(3, "Cannot open second file!");
  }
  if(fstat(fd2, &s) == -1){
    err(2, "Fstat failed for the second file!");
  }
  if(s.st_size % 4 != 0){
    err(2, "Incorrect size of the second file!");
  }
  if(fd3 = open(argv[3], O_WRONLY | O_CREAT, 0777) == -1){
    err(4, "cannot open third file!");
  }
  struct pair data;
  int res;
  while(res = read(fd1, &data, sizeof(pair)) > 0){
    if(lseek(fd2, data.x*4, SEEK_SET) == -1){
      err(5, "Error while seeking!");
    }
    uint32_t read_numbers;
    for(uint32_t i = 0; i < data.y; i++){
      if(read(fd2, &read_numbers, 4) == -1){
        err(6, "error while reading from the second file!")
      }
      if(write(fd3, &read_numbers, 4) == -1){
        err(7, "error while writing to the third file!");
      }
    }
  }
  if(res == -1){
    err(8, "Error while reading from the first file!");
  }
  close(fd1);
  close(fd2);
  close(fd3);
  exit(0);
}
