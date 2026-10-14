#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {

  // NOTE: fp is unused; the return value of fopen is thrown away
  FILE *fp;
  // Opening a file we are not allowed to write fails and sets errno (EACCES, or ENOENT/EROFS depending on the system)
  fopen("/etc/canttouch", "w");

  // errno is a thread-local global set by failing calls; strerror() turns it into a human-readable message
  // Only valid right after a failure: a successful call may leave it unchanged or modified
  fprintf(stderr, "[%d]: %s\n", errno, strerror(errno));

  return 0;
}