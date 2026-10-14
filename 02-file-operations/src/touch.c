#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv, char** envp) {

  // A file name is required
  if( argc < 2 ) {
    fprintf(stderr, "%s: missing file operand", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Creates the file when it does not exist with 0664 (rw-rw-r--, minus umask)
  // NOTE: unlike the real touch, it does not update the timestamps of an existing file
  int fd = open(argv[1], O_CREAT, 0664);
  if( fd == -1 ) {
    fprintf(stderr, "Can not create file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  // The file now exists; nothing was written, so it has size 0
  close(fd);

  return 0;
}
