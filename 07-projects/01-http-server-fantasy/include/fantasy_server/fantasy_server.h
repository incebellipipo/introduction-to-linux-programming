#ifndef FANTASY_SERVER_H_
#define FANTASY_SERVER_H_

#include <sys/types.h>
#include <netinet/in.h>
// Macros

#define BACKLOG_MAX 128

#define SERSTAINIT    0b00000001
#define SERSTARUN     0b00000010
#define SERSTAHALT    0b00000100

// Datatypes
struct fantasy_client {
  int fd_;
  struct sockaddr_in addr_;
  struct fantasy_client* next_; 
};

struct fantasy_server {
  int fd_;
  u_int16_t port_;
  u_int8_t max_conn_;
  u_int8_t state_;
  struct fantasy_client* clients_;
};


// Functions
struct fantasy_server * init_server(u_int16_t port);

void start_server(struct fantasy_server *_server);

void client_callback(void*_client);

void destroy_server(struct fantasy_server* _server);

void main_loop();

// Global variables
int server_file_;

#endif