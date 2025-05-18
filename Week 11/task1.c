#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

int main(void){
  if(execlp("date", "date", (char*)NULL) == -1){
    err(1, "could not execute!");
  }
}
// Execute the command ,,date''
