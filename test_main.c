#include <stdio.h>
#include <stdlib.h> // For malloc/free

#include "ibst.h"
#include "ilist.h"
#include "idlist.h"

typedef struct ilist_item {
    int value;
    ilist_node_t node;
} ilist_item_t;

// Helper to create an ilist_item
ilist_item_t* create_ilist_item(int value) {
    ilist_item_t *new_item = (ilist_item_t*) malloc(sizeof(ilist_item_t));
    if (new_item == NULL) {
        fprintf(stderr, "Memory allocation failed for ilist_item.\n");
        exit(EXIT_FAILURE);
    }
    new_item->value = value;
    new_item->node.next = NULL;
    return new_item;
}

typedef struct idlist_item {
    int value;
    idlist_node_t node;
} idlist_item_t;

// Helper to create an idlist_item
idlist_item_t* create_idlist_item(int value) {
    idlist_item_t *new_item = (idlist_item_t*) malloc(sizeof(idlist_item_t));
    if (new_item == NULL) {
        fprintf(stderr, "Memory allocation failed for idlist_item.\n");
        exit(EXIT_FAILURE);
    }
    new_item->value = value;
    new_item->node.next = NULL;
    new_item->node.prev = NULL;
    return new_item;
}

static int tests_run = 0;
static int tests_passed = 0;

typedef struct task {
    int priority;
    ibst_node_t node;
} task_t;

int compare(ibst_node_t *current, int target) {
    task_t *task = CONTAINER_OF(current, task_t, node);
    return task->priority - target;
}

#define ASSERT_TRUE(condition, message) do { \
    tests_run++; \
    if (condition) { \
        tests_passed++; \
        printf("[PASSED] %s\n", message); \
    } else { \
        printf("[FAILED] %s (Condition: %s)\n", message, #condition); \
    } \
} while (0)

// Helper function to create a task node for testing purposes
task_t* create_test_task_node(int priority) {
    task_t *new_task = (task_t*) malloc(sizeof(task_t));
    if (new_task == NULL) {
        fprintf(stderr, "Memory allocation failed for test task node.\n");
        exit(EXIT_FAILURE);
    }
    new_task->priority = priority;
    new_task->node.left = NULL;
    new_task->node.right = NULL;
    return new_task;
}

void test_compare_function() {
    printf("\n--- Running Test: test_compare_function ---\n");
    task_t t1;
    t1.priority = 10;

    ASSERT_TRUE(compare(&t1.node, 10) == 0, "compare(10, 10) should return 0");
    ASSERT_TRUE(compare(&t1.node, 5) > 0, "compare(10, 5) should return > 0");
    ASSERT_TRUE(compare(&t1.node, 15) < 0, "compare(10, 15) should return < 0");
}

void test_search_empty_tree() {
    printf("\n--- Running Test: test_search_empty_tree ---\n");
    ibst_node_t *result = ibst_search(NULL, 10, compare);
    ASSERT_TRUE(result == NULL, "search in an empty tree should return NULL");
}

void test_search_single_node_tree() {
    printf("\n--- Running Test: test_search_single_node_tree ---\n");
    task_t *root_task = create_test_task_node(20);

    ibst_node_t *result_found = ibst_search(&root_task->node, 20, compare);
    ASSERT_TRUE(result_found == &root_task->node, "search for existing node (20) in single node tree");

    ibst_node_t *result_not_found = ibst_search(&root_task->node, 10, compare);
    ASSERT_TRUE(result_not_found == NULL, "search for non-existing node (10) in single node tree");

    free(root_task);
}

