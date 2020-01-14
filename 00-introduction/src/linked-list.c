#include <stdio.h>
#include <stdlib.h>
#include <linked-list.h>

node create_node() {
  node n;
  n = (node)malloc(sizeof(struct linked_list));
  n->next = NULL;
  return n;//return the new node
}

node addNode(node head, int value){
  node temp, p;
  temp = createNode();
  temp->value = value;
  if(head == NULL){
    head = temp;
  }
  else{
    p  = head;
    while(p->next != NULL){
      p = p->next;
    }
    p->next = temp;
  }
  return head;
}

int main(int argc, char** argv, char** envp) {


  return 0;
}