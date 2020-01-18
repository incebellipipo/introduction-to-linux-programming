#include <stdio.h>
#include <stdlib.h>
#include <fantasy-server/fantasy-server.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

void init_server(struct fantasy_server *_server, u_int16_t port) {
  _server = (struct fantasy_server*) malloc(sizeof(struct fantasy_server));
  _server->port_ = port;
}

void start_server(struct fantasy_server *_server) {
  if( (_server->fd_ = socket(AF_INET, SOCK_STREAM, 0)) == 0 ) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  int opt = 1;
  if( setsockopt(_server->fd_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) ) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(_server->port_);

  if(bind(_server->fd_, (struct sockaddr* )&addr, sizeof(addr)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if(listen(_server->fd_, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  int cfd;
  int addr_len = sizeof(addr);
  if((cfd = accept(_server->fd_, (struct sockaddr*)&addr, (socklen_t*)&addr_len)) < 0) {
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
  close(_server->fd_);
}