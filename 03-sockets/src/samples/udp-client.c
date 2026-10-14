#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

// UDP client: connectionless, so there is no connect/accept; each message is a datagram
int main(int argc, char** argv) {

  int fd;
  char buf[BUFSIZ];
  int port = 8080;
  struct sockaddr_in servaddr;

  // SOCK_DGRAM = datagrams (UDP)
  if( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // Destination address; INADDR_ANY (0.0.0.0) is routed to the local host here
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(port);

  // len is in/out for recvfrom: size of the address buffer in, size of the sender address out
  int len, n;

  len = sizeof(servaddr);


  // Send one datagram to the given address; argv[1] is not validated (crashes without an argument)
  // MSG_CONFIRM is a Linux hint that the reply path is known
  sendto(fd, (char*)argv[1], strlen(argv[1]), MSG_CONFIRM, (struct sockaddr*)&servaddr, len);

  // Wait for the answer; the sender's address is stored in servaddr
  n = recvfrom( fd, (char*)buf, BUFSIZ, 0, (struct sockaddr*)&servaddr, &len);
  // recvfrom does not null terminate, so do it before printing
  buf[n] = '\0';
  printf("Server[%d]: %s\n", n, buf);
  
  close(fd);

  return 0;
}