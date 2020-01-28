#include <stdio.h>
#include <stdlib.h>
#include <fantasy_server/fantasy_server.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

struct fantasy_server* init_server(u_int16_t port) {
  struct fantasy_server *_server; 
  _server = (struct fantasy_server*) malloc(sizeof(struct fantasy_server));
  _server->port_ = port;
  _server->state_ = SERSTAINIT;

  return _server;
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

  fprintf(stdout, "Listening on port: %d\n", _server->port_);
  _server->state_ = SERSTARUN;

  while((_server->state_ & SERSTAHALT) != SERSTAHALT ) {
    pthread_t servant; 
    struct fantasy_client c;
    
    int addr_len = sizeof(c.addr_);
    if((c.fd_ = accept(_server->fd_, (struct sockaddr*)&c.addr_, (socklen_t*)&addr_len)) < 0) {
      perror("accept");
      continue;
    }
    fprintf(stdout, "accepted: %d\n", c.fd_);

    pthread_create(&servant, NULL, (void*)&client_callback, &c);
  }
  close(_server->fd_);
  free(_server);
}

void client_callback(void* _c) {
  struct fantasy_client* _client = (struct fantasy_client*) _c;
  char buf[1024] = {0};
  int ret;
  ret = read(_client->fd_, buf, 1024);
  if( ret < 0 ) {
    perror("read");
    return;
  } 
  char response[1024];
  sprintf(response, "HTTP/1.0 200 OK\nContent-type: text/html; charset=UTF-8\n\n<h1>Hello world</h1><p>How are you %s?</p>", inet_ntoa(_client->addr_.sin_addr));
  write(_client->fd_, response, strlen(response));
  printf("[%ld]: %s", strlen(response), response);
  memset(&buf, 0, 1024);
  close(_client->fd_);
}

void destroy_server(struct fantasy_server* server) {
  server->state_ |= SERSTAHALT;
}