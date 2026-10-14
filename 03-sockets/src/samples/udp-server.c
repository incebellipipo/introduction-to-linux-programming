#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

// UDP server: receives one datagram and echoes it back to whoever sent it
int main(int argc, char** argv) {

  int fd;
  char buf[BUFSIZ];
  int port = 8080;

  // servaddr = our address, cliaddr = filled in by recvfrom with the sender's address
  struct sockaddr_in servaddr, cliaddr;

  if( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(port);

  // Bind is required on the server so clients know where to send
  if( bind(fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0 ) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  int len, n;

  len = sizeof(cliaddr);

  // Blocks until a datagram arrives; no listen/accept for UDP
  n = recvfrom( fd, (char*)buf, BUFSIZ, 0, (struct sockaddr*)&cliaddr, &len);
  buf[n] = '\0';
  printf("Client[%d]: %s\n", n, buf);
  // Reply using the address recorded by recvfrom
  sendto(fd, (char*)buf, strlen(buf), MSG_CONFIRM, (struct sockaddr*)&cliaddr, len);

  return 0;
}
