#include <stdio.h>
#include <stdlib.h>
#include <linked-list.h>

// Allocate one node on the heap and mark it as the end of the list
node create_node() {
  node n;
  // NOTE: malloc result is not checked for NULL, and n->value is left uninitialized
  n = (node)malloc(sizeof(struct linked_list));
  n->next = NULL;
  return n;//return the new node
}

// NOTE: the header declares add_node / create_node, but this file defines addNode and calls createNode,
// so it does not compile as is. The logic is what matters here
// Append 'value' to the list; returns the (possibly new) head
node addNode(node head, int value){
  node temp, p;
  temp = createNode();
  temp->value = value;
  // Empty list: the new node becomes the head
  if(head == NULL){
    head = temp;
  }
  else{
    // Otherwise walk to the last node and link the new one after it (O(n))
    p  = head;
    while(p->next != NULL){
      p = p->next;
    }
    p->next = temp;
  }
  return head;
}

// Nothing is exercised yet; the list functions are not called
int main(int argc, char** argv, char** envp) {


  return 0;
}