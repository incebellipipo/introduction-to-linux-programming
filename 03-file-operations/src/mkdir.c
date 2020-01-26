#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#define BUFSIZE 128


int main() {

  char *dirname = (char*) malloc(BUFSIZE);
  printf("Enter a directory name: ");
  scanf("%s", dirname);

  if(mkdir(dirname, 0755) < 0) {
    perror("mkdir");
  }

  return 0;
}
