#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <err.h>

//cut -d: -f7 /etc/passwd | sort | uniq -c| sort -n
int main(void){
  int pipeCut[2];
  if(pipe(pipeCut) == -1){
    err(1, "couldnt create pipe!");
  }
  pid_t s = fork();
  if(s == -1){
    err(2, "couldnt fork!");
  }
  if(s==0){
    close(pipeCut[0]);
    if(dup2(pipeCut[1], 1) == -1){
      err(3, "couldnt dup2");
    }
    close(pipeCut[1]);
    if(execlp("cut", "cut", "-d:", "-f7", "/etc/passwd", (char*)NULL) == -1){
      err(4, "coudlnt exec");
    }
  }
  close(pipeCut[1]);
  int pipeSort1[2];
  if(pipe(pipeSort1) == -1){
    err(5, "couldnt pipe!");
  }
  pid_t s2 = fork();
  if(s2 == -1){
    err(6, "coudlnt fork");
  }
  if(s2==0){
    close(pipeSort1[0]);
    if(dup2(pipeSort[1], 1) == -1){
      err(7, "couldnt dup2");
    }
    if(dup2(pipeCut[0], 0) == -1){
      err(8, "couldnt dup2");
    }
    close(pipeSort1[1]);
    if(execlp("sort", "sort", (char*)NULL) == -1){
      err(9, "couldnt dup2");
    }
  }
  close(pipeSort1[1]);
  int pipeUniq[2];
  if(pipe(pipeUniq) == -1){
    err(10, "couldnt pipe");
  }
  pid_t s3 = fork();
  if(s3==-1){
    err(11, "couldnt fork!");
  }
  if(s3==0){
    close(pipeUniq[0]);
    if(dup2(pipeUniq[1], 1) == -1){
      err(12, "couldnt dup2");
    }
    if(dup2(pipeSort1[0], 0) == -1){
      err(13, "coudlnt dup2");
    }
    close(pipeUniq[1]);
    if(execlp("exec", "exec", "-c", (char*)NULL) == -1){
      err(14, "couldnt exec");
    }
  }
  close(pipeUniq[1]);
  close(pipeCut[0]);
  close(pipeSort1[0]);
  if(dup2(pipeUniq[0], 0) == -1){
    err(16, "couldnt dup2");
  }
  for(int i=0;i<3;++i){
    if(wait(NULL) == -1){
      err(15, "coudlnt wait!");
    }
  }
  if(execlp("sort", "sort", "-n", (char*)NULL) == -1){
    err(16, "couldnt exec");
  }
  exit(0);
}
