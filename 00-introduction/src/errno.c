#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {

  FILE *fp;
  fopen("/etc/canttouch", "w");

  fprintf(stderr, "[%d]: %s\n", errno, strerror(errno));

  return 0;
}