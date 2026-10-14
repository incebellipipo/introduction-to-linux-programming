#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
// Maximum directory name length we are prepared to read
#define BUFSIZE 128


int main() {

  // Heap buffer for the name (never freed; fine for a short lived program)
  char *dirname = (char*) malloc(BUFSIZE);
  printf("Enter a directory name: ");
  // NOTE: no width limit, so input over 127 characters overflows the buffer; use "%127s"
  scanf("%s", dirname);

  // mkdir(2) creates the directory with mode 0755 (rwxr-xr-x), filtered by the process umask
  if(mkdir(dirname, 0755) < 0) {
    // Prints "mkdir: <strerror(errno)>" to stderr, e.g. 'File exists'
    perror("mkdir");
  }

  return 0;
}
