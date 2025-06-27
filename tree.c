#ifndef INTRUSIVE_TREE
#define INTRUSIVE_TREE

#include <stddef.h>

typedef struct node {
    struct node *left;
    struct node *right;
} node_t;

static inline node_t* search(node_t *current, int target, int (*compare)(node_t *node, int target)) {
    while (current != NULL) {
        int result = compare(current, target);
        if (result == 0) {
            return current;
        } else if (result < 0) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return NULL;
}

#define CONTAINER_OF(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

typedef struct task {
    int priority;
    node_t node;
} task_t;

int compare(node_t *current, int target) {
    task_t *task = CONTAINER_OF(current, task_t, node);
    return task->priority - target;
}

#endif
