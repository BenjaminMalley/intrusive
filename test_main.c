#include <stdio.h>
#include <stdlib.h> // For malloc/free

#include "ibst.h"

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

int main() {
    printf("Running unit tests for tree.c functions...\n");

    test_compare_function();
    test_search_empty_tree();
    test_search_single_node_tree();
    test_search_multi_node_tree();

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
