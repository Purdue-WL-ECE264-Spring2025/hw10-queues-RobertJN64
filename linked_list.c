#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
  struct list_node *new_node = malloc(sizeof(struct list_node));
  if (new_node == NULL) {
    return NULL;
  }

  new_node->value = value;
  return new_node;
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *old_head = list->head;
  list->head = new_node(value);
  list->head->next = old_head;
}

void insert_at_tail(struct linked_list *list, size_t value) {}

size_t remove_from_head(struct linked_list *list) {
  struct list_node *old_head = list->head;
  list->head = old_head->next;

  size_t value = old_head->value;
  free(old_head);
  return value;
}

size_t remove_from_tail(struct linked_list *list) { return 0; }

void free_list(struct linked_list list) {}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