void test_search_multi_node_tree() {
    printf("\n--- Running Test: test_search_multi_node_tree ---\n");
    // Build a simple tree:
    //      20 (root_task)
    //     /  \
    //    10  30 (left_task, right_task)
    task_t *root_task = create_test_task_node(20);
    task_t *left_task = create_test_task_node(10);
    task_t *right_task = create_test_task_node(30);

    root_task->node.left = &left_task->node;
    root_task->node.right = &right_task->node;

    // Test existing nodes
    ibst_node_t *result_20 = ibst_search(&root_task->node, 20, compare);
    ASSERT_TRUE(result_20 == &root_task->node, "search for root node (20) in multi-node tree");

    ibst_node_t *result_10 = ibst_search(&root_task->node, 10, compare);
    ASSERT_TRUE(result_10 == &left_task->node, "search for left child (10) in multi-node tree");

    ibst_node_t *result_30 = ibst_search(&root_task->node, 30, compare);
    ASSERT_TRUE(result_30 == &right_task->node, "search for right child (30) in multi-node tree");

    // Test non-existing nodes
    ibst_node_t *result_5 = ibst_search(&root_task->node, 5, compare);
    ASSERT_TRUE(result_5 == NULL, "search for non-existing node (5) in multi-node tree");

    ibst_node_t *result_15 = ibst_search(&root_task->node, 15, compare);
    ASSERT_TRUE(result_15 == NULL, "search for non-existing node (15) in multi-node tree");

    ibst_node_t *result_25 = ibst_search(&root_task->node, 25, compare);
    ASSERT_TRUE(result_25 == NULL, "search for non-existing node (25) in multi-node tree");

    ibst_node_t *result_35 = ibst_search(&root_task->node, 35, compare);
    ASSERT_TRUE(result_35 == NULL, "search for non-existing node (35) in multi-node tree");

    free(root_task);
    free(left_task);
    free(right_task);
}

void test_ilist_ins_after() {
    printf("\n--- Running Test: test_ilist_ins_after ---\n");
    ilist_item_t *head = create_ilist_item(10);
    ilist_item_t *item1 = create_ilist_item(20);
    ilist_item_t *item2 = create_ilist_item(30);

    // Initial list: head -> NULL
    // Insert item1 after head: head -> item1 -> NULL
    ilist_ins_after(&head->node, &item1->node);
    ASSERT_TRUE(head->node.next == &item1->node, "ilist_ins_after: head->next should be item1");
    ASSERT_TRUE(item1->node.next == NULL, "ilist_ins_after: item1->next should be NULL");

    // Insert item2 after head: head -> item2 -> item1 -> NULL
    ilist_ins_after(&head->node, &item2->node);
    ASSERT_TRUE(head->node.next == &item2->node, "ilist_ins_after: head->next should be item2");
    ASSERT_TRUE(item2->node.next == &item1->node, "ilist_ins_after: item2->next should be item1");
    ASSERT_TRUE(item1->node.next == NULL, "ilist_ins_after: item1->next should still be NULL");

    free(head);
    free(item1);
    free(item2);
}

void test_ilist_del_after() {
    printf("\n--- Running Test: test_ilist_del_after ---\n");
    ilist_item_t *head = create_ilist_item(10);
    ilist_item_t *item1 = create_ilist_item(20);
    ilist_item_t *item2 = create_ilist_item(30);

    // Build list: head -> item1 -> item2 -> NULL
    ilist_ins_after(&head->node, &item2->node);
    ilist_ins_after(&head->node, &item1->node);

    // List is now: head(10) -> item1(20) -> item2(30) -> NULL
    ASSERT_TRUE(head->node.next == &item1->node, "ilist_del_after setup: head->next should be item1");
    ASSERT_TRUE(item1->node.next == &item2->node, "ilist_del_after setup: item1->next should be item2");
    ASSERT_TRUE(item2->node.next == NULL, "ilist_del_after setup: item2->next should be NULL");

    // Delete item1 (after head)
    ilist_node_t *deleted_node = ilist_del_after(&head->node);
    ASSERT_TRUE(deleted_node == &item1->node, "ilist_del_after: Deleted node should be item1");
    ASSERT_TRUE(head->node.next == &item2->node, "ilist_del_after: head->next should now be item2");
    ASSERT_TRUE(item2->node.next == NULL, "ilist_del_after: item2->next should still be NULL");

    // Delete item2 (which is now after head)
    deleted_node = ilist_del_after(&head->node);
    ASSERT_TRUE(deleted_node == &item2->node, "ilist_del_after: Deleted node should be item2");
    ASSERT_TRUE(head->node.next == NULL, "ilist_del_after: head->next should now be NULL");

    // Attempt to delete from an empty list (after head which has no next)
    deleted_node = ilist_del_after(&head->node);
    ASSERT_TRUE(deleted_node == NULL, "ilist_del_after: Deleting from empty list should return NULL");

    free(head);
    free(item1); // Still need to free even if deleted from list
    free(item2); // Still need to free even if deleted from list
}

