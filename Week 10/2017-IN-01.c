#include <fcntl.h>
   #include <sys/stat.h>
   #include <err.h>
   #include <stdint.h>
   #include <unistd.h>
  
   struct triplet{
       uint16_t offset;
       uint8_t len;
      uint8_t blank;
  };
 
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
      if(argc != 5){
          errx(1, "file number error");
      }
      int f1dat, f1idx;
      f1dat = safeOpen(argv[1], O_RDONLY);
      f1idx = safeOpen(argv[2], O_RDONLY);
      struct stat s;
      if(fstat(f1idx, &s) == -1){
          err(2, "error while fstat");
      }
      if(s.st_size % 4 != 0){
          errx(3, "invalid size !");
      }
     int f1dat_size;
      if(fstat(f1dat, &s) == -1){
          err(4, "error while fstat");
      }
      f1dat_size = s.st_size;
      int f2dat, f2idx;
      f2dat = safeOpenCreate(argv[3], O_CREAT | O_TRUNC | O_WRONLY, 0666);
      f2idx = safeOpenCreate(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0666);
      struct triplet t;
      uint16_t offset = 0;
      while(safeRead(f1idx, &t, sizeof(t))){
          if(t.offset + (uint16_t)t.len > (uint16_t)f1dat_size){
              errx(5, "invalid data");
          }
          safeLseek(f1dat, t.offset, SEEK_SET);
          uint8_t symbol;
          safeRead(f1dat, &symbol, 1);
          if(symbol < 0x41 || symbol > 0x5A){
              continue;
          }
          safeWrite(f2dat, &symbol, 1);
          for(int i=0;i<t.len-1;i++){
              safeRead(f1dat, &symbol, 1);
              safeWrite(f2dat, &symbol, 1);
          }
          struct triplet t_out;
          t_out.offset = offset;
          t_out.len = t.len;
          t_out.blank = 0;
          safeWrite(f2idx, &t_out, sizeof(t_out));
          offset += t.len;
 
      }
     close(f1dat);
     close(f1idx);
     close(f2dat);
     close(f2idx);
     return 0;
 }
