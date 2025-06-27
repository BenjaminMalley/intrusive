#include "ibst.h"

ibst_node_t* ibst_search(ibst_node_t *current, int target, int (*compare)(ibst_node_t *node, int target)) {
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
