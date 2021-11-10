#include <stdio.h>
#include <stdlib.h>

int main () {
  FILE * file = fopen("TestFile", "w+");
  fprintf(file, "test\n");
  fclose(file);
  exit(0);
}
