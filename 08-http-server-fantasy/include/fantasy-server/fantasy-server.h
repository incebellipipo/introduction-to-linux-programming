#ifndef FANTASY_SERVER_H_
#define FANTASY_SERVER_H_

#include <sys/types.h>
// Macros

#define BACKLOG_MAX 128

// Datatypes
struct fantasy_client {
  int fd_;
  struct fantasy_client* next_; 
};

struct fantasy_server {
  int fd_;
  u_int16_t port_;
  u_int8_t max_conn_;
  struct fantasy_client* clients_;
};


// Functions
void init_server(struct fantasy_server * _server, u_int16_t port);

void start_server(struct fantasy_server *_server);

void client_callback(struct fantasy_client *_client);

void serve(struct fantasy_client *_client);

void destroy_server(struct fantasy_server* _server);

void main_loop();

// Global variables
int server_file_;

#endif