#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {

  if( argc < 2 ) {
    fprintf(stderr, "File name required!\n");
    exit(EXIT_FAILURE);
  }

  FILE *fp;

  if((fp = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Can't open file to read: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  fseek(fp, 0, SEEK_END);

  int s = ftell(fp);
  fprintf(stdout, "%d bytes\n", s);
  fclose(fp);

  return 0;
}