void test_idlist_ins() {
    printf("\n--- Running Test: test_idlist_ins ---\n");
    idlist_item_t *head = create_idlist_item(10);
    idlist_item_t *item1 = create_idlist_item(20);
    idlist_item_t *item2 = create_idlist_item(30);

    // A head node for an intrusive doubly linked list needs to point to itself
    // to represent an empty list.
    head->node.next = &head->node;
    head->node.prev = &head->node;

    // Insert item1 after head: head <-> item1 <-> head
    ilist_ins(&item1->node, &head->node); // Note: idlist.h uses ilist_ins/del
    ASSERT_TRUE(head->node.next == &item1->node, "idlist_ins: head->next should be item1");
    ASSERT_TRUE(head->node.prev == &item1->node, "idlist_ins: head->prev should be item1");
    ASSERT_TRUE(item1->node.next == &head->node, "idlist_ins: item1->next should be head");
    ASSERT_TRUE(item1->node.prev == &head->node, "idlist_ins: item1->prev should be head");

    // Insert item2 after head (i.e., before item1): head <-> item2 <-> item1 <-> head
    ilist_ins(&item2->node, &head->node);
    ASSERT_TRUE(head->node.next == &item2->node, "idlist_ins: head->next should be item2");
    ASSERT_TRUE(item2->node.next == &item1->node, "idlist_ins: item2->next should be item1");
    ASSERT_TRUE(item1->node.prev == &item2->node, "idlist_ins: item1->prev should be item2");
    ASSERT_TRUE(head->node.prev == &item1->node, "idlist_ins: head->prev should be item1");

    free(head);
    free(item1);
    free(item2);
}

void test_idlist_del() {
    printf("\n--- Running Test: test_idlist_del ---\n");
    idlist_item_t *head = create_idlist_item(10);
    idlist_item_t *item1 = create_idlist_item(20);
    idlist_item_t *item2 = create_idlist_item(30);

    head->node.next = &head->node;
    head->node.prev = &head->node;

    // Build list: head <-> item1 <-> item2 <-> head
    ilist_ins(&item1->node, &head->node);
    ilist_ins(&item2->node, &item1->node); // Insert item2 after item1

    // Verify setup
    ASSERT_TRUE(head->node.next == &item1->node, "idlist_del setup: head->next should be item1");
    ASSERT_TRUE(item1->node.prev == &head->node, "idlist_del setup: item1->prev should be head");
    ASSERT_TRUE(item1->node.next == &item2->node, "idlist_del setup: item1->next should be item2");
    ASSERT_TRUE(item2->node.prev == &item1->node, "idlist_del setup: item2->prev should be item1");
    ASSERT_TRUE(item2->node.next == &head->node, "idlist_del setup: item2->next should be head");
    ASSERT_TRUE(head->node.prev == &item2->node, "idlist_del setup: head->prev should be item2");

    // Delete item1
    ilist_del(&item1->node);
    ASSERT_TRUE(head->node.next == &item2->node, "idlist_del: head->next should be item2 after deleting item1");
    ASSERT_TRUE(item2->node.prev == &head->node, "idlist_del: item2->prev should be head after deleting item1");
    ASSERT_TRUE(item1->node.next == NULL, "idlist_del: deleted item1->next should be NULL");
    ASSERT_TRUE(item1->node.prev == NULL, "idlist_del: deleted item1->prev should be NULL");

    // Delete item2 (now it's the only one between head and head)
    ilist_del(&item2->node);
    ASSERT_TRUE(head->node.next == &head->node, "idlist_del: head->next should point to itself after deleting all items");
    ASSERT_TRUE(head->node.prev == &head->node, "idlist_del: head->prev should point to itself after deleting all items");
    ASSERT_TRUE(item2->node.next == NULL, "idlist_del: deleted item2->next should be NULL");
    ASSERT_TRUE(item2->node.prev == NULL, "idlist_del: deleted item2->prev should be NULL");

    free(head);
    free(item1);
    free(item2);
}

int main() {
    printf("Running unit tests for intrusive data structures (IBST, Ilist, IDList)...\n");

    test_compare_function();
    test_search_empty_tree();
    test_search_single_node_tree();
    test_search_multi_node_tree();

    // Intrusive List Tests
    test_ilist_ins_after();
    test_ilist_del_after();

    // Intrusive Doubly Linked List Tests
    test_idlist_ins();
    test_idlist_del();

    printf("\n--- Test Summary ---\n");
    printf("Total tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);

    if (tests_passed == tests_run) {
        printf("All tests passed!\n");
        return EXIT_SUCCESS;
    } else {
        printf("Some tests failed.\n");
        return EXIT_FAILURE;
    }
}
