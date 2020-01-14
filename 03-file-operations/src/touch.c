#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv, char** envp) {

  if( argc < 2 ) {
    fprintf(stderr, "%s: missing file operand", argv[0]);
    exit(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_CREAT, 0664);
  if( fd == -1 ) {
    fprintf(stderr, "Can not create file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  close(fd);

  return 0;
}
