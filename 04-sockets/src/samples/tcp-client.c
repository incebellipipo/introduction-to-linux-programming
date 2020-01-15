#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char** argv) {

  if(argc < 2){
    fprintf(stderr, "This command requires argument");
    exit(EXIT_FAILURE);
  }

  int port = 8080;
  int fd = 0;
  struct sockaddr_in serv_addr;
  char buf[1024] = {0};
  if(( fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }
  
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if(connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) {
    perror("connect");
    exit(EXIT_FAILURE);
  }

  write(fd, argv[1], strlen(argv[1]));
  int ret = read(fd, buf, 1024);

  fprintf(stdout, "%s\n", buf);

  close(fd);

  return 0;
}