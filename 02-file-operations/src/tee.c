#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h> 
#include <sys/select.h>

// Small buffer on purpose, to show data being handled in chunks
#define BUFFER_SIZE 16

int main(int argc, char** argv) {

  if( argc < 2 ) {
    fprintf(stderr, "%s: missing file operand\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // O_CREAT creates the file if missing, O_WRONLY write only; 0644 = rw-r--r-- (minus umask)
  // NOTE: no O_TRUNC, so an existing longer file keeps its tail
  int fd = open(argv[1], O_CREAT | O_WRONLY, 0644);
  if ( fd == -1 ) {
    fprintf(stderr, "Can not create file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  char buf[BUFFER_SIZE] = {0};

  // Distinguish interactive terminal input from a pipe or redirected file
  int istty = isatty(stdin->_fileno);

  // ret = bytes read; n receives the bytes pending in the input queue (not used afterwards)
  int ret, n;
  do {
    // Clear the buffer so no stale data remains from the previous iteration
    memset(buf, 0, BUFFER_SIZE);
    // Blocks until data is available; returns 0 on end-of-file
    ret = read(stdin->_fileno, buf, BUFFER_SIZE);
    // Copy the chunk to the file...
    write(fd, buf, ret);
    ioctl(stdin->_fileno, FIONREAD, &n);
    // ...and to standard output, which is what makes this 'tee'
    write(stdout->_fileno, buf, ret);
    // EOF on a pipe/file means stop; on a terminal we keep looping (Ctrl+C to quit)
    if( ret == 0 && istty == 0) {
      break;
    }
  } while(1);

  close(fd);

  return 0;
}