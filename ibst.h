#ifndef INTRUSIVE_TREE_H
#define INTRUSIVE_TREE_H

#include <stddef.h>
#include "common.h"

typedef struct ibst_node {
  struct ibst_node *left;
  struct ibst_node *right;
} ibst_node_t;

ibst_node_t* ibst_search(ibst_node_t *current, int target, int (*compare)(ibst_node_t *node, int target));

int compare(ibst_node_t *current, int target);

#endif
