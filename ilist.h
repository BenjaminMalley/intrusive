#ifndef INTRUSIVE_LIST_H
#define INTRUSIVE_LIST_H

typedef struct ilist_node {
    ilist_node *next;
} ilist_node_t;

static inline void ilist_ins_after(ilist_node_t *prev, ilist_node_t *toInsert) {
    ilist_node_t *next = prev->next;
    prev->next = toInsert;
    toInsert->next = next;
}

static inline ilist_node_t* ilist_del_after(ilist_node_t *prev) {
    ilist_node_t *next = prev->next;
    prev->next = next->next;
    return next;
}

#endif
