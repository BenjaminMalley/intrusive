#ifndef INTRUSIVE_DLIST_H
#define INTRUSIVE_DLIST_H

#include <stddef.h>
#include "common.h"

typedef struct idlist_node {
    struct idlist_node *next;
    struct idlist_node *prev;
} idlist_node_t;

static inline void ilist_ins(idlist_node_t *toInsert, idlist_node_t *prev) {
    idlist_node_t *next = prev->next;
    prev->next = toInsert;
    toInsert->next = next;
    toInsert->prev = prev;
    next->prev = toInsert;
}

static inline void ilist_del(idlist_node_t *toDelete) {
    idlist_node_t *prev = toDelete->prev;
    idlist_node_t *next = toDelete->next;
    next->prev = prev;
    prev->next = next;
    toDelete->prev = NULL;
    toDelete->next = NULL;
}

#endif
