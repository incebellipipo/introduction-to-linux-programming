#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef struct linked_list {
  int value;
  struct linked_list* next;
} linked_list;

typedef struct linked_list *node;

node create_node();

node add_node();

#endif