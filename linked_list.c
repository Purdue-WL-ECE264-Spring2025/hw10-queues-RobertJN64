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

// creates a new node and inserts at the head of a linked list
// the new node now points to the old head
void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *old_head = list->head;
  list->head = new_node(value);
  list->head->next = old_head;
}

// creates a new node and inserts at the tail of a linked list
// the previous tail now points to the new node
void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node *new_tail = new_node(value);

  struct list_node *old_tail = list->head;
  if (old_tail == NULL) {
    list->head = new_tail;
  } else {
    while (old_tail->next != NULL) {
      old_tail = old_tail->next;
    }
    old_tail->next = new_tail;
  }
}

// returns the value of the current head node
// head now points to the 2nd node
// if list is empty, returns 0
size_t remove_from_head(struct linked_list *list) {
  struct list_node *old_head = list->head;

  if (old_head == NULL) {
    return 0;
  }

  list->head = old_head->next;
  size_t value = old_head->value;
  free(old_head);
  return value;
}

// returns the value of the final node in the linked list
// final node now points to NULL
// if list is empty, returns 0
size_t remove_from_tail(struct linked_list *list) {
  struct list_node *current_node = list->head;

  // list is empty
  if (current_node == NULL) {
    return 0;
  }

  // list only has one element
  if (current_node->next == NULL) {
    size_t value = current_node->value;
    free(current_node);
    list->head = NULL;
    return value;
  }

  // find the second to last node
  while (current_node->next->next != NULL) {
    current_node = current_node->next;
  }
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
