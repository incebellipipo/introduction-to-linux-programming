#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fantasy_server/fantasy_server.h>

struct fantasy_server* server = NULL;

void sig_handle(int sig) {
  fprintf(stdout, "Closing server\n");
  if(server) {
    destroy_server(server);
  }
}

int main(int argc, char* argv[]) {

  signal(SIGINT, sig_handle);

  server = init_server(8080);

  start_server(server);

  return 0;
}