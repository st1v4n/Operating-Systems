#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

struct triplet{
    uint16_t offset;
    uint8_t first;
    uint8_t second;
};

int main(int argc, char** argv){
  if(agrc != 4){
    err(1, "Invalid number of arguments!");
  }
  int fd1, fd2, patch;
  if(fd1 = open(argv[1], O_RDONLY) == -1){
    err(2, "Cannot open first file!");
  }
  if(fd2 = open(argv[2], O_RDONLY) == -1){
    err(3, "Cannot open the second file!");
  }
  struct stat statFirst;
  struct stat statSecond;
  if(stat(fd1, &statFirst) == -1){
    err(4, "Cannot stat from file 1");
  }
  if(stat(fd2, &statSecond) == -1){
    err(5, "Cannot stat from file 2");
  }
  if(statFirst.st_size != statSecond.st_size){
    err(6, "The sizes of the files must be equal!");
  }
  if(patch = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666) == -1){
    err(7, "Cannot open the third file!");
  }
  struct triplet t;
  int res1;
  int res2;
  uint8_t byte1;
  uint8_t byte2;
  uint16_t counter = 1;
  while(res1 = read(fd1, &byte1, 1) > 0){
    if(res2 = read(fd2, &byte2, 1) == -1){
      err(8, "error while reading from second file!");
    }
    if(byte1 != byte2){
      t.offset = counter;
      t.first = byte1;
      t.second = byte2;
      if(write(patch, &t, sizeof(triplet)) == -1){
        err(9, "error while writing to file 3");
      }
    }
    counter++;
  }
  if(res1 == -1){
    err(1, "error while reading!");
  }
  close(fd1);
  close(fd2);
  close(patch);
  exit(0);
}
