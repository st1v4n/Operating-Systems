#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <stdio.h>

int main(void){
  int filedesc1;
  int filedesc2;
  if((filedesc1 = open("file1.txt", O_RDONLY)) == -1){
    err(1, "Unable to open the first file!");
  }
  if((filedesc2 = open("file2.txt", O_CREAT | O_WRONLY, 0777)) == -1){
    close(filedesc1);
    err(2, "Unable to open the second file!");
  }
  chat symbol;
  int res;
  while((res = read(filedesc1, symbol, sizeof(char))) == 1){
    if(write(filedesc2, symbol, sizeof(char)) != res){
      close(filedesc1);
      close(filedesc2);
      err(3, "Error while writing to file!");
    }
  }
  if(res != 0){
    close(filedesc1);
    close(filedesc2);
    err(4, "Error while reading from the file!");
  }
  close(filedesc1);
  close(filedesc2);
  exit(0);
}
