#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <err.h>
#include <unistd.h>

int main(int argc, char** argv){
  if(argc != 2){
    err(1, "Invalid number of arguments!");
  }
  const char* fileName = argv[1];
  int filedesc1;
  if((filedesc1 = open(fileName, O_RDONLY)) == -1){
    err(2, "Unable to open the file!");
  }
  chat symbol;
  int lineCount = 1;
  int res;
  while((res = read(filedesc1, &symbol, sizeof(char))) == 1){
    if(symbol == '\n'){
      if(write(1, &symbol, sizeof(char)) != res){
        close(filedesc1);
        err(3, "Error while writing!");
      }
      lineCount++;
      if(lineCount == 11){
        break;
      }
    }
    if(write(1, &symbol, sizeof(char)) != res){
      close(filedesc1);
      err(4, "Error while writing!");
    }
  }
  if(res == -1){
    close(filedesc1);
    err(5, "Error while reading from file!");
  }
  close(filedesc1);
  exit(0);
}
