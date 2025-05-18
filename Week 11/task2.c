#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

int main(int argc, char** argv){
  if(argc != 2){
    errx(1, "invalid number of arguments!");
  }
  if(execlp("ls", "ls", argv[1], (char*)NULL) == -1){
    err(2, "could not execute!");
  }
}

// execute the command ls with exactly 1 argument
