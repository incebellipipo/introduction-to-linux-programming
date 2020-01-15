#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
  int port = 8080;
  int fd;
  if( (fd = socket(AF_INET, SOCK_STREAM, 0)) == 0 ) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  int opt = 1;
  if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) ) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  if(bind(fd, (struct sockaddr* )&addr, sizeof(addr)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if(listen(fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  int cfd;
  int addr_len = sizeof(addr);
  if((cfd = accept(fd, (struct sockaddr*)&addr, (socklen_t*)&addr_len)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  char buf[1024] = {0};
  int ret;
  do {
    ret = read(cfd, buf, 1024);
    if( ret < 0 ) {
      perror("read");
      exit(EXIT_FAILURE);
    }
    printf("Client[%d]: %s", ret, buf);
    memset(&buf, 0, 1024);
  } while( ret != 0);
  close(cfd);
  close(fd);

  return 0;
}