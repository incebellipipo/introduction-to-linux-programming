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
  char buf[1024];

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
  fprintf(stdout, "binding...\n");
  if( bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0 ) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "listening...\n");
  if(listen(fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  int len = sizeof(addr);
  if( (cl = accept(fd, (struct sockaddr*)&addr, &len)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }
  fprintf(stdout, "accepted...\n");

  do {
    rc = recv(cl, buf, 1024, 0);
    buf[rc] = '\0';
    if( rc < 0 ) {
      perror("recv");
      exit(EXIT_FAILURE);
    }
    printf("Client[%d]: %s", rc, buf);
  } while (rc != 0);
  
  return 0;
}