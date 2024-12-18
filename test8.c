#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H
// Reduce the number of chunks to 5
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h> // Include the necessary header for strlen

typedef struct s_stack
{
    int value;
    struct s_stack *next;
} t_stack;

// Function prototypes for stack operations
void sa(t_stack **a);
void sb(t_stack **b);
void ss(t_stack **a, t_stack **b);
void pa(t_stack **a, t_stack **b);
void pb(t_stack **a, t_stack **b);
void ra(t_stack **a);
void rb(t_stack **b);
void rr(t_stack **a, t_stack **b);
void rra(t_stack **a);
void rrb(t_stack **b);
void rrr(t_stack **a, t_stack **b);

// Utility functions
int is_sorted(t_stack *stack);
void error_exit(const char *msg);
t_stack *create_node(int value);
void free_stack(t_stack **stack);
int stack_size(t_stack *stack);
void print_stack(t_stack *stack, const char *label);

// Function prototypes for the missing functions
int find_min(t_stack *stack);
int get_position(t_stack *stack, int value);
int *create_chunks(t_stack *stack, int chunk_size, int chunk_count);
void push_chunk_to_b(t_stack **a, t_stack **b, int min, int max);
int find_max(t_stack *stack);
int *stack_to_array(t_stack *stack);
void sort_array(int *array, int size);
int find_hold_first(t_stack *stack, int min, int max);
int find_hold_second(t_stack *stack, int min, int max);
int has_values_in_range(t_stack *stack, int min, int max);
void rotate_to_top(t_stack **a, int value);

// Sorting functions
void sort_three(t_stack **a);
void sort_five(t_stack **a, t_stack **b);
void chunk_sort(t_stack **a, t_stack **b);
#endif // PUSH_SWAP_H

void sa(t_stack **a)
{
    t_stack *first;
    t_stack *second;

    if (!a || !*a || !(*a)->next)
        return;
    first = *a;
    second = first->next;
    first->next = second->next;
    second->next = first;
    *a = second;
    write(1, "sa\n", 3);
}

void sb(t_stack **b)
{
    t_stack *first;
    t_stack *second;

    if (!b || !*b || !(*b)->next)
        return;
    first = *b;
    second = first->next;
    first->next = second->next;
    second->next = first;
    *b = second;
    write(1, "sb\n", 3);
}

void ss(t_stack **a, t_stack **b)
{
    sa(a);
    sb(b);
    write(1, "ss\n", 3);
}

void pa(t_stack **a, t_stack **b)
{
    t_stack *temp;

    if (!b || !*b)
        return;
    temp = *b;
    *b = (*b)->next;
    temp->next = *a;
    *a = temp;
    write(1, "pa\n", 3);
}

void pb(t_stack **a, t_stack **b)
{
    t_stack *temp;

    if (!a || !*a)
        return;
    temp = *a;
    *a = (*a)->next;
    temp->next = *b;
    *b = temp;
    write(1, "pb\n", 3);
}

void ra(t_stack **a)
{
    t_stack *first;
    t_stack *last;

    if (!a || !*a || !(*a)->next)
        return;
    first = *a;
    last = *a;
    while (last->next)
        last = last->next;
    *a = first->next;
    first->next = NULL;
    last->next = first;
    write(1, "ra\n", 3);
}

void rb(t_stack **b)
{
    t_stack *first;
    t_stack *last;

    if (!b || !*b || !(*b)->next)
        return;
    first = *b;
    last = *b;
    while (last->next)
        last = last->next;
    *b = first->next;
    first->next = NULL;
    last->next = first;
    write(1, "rb\n", 3);
}

void rr(t_stack **a, t_stack **b)
{
    ra(a);
    rb(b);
    write(1, "rr\n", 3);
}

void rra(t_stack **a)
{
    t_stack *last;
    t_stack *second_last;

    if (!a || !*a || !(*a)->next)
        return;
    last = *a;
    second_last = NULL;
    while (last->next)
    {
        second_last = last;
        last = last->next;
    }
    second_last->next = NULL;
    last->next = *a;
    *a = last;
    write(1, "rra\n", 4);
}

void rrb(t_stack **b)
{
    t_stack *last;
    t_stack *second_last;

    if (!b || !*b || !(*b)->next)
        return;
    last = *b;
    second_last = NULL;
    while (last->next)
    {
        second_last = last;
        last = last->next;
    }
    second_last->next = NULL;
    last->next = *b;
    *b = last;
    write(1, "rrb\n", 4);
}

void rrr(t_stack **a, t_stack **b)
{
    rra(a);
    rrb(b);
    write(1, "rrr\n", 4);
}

t_stack *create_node(int value)
{
    t_stack *node;

    node = malloc(sizeof(t_stack));
    if (!node)
        return NULL;
    node->value = value;
    node->next = NULL;
    return node;
}

void free_stack(t_stack **stack)
{
    t_stack *current;
    t_stack *next;

    current = *stack;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *stack = NULL;
}

int stack_size(t_stack *stack)
{
    int size;

    size = 0;
    while (stack)
    {
        size++;
        stack = stack->next;
    }
    return size;
}

int is_sorted(t_stack *stack)
{
    while (stack && stack->next)
    {
        if (stack->value > stack->next->value)
            return 0;
        stack = stack->next;
    }
    return 1;
}

void error_exit(const char *msg)
{
    write(2, msg, strlen(msg));
    exit(1);
}

void print_stack(t_stack *stack, const char *label)
{
    printf("%s Stack: ", label);
    while (stack)
    {
        printf("%d ", stack->value);
        stack = stack->next;
    }
    printf("\n");
}

void sort_three(t_stack **a)
{
    int first;
    int second;
    int third;

    if (is_sorted(*a))
        return;

    first = (*a)->value;
    second = (*a)->next->value;
    third = (*a)->next->next->value;

    if (first > second && second < third && first < third)
        sa(a);
    else if (first > second && second > third && first > third)
    {
        sa(a);
        rra(a);
    }
    else if (first > second && second < third && first > third)
        ra(a);
    else if (first < second && second > third && first < third)
    {
        sa(a);
        ra(a);
    }
    else if (first < second && second > third && first > third)
        rra(a);
}

void sort_five(t_stack **a, t_stack **b)
{
    int min;

    while (stack_size(*a) > 3)
    {
        min = find_min(*a);
        while ((*a)->value != min)
        {
            if (get_position(*a, min) <= stack_size(*a) / 2)
                ra(a);
            else
                rra(a);
        }
        pb(a, b);
    }
    sort_three(a);
    while (*b)
        pa(a, b);
}

int get_position(t_stack *stack, int value)
{
    int pos;

    pos = 0;
    while (stack)
    {
        if (stack->value == value)
            break;
        pos++;
        stack = stack->next;
    }
    return pos;
}

void chunk_sort(t_stack **a, t_stack **b)
{
    int size;
    int chunk_count;
    int chunk_size;
    int *chunks;
    int i;
    int max;
    
    size = stack_size(*a);
    chunk_count = 4; 
    chunk_size = size / chunk_count;
    chunks = create_chunks(*a, chunk_size, chunk_count);
    i = 0;

    while (i < chunk_count)
    {
        push_chunk_to_b(a, b, chunks[i], chunks[i + 1]);
        i++;
    }
    while (*b)
    {
        max = find_max(*b);
        while ((*b)->value != max)
        {
            if (get_position(*b, max) <= stack_size(*b) / 2)
                rb(b);
            else
                rrb(b);
        }
        pa(a, b);
        if (*b && (*b)->next && (*b)->value < (*b)->next->value)
            sb(b);
    }
    free(chunks);
}

void rotate_to_top(t_stack **stack, int value)
{
    int pos = get_position(*stack, value);
    int size = stack_size(*stack);

    if (pos <= size / 2)
    {
        while ((*stack)->value != value)
            ra(stack);
    } else
    {
        while ((*stack)->value != value)
            rra(stack);
    }
}

void rotate_closer_to_top(t_stack **a, int hold_first, int hold_second) {
    int pos_first;
    int pos_second;
    int size;

    pos_first = get_position(*a, hold_first);
    pos_second = get_position(*a, hold_second);
    size = stack_size(*a);
    if (pos_first <= size / 2 && pos_second <= size / 2)
    {
        if (pos_first <= pos_second)
            rotate_to_top(a, hold_first);
        else
            rotate_to_top(a, hold_second);
    } else if (pos_first > size / 2 && pos_second > size / 2)
    {
        if (pos_first >= pos_second)
            rotate_to_top(a, hold_first);
        else
            rotate_to_top(a, hold_second);
    } else
    {
        if (pos_first <= size / 2)
            rotate_to_top(a, hold_first);
        else
            rotate_to_top(a, hold_second);
    }
}

