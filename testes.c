#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "push_swap.h"

// Helper function to create a stack from an array
t_stack *create_stack_from_array(int *arr, int size) {
    t_stack *stack = NULL;
    for (int i = 0; i < size; i++) {
        t_stack *new_node = create_node(arr[i]);
        if (!stack) {
            stack = new_node;
        } else {
            t_stack *last = stack;
            while (last->next) {
                last = last->next;
            }
            last->next = new_node;
        }
    }
    return stack;
}

// Test function for stack operations
void test_stack_operations() {
    t_stack *a = create_stack_from_array((int[]){3, 2, 1}, 3);
    t_stack *b = NULL;

    sa(&a);
    assert(a->value == 2 && a->next->value == 3 && a->next->next->value == 1);

    pb(&a, &b);
    assert(a->value == 3 && a->next->value == 1 && b->value == 2);

    pa(&a, &b);
    assert(a->value == 2 && a->next->value == 3 && a->next->next->value == 1 && b == NULL);

    ra(&a);
    assert(a->value == 3 && a->next->value == 1 && a->next->next->value == 2);

    rra(&a);
    assert(a->value == 2 && a->next->value == 3 && a->next->next->value == 1);

    free_stack(&a);
    free_stack(&b);
}

// Test function for sorting three elements
void test_sort_three() {
    t_stack *a = create_stack_from_array((int[]){3, 2, 1}, 3);
    sort_three(&a);
    assert(is_sorted(a));
    free_stack(&a);
}

// Test function for sorting five elements
void test_sort_five() {
    t_stack *a = create_stack_from_array((int[]){5, 4, 3, 2, 1}, 5);
    t_stack *b = NULL;
    sort_five(&a, &b);
    assert(is_sorted(a));
    free_stack(&a);
    free_stack(&b);
}

// Test function for chunk sorting
void test_chunk_sort() {
    int arr[100];
    for (int i = 0; i < 100; i++) {
        arr[i] = 100 - i;
    }
    t_stack *a = create_stack_from_array(arr, 100);
    t_stack *b = NULL;
    chunk_sort(&a, &b);
    assert(is_sorted(a));
    free_stack(&a);
    free_stack(&b);
}

// Main function to run all tests
int main() {
    test_stack_operations();
    test_sort_three();
    test_sort_five();
    test_chunk_sort();
    printf("All tests passed!\n");
    return 0;
}