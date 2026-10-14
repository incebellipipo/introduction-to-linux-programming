#include <stdio.h>
#include <stdlib.h>

// Three functions with an identical signature, so they can be addressed through the same pointer type
void f3(void) {
  printf("hello from f3\n");
}

void f2(void) {
  printf("hello from f2\n");
}

void f1(void) {
  printf("hello from f1\n");
}

// Array of 3 pointers to functions taking no arguments and returning void
// A function's name decays to its address, so {f1, f2, f3} needs no '&'
void (*fcaller[3])(void) = {f1, f2, f3};


int main(int argc, char** argv) {

  // Calling through the pointer is the same syntax as a normal call
  for(int i = 0 ; i < 3 ; i++) {
    fcaller[i]();
  }

  return 0;
}
