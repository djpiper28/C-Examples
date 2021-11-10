#include <stdlib.h>
#include <stdio.h>

int main() {
  int fid[2];
  pipe(fid);
  int id = fork();
  if (id != 0) {
    char str[] = "I am writing to a pipe";
    write(fid[1], str, sizeof(str));
    close(fid[1]);
    exit(0);
  } else {
    wait();
    char buff[256];
    read(fid[0], buff, 256);
    printf("%s", buff);
    close(fid[0]);
  }
  return 0;
}
