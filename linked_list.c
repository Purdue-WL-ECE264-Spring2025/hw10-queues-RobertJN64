#include "linked_list.h"

#include <stdlib.h>

// allocates the memory and sets the value of a new list node
// returns NULL if malloc fails
// the new_node points to NULL
struct list_node *new_node(size_t value) {
  struct list_node *new_node = malloc(sizeof(struct list_node));
  if (new_node == NULL) {
    return NULL;
  }

  new_node->next = NULL;
  new_node->value = value;
  return new_node;
}

// the code spends 99% of its time iterating over the linked list
// so these functions are modified to allow O(1) insertions at both ends, and O(1) removals from the head
// the "head" of the list now contains pointers to the head and tail nodes

// creates a new node and inserts at the head of a linked list
// the new node now points to the old head
void insert_at_head(struct linked_list *list, size_t value) {
  if (list->head == NULL) { // if the list is not init, create a head node that points to NULL, NULL
    list->head = new_node((size_t)NULL);
  }

  struct list_node *node_to_add = new_node(value);
  if (list->head->next == NULL) { // list is empty, so new node becomes the head and tail
    list->head->next = node_to_add;
    list->head->value = (size_t)node_to_add;
    return;
  }

  node_to_add->next = list->head->next; // new node points at current first node
  list->head->next = node_to_add;       // list now treats new node as the first node
}

// creates a new node and inserts at the tail of a linked list
// the previous tail now points to the new node
void insert_at_tail(struct linked_list *list, size_t value) {
  if (list->head == NULL) { // if the list is not init, create a head node that points to NULL, NULL
    list->head = new_node((size_t)NULL);
  }

  struct list_node *node_to_add = new_node(value);
  if (list->head->next == NULL) { // list is empty, so new node becomes the head and tail
    list->head->next = node_to_add;
    list->head->value = (size_t)node_to_add;
    return;
  }

  ((struct list_node *)(list->head->value))->next = node_to_add; // tail node now points to new node
  list->head->value = (size_t)node_to_add;                       // head contains ref to the tail node
}

// returns the value of the current head node
// head now points to the 2nd node
// if list is empty, returns 0
size_t remove_from_head(struct linked_list *list) {
  if (list->head == NULL) { // list is not init
    return 0;
  }

  if (list->head->next == NULL) { // list is empty
    return 0;
  }

  size_t value = list->head->next->value;
  struct list_node *new_head = list->head->next->next;
  free(list->head->next);
  list->head->next = new_head;
  return value;
}

// returns the value of the final node in the linked list
// final node now points to NULL
// if list is empty, returns 0
size_t remove_from_tail(struct linked_list *list) {
  if (list->head == NULL) { // list is not init
    return 0;
  }

  if (list->head->next == NULL) { // list is empty
    return 0;
  }

  struct list_node *current_node = list->head->next;

  // list only has one element
  if (current_node->next == NULL) {
    size_t value = current_node->value;

    list->head->value = (size_t)NULL;
    list->head->next = NULL;

    free(current_node);
    return value;
  }

  // find the second to last node
  while (current_node->next->next != NULL) {
    current_node = current_node->next;
  }
  list->head->value = (size_t)current_node;
  size_t value = current_node->next->value;
  free(current_node->next);
  current_node->next = NULL;
  return value;
}

// frees memory of all nodes in list
void free_list(struct linked_list list) {
  struct list_node *node = list.head;
  while (node != NULL) {
    struct list_node *next_node = node->next;
    free(node);
    node = next_node;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
