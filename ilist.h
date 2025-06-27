#ifndef INTRUSIVE_LIST_H
#define INTRUSIVE_LIST_H

#include <stddef.h>

typedef struct ilist_node {
    struct ilist_node *next;
} ilist_node_t;

static inline void ilist_ins_after(ilist_node_t *prev, ilist_node_t *toInsert) {
    ilist_node_t *next = prev->next;
    prev->next = toInsert;
    toInsert->next = next;
}

static inline ilist_node_t* ilist_del_after(ilist_node_t *prev) {
    ilist_node_t *next = prev->next;
    if (next == NULL) {
        return NULL; // No node to delete after prev
    }
    prev->next = next->next;
    return next;
}

#endif
