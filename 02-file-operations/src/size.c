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

  // Assignment inside the condition: open and test in one step
  if((fp = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Can't open file to read: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  // Move the file position to the end of the file
  fseek(fp, 0, SEEK_END);

  // The offset at the end equals the size in bytes (use long/off_t for big files; fstat is the alternative)
  int s = ftell(fp);
  fprintf(stdout, "%d bytes\n", s);
  fclose(fp);

  return 0;
}
