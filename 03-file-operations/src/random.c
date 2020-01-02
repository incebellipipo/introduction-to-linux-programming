#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {

  int _fd = open("/dev/random", O_RDONLY);

  if ( _fd < 0 ) {
    return EXIT_FAILURE;
  }
  
  float data;
  ssize_t result = read(_fd, &data, sizeof(float));
  fprintf(stdout, "random(%ld): %.50f\n", result, data);

  close(_fd);

  return 0;

}