void push_chunk_to_b(t_stack **a, t_stack **b, int min, int max)
{
    int hold_first;
    int hold_second;

    while (has_values_in_range(*a, min, max))
    {
        hold_first = find_hold_first(*a, min, max);
        hold_second = find_hold_second(*a, min, max);
        if (hold_first != -1 && hold_second != -1)
            rotate_closer_to_top(a, hold_first, hold_second);
        else if (hold_first != -1)
            rotate_to_top(a, hold_first);
        else if (hold_second != -1)
            rotate_to_top(a, hold_second);
        pb(a, b);
    }
}


int find_hold_first(t_stack *stack, int min, int max)
{
    int pos;

    pos = 0;
    while (stack)
    {
        if (stack->value >= min && stack->value <= max)
            return stack->value;
        stack = stack->next;
        pos++;
    }
    return -1;
}

int find_hold_second(t_stack *stack, int min, int max)
{
    int pos;
    t_stack *current;

    pos = stack_size(stack) - 1;
    current = stack;
    while (current)
    {
        if (current->value >= min && current->value <= max)
            return current->value;
        current = current->next;
        pos--;
    }
    return -1;
}

int has_values_in_range(t_stack *stack, int min, int max)
{
    while (stack)
    {
        if (stack->value >= min && stack->value <= max)
            return 1;
        stack = stack->next;
    }
    return 0;
}

int find_min(t_stack *stack)
{
    int min;

    min = stack->value;
    while (stack)
    {
        if (stack->value < min)
            min = stack->value;
        stack = stack->next;
    }
    return min;
}

int find_max(t_stack *stack)
{
    int max;

    max = stack->value;
    while (stack)
    {
        if (stack->value > max)
            max = stack->value;
        stack = stack->next;
    }
    return max;
}

int *create_chunks(t_stack *stack, int chunk_size, int chunk_count)
{
    int *chunks;
    int *values;
    int i;

    chunks = malloc(sizeof(int) * (chunk_count + 1));
    values = stack_to_array(stack);
    sort_array(values, stack_size(stack));

    i = 0;
    while (i < chunk_count)
    {
        chunks[i] = values[i * chunk_size];
        i++;
    }
    chunks[chunk_count] = values[stack_size(stack) - 1];

    free(values);
    return chunks;
}

int *stack_to_array(t_stack *stack)
{
    int size;
    int *array;
    int i;

    size = stack_size(stack);
    array = malloc(sizeof(int) * size);
    i = 0;
    while (i < size)
    {
        array[i] = stack->value;
        stack = stack->next;
        i++;
    }
    return array;
}

void sort_array(int *array, int size)
{
    int i;
    int j;
    int temp;

    i = 0;
    while (i < size - 1)
    {
        j = 0;
        while (j < size - i - 1)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}
int main(int argc, char **argv)
{
    t_stack *a;
    t_stack *b;
    int i;
    long num;
    t_stack *new_node;
    t_stack *last;
    int size;

    a = NULL;
    b = NULL;

    if (argc < 2)
    {
        write(2, "Usage: ./push_swap <numbers>\n", 29);
        return 1;
    }

    i = 1;
    while (i < argc)
    {
        num = atol(argv[i]);
        if (num > INT_MAX || num < INT_MIN)
        {
            write(2, "Error\n", 6);
            free_stack(&a);
            return 1;
        }
        new_node = create_node((int)num);
        if (!a)
            a = new_node;
        else
        {
            last = a;
            while (last->next)
                last = last->next;
            last->next = new_node;
        }
        i++;
    }

    if (is_sorted(a))
    {
        print_stack(a, "Sorted");
        free_stack(&a);
        return 0;
    }

    size = stack_size(a);
    if (size <= 3)
        sort_three(&a);
    else if (size <= 5)
        sort_five(&a, &b);
    else
        chunk_sort(&a, &b);
    print_stack(a, "Sorted");
    free_stack(&a);
    free_stack(&b);
    return 0;
}
