#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#define PORT 8080
struct req {
	int fd;
	struct sockaddr_in addr;
} req;

// TCP Socket Server!!
int is_prime(int n) {
	if (n <= 1) return 0;
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	for(int i = 3 ; i <= n/2 ; i+=2) {
		if(n%i==0)
			return 0;
	}
	return 1;
}

void* serve(void* r) {
  struct req* rq = (struct req*)r;
  int cfd = rq->fd;
  char buf[BUFSIZ];
  read(cfd, buf, BUFSIZ);
	
  char * request_line = strtok(buf, "\n");
  char * request_type = strtok(request_line, " ");
  char * request_route = strtok(NULL, " ");
  if( strstr(request_route, "favico") ){
    return NULL;
  }
  strtok(request_route, "=");
  char * requested_number = strtok(NULL, "=");


  char response[BUFSIZ];
  sprintf(response, 
      "HTTP/1.0 200 OK\n"
      "Content-type: text/html; charset=UTF-8\n"
      "\n"
      "<h1>Hello</h1><p>%s!</p><h2>%d %s</h2>",
      inet_ntoa(rq->addr.sin_addr),
			atoi(requested_number),
      is_prime(atoi(requested_number))?"is prime":"is not prime"
      );
  write(cfd, response, strlen(response));
  close(cfd);
}

int main(int argc, char** argv) {
 
  int fd = socket(AF_INET, SOCK_STREAM, 0 /* man 7 ip */);
  if( fd < 0 ){
    perror("socket");
    exit(EXIT_FAILURE);
  }
  int opt = 1;
  setsockopt(
      fd, 
      SOL_SOCKET, 
      SO_REUSEADDR | SO_REUSEPORT, 
      &opt, 
      sizeof(opt)
  );

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(PORT);

  int retval = bind(
      fd,
      (struct sockaddr*)&serv_addr,
      sizeof(struct sockaddr_in)
  );
  if( retval < 0 ) {
    perror("bind");
    exit(EXIT_FAILURE);
  }
  
  retval = listen(fd, 1024);
  if( retval < 0 ) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  
  while(1){
    struct sockaddr_in cli_addr;
    socklen_t s = sizeof(cli_addr);
    int cfd = accept(
        fd,
        (struct sockaddr*)&cli_addr,
        &s 
    );
    if( cfd < 0 ) {
      perror("accept");
      exit(EXIT_FAILURE);
    }
    struct req rq;
    rq.fd = cfd;
    rq.addr = cli_addr;

    pthread_t serve_t;
    pthread_create(&serve_t, NULL, serve, (void*)&rq);
    pthread_detach(serve_t);
  } 

  

  return 0;
}
