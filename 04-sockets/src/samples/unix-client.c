#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>


int main(int argc, char** argv) {
  fprintf(stdout, "starting\n");
  struct sockaddr_un addr;
  char buf[BUFSIZ];

  int fd, cl, rc;

  fprintf(stdout, "socket creating...\n");
  if( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0 ) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&addr, 0 , sizeof(addr));
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, "/var/tmp/dsocket");
  unlink(addr.sun_path);

  connect(fd, (struct sockaddr*)&addr, sizeof(addr));

  write(fd, argv[1],strlen(argv[1]));

  close(fd); 
  return 0;
}