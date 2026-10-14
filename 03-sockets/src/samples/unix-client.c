#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>


// UNIX domain socket client: same API as TCP, but addressed by a filesystem path instead of IP:port
int main(int argc, char** argv) {
  fprintf(stdout, "starting\n");
  // struct sockaddr_un holds the socket's path name
  struct sockaddr_un addr;
  char buf[BUFSIZ];

  // cl and rc are unused in the client
  int fd, cl, rc;

  fprintf(stdout, "socket creating...\n");
  // AF_UNIX = local communication on the same machine, no network stack involved
  if( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0 ) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // Zero the structure, then set family and path
  memset(&addr, 0 , sizeof(addr));
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, "/var/tmp/dsocket");
  // NOTE: the client should not unlink; this deletes the server's socket file before connecting
  // (that is the server's job, see unix-server.c)
  unlink(addr.sun_path);

  // Connects to the path; return value is not checked
  connect(fd, (struct sockaddr*)&addr, sizeof(addr));

  // Send the message
  write(fd, argv[1],strlen(argv[1]));

  close(fd); 
  return 0;
}