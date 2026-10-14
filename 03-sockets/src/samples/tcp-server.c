#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

// TCP server: socket -> setsockopt -> bind -> listen -> accept -> read
int main(int argc, char** argv) {
  int port = 8080;
  int fd;
  // Create the listening socket (IPv4, TCP)
  // NOTE: socket() returns -1 on error, not 0
  if( (fd = socket(AF_INET, SOCK_STREAM, 0)) == 0 ) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  // SO_REUSEADDR lets us rebind immediately after a restart instead of waiting for TIME_WAIT sockets to expire
  int opt = 1;
  if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) ) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in addr;
  // Listen on every local interface (INADDR_ANY), port in network byte order
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  // Attach the socket to the address/port; fails with EADDRINUSE if taken
  if(bind(fd, (struct sockaddr* )&addr, sizeof(addr)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // Mark as passive socket; 3 is the backlog of pending connections
  if(listen(fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  // accept blocks until a client connects and returns a NEW descriptor for that client;
  // the original fd keeps listening. addr is filled with the client's address
  int cfd;
  int addr_len = sizeof(addr);
  if((cfd = accept(fd, (struct sockaddr*)&addr, (socklen_t*)&addr_len)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  // Echo loop: read until the client closes (read returns 0)
  char buf[BUFSIZ] = {0};
  int ret;
  do {
    ret = read(cfd, buf, BUFSIZ);
    if( ret < 0 ) {
      perror("read");
      exit(EXIT_FAILURE);
    }
    printf("Client[%d]: %s", ret, buf);
    // Clear the buffer so a short message does not show leftovers of a longer one
    memset(&buf, 0, BUFSIZ);
  } while( ret != 0);
  // Close the client connection, then the listening socket
  // This server handles a single client and then exits
  close(cfd);
  close(fd);

  return 0;
}