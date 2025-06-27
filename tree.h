#ifndef INTRUSIVE_TREE_H
#define INTRUSIVE_TREE_H

#include <stddef.h>

typedef struct node {
  struct node *left;
  struct node *right;
} node_t;

node_t* search(node_t *current, int target, int (*compare)(node_t *node, int target));

#define CONTAINER_OF(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

int compare(node_t *current, int target);

#endif
