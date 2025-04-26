//Реализирайте команда wc, с един аргумент подаден като входен параметър.
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char** argv){
  if(argc != 2){
    err(1, "Invalid number of arguments!");
  }
  const char* fileName = argv[0];
  int filedesc1;
  if((filedesc = open(fileName, O_RDONLY)) == -1){
    err(2, "Unable to open the file!");
  }
  char symbol;
  int res;
  int lines = 0;
  int words = 0;
  int chars = 0;
  char previous = ' ';
  while((res = read(filedesc1, &symbol, sizeof(char))) == 1){
    chars++;
    if(symbol == '\n'){
      lines++;
    }
    if(symbol == ' '){
      if(previous != ' '){
        words++;
      }
    }
    previous = symbol;
  }
  if(res != 0){
    close(filedesc1);
    err(3, "Error while reading from file!");
  }
  dprintf(1, "Files %s has:\nLines: %d\nWords: %d\nCharacters: %d\n", file_name, lines, words, chars);
  close(filedesc1);
  exit(0);
}
