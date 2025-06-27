#ifndef INTRUSIVE_LIST
#define INTRUSIVE_LIST

#include <stddef.h>

typedef struct node {
    struct node *next;
    struct node *prev;
} node_t;

static inline void insert(node_t *new, node_t *prev) {
    node_t *next = prev->next;
    prev->next = new;
    new->next = next;
    new->prev = prev;
    next->prev = new;
}

static inline void delete(node_t *toDelete) {
    node_t *prev = toDelete->prev;
    node_t *next = toDelete->next;
    next->prev = prev;
    prev->next = next;
    toDelete->prev = NULL;
    toDelete->next = NULL;
}

#define CONTAINER_OF(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

    
#endif