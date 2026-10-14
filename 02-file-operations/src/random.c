#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {

  // Low level I/O: open returns a small integer file descriptor, or -1 on error
  // /dev/random is a device file supplying kernel entropy
  int _fd = open("/dev/random", O_RDONLY);

  if ( _fd < 0 ) {
    fprintf(stderr, "Can't open /dev/random: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  // Read the raw bytes of a float; the bit pattern is random, so the value can even be NaN
  float data;
  // read returns the number of bytes actually read (may be fewer than requested), or -1
  ssize_t result = read(_fd, &data, sizeof(float));
  fprintf(stdout, "random(%ld): %.50f\n", result, data);

  // Release the descriptor
  close(_fd);

  return 0;

}
