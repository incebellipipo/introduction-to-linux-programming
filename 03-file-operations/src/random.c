#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {

  int fd = open("/dev/random", O_RDONLY);
  

}
