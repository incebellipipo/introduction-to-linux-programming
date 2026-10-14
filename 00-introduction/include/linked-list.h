// Include guard: prevents the header from being processed twice in one translation unit
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

// A self-referential struct: each node holds a value and a pointer to the next node
typedef struct linked_list {
  int value;
  struct linked_list* next;
} linked_list;

// 'node' is an alias for a pointer to a list element
typedef struct linked_list *node;

// Allocates a new, unlinked node
node create_node();

// Appends a node at the end of the list
node add_node();

#endif