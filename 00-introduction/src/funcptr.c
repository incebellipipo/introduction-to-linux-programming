#include <stdio.h>
#include <stdlib.h>

void f3(void) {
  printf("hello from f3\n");
}

void f2(void) {
  printf("hello from f2\n");
}

void f1(void) {
  printf("hello from f1\n");
}

void (*fcaller[3])(void) = {f1, f2, f3};


int main(int argc, char** argv) {

  for(int i = 0 ; i < 3 ; i++) {
    fcaller[i]();
  }

  return 0;
}
