#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>


// UNIX domain socket server: socket -> bind -> listen -> accept -> recv
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
  // The socket appears as a file at this path
  strcpy(addr.sun_path, "/var/tmp/dsocket");
  // Remove a stale socket file from a previous run, otherwise bind fails with EADDRINUSE
  unlink(addr.sun_path);
  fprintf(stdout, "binding...\n");
  // Creates the socket file in the filesystem
  if( bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0 ) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "listening...\n");
  // Allow up to 3 queued connections
  if(listen(fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  // accept returns a new descriptor (cl) dedicated to this client
  int len = sizeof(addr);
  if( (cl = accept(fd, (struct sockaddr*)&addr, &len)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }
  fprintf(stdout, "accepted...\n");

  // Receive until the peer closes the connection (recv returns 0)
  do {
    rc = recv(cl, buf, BUFSIZ, 0);
    // NOTE: rc is used as an index before the error check; with rc == -1 this writes out of bounds
    buf[rc] = '\0';
    if( rc < 0 ) {
      perror("recv");
      exit(EXIT_FAILURE);
    }
    printf("Client[%d]: %s", rc, buf);
  } while (rc != 0);
  
  return 0;
}