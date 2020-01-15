#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {

  int fd;
  char buf[1024];
  int port = 8080;

  struct sockaddr_in servaddr;

  if( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(port);

  int len, n;

  len = sizeof(servaddr);

  sendto(fd, (char*)argv[1], strlen(argv[1]), MSG_CONFIRM, (struct sockaddr*)&servaddr, len);

  n = recvfrom( fd, (char*)buf, 1024, 0, (struct sockaddr*)&servaddr, &len);
  buf[n] = '\0';
  printf("Server[%d]: %s\n", n, buf);
  
  close(fd);

  return 0;
}