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

#define BUFFER_SIZE 16

int main(int argc, char** argv) {

  if( argc < 2 ) {
    fprintf(stderr, "%s: missing file operand\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_CREAT | O_WRONLY, 0644);
  if ( fd == -1 ) {
    fprintf(stderr, "Can not create file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  char buf[BUFFER_SIZE] = {0};

  int istty = isatty(stdin->_fileno);

  int ret, n;
  do {
    memset(buf, 0, BUFFER_SIZE);
    ret = read(stdin->_fileno, buf, BUFFER_SIZE);
    write(fd, buf, ret);
    ioctl(stdin->_fileno, FIONREAD, &n);
    write(stdout->_fileno, buf, ret);
    if( ret == 0 && istty == 0) {
      break;
    }
  } while(1);

  close(fd);

  return 0;
}