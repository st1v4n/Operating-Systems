#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

int main(void){
  if(execlp("sleep", "sleep", "60", (char*)NULL) == -1){
    err(1, "could not execute!");
  }
}

//execute the command sleep for 60 seconds
